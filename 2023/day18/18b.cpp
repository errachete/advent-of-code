#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

using llint = unsigned long long int;
using ii = pair<int,int>;
using iii = pair<int,ii>;

enum dir {U, R, D, L};
vector<ii> dCoords = {{-1,0},{0,1},{1,0},{0,-1}};
dir opDir(dir direc)
{
    switch(direc)
    {
        case U: return D;
        case R: return L;
        case D: return U;
        case L: return R;
    }
    return U;
}
// Transform number to dir, following the description in the problem or direct char
dir toDir(char num)
{
    switch(num)
    {
        case '0': return R;
        case '1': return D;
        case '2': return L;
        case '3': return U;
        case 'U': return U;
        case 'R': return R;
        case 'D': return D;
        case 'L': return L;
    }
    return U;
}
// Additional movement for horizontal segments, depending on direction of previous movement,
// current direction, next movement and general figure direction 
int addition(dir prev, dir curr, dir next, bool clkws) 
{
    // Two consecutive turns in the general direction means adding one
    // Two consecutive turns in the opposite direction means subtracting one
    if ((prev == U && curr == R && next == D) ||
        (prev == D && curr == L && next == U))
        return clkws ? 1 : -1;
    if ((prev == D && curr == R && next == U) ||
        (prev == U && curr == L && next == D))
        return clkws ? -1 : 1;

    // EOC nothing to add nor subtract
    return 0;
}

bool operator<(const iii & one, const iii & other)
{
    return one.first < other.first || 
            (one.first == other.first &&
             one.second.first < other.second.first);
}

ii intersection(const ii & one, const ii & other)
{
    // No intersection
    if (other.first >= one.second || one.first >= other.second)
        return make_pair(-1,-1);

    return make_pair(
        (one.first > other.first ? one.first : other.first),
        (one.second < other.second ? one.second : other.second)
    );
}

int main() 
{
    ifstream fin("input.txt");
    string line;
    vector<pair<int,dir>> instr;
    int maxU = 0, maxL = 0, row = 0, col = 0;
    ii startPoint = make_pair(0,0);
    int startIdx = 0;
    // Read the instruccions and compute the necessary map size
    while (getline(fin, line))
    {
        istringstream in(line);
        int steps;
        char dirChar;
        string color;
        in >> dirChar >> steps >> color;

        dir direc = toDir(color[7]);
        color = color.substr(2,5);
        istringstream hexin(color);
        hexin >> hex >> steps;

        instr.emplace_back(steps,direc);
        if (row < startPoint.first || (row == startPoint.first && col < startPoint.second))
        {
            startPoint = make_pair(row,col);
            startIdx = instr.size() - 1;
        }

        row += dCoords[direc].first * steps;
        col += dCoords[direc].second * steps;

        maxU = maxU < row ? maxU : row;
        maxL = maxL < col ? maxL : col;
    }  
    fin.close();
    
    vector<iii> horItv;
    row = startPoint.first - maxU;
    col = startPoint.second - maxL;
    instr.insert(instr.end(), instr.begin(), instr.begin()+startIdx);
    instr.erase(instr.begin(), instr.begin()+startIdx);
    // General figure direction
    bool clkws = instr[0].second == R;
    for (int i = 0; i < instr.size(); ++i)
    {
        int steps = instr[i].first;
        dir direc = instr[i].second;

        dir prev = instr[(i-1+instr.size())%instr.size()].second;
        dir next = instr[(i+1)%instr.size()].second;

        steps += addition(prev,direc,next,clkws);

        if (direc == L || direc == R)
        {
            horItv.emplace_back(row,make_pair(col,col+dCoords[direc].second*steps));
            if (horItv.back().second.second < horItv.back().second.first) 
                swap(horItv.back().second.second, horItv.back().second.first);
        }

        row += dCoords[direc].first * steps;
        col += dCoords[direc].second * steps;
    }

    // Sort intervals by row and left to right
    sort(horItv.begin(), horItv.end());

    // Traverse the horizontal intervals, ordered by row, and search, for each one, 
    // the intervals below that act as limits
    llint total = 0;
    for (int i = 0; i < horItv.size(); ++i)
    {
        iii upLim = horItv[i];

        for (int j = i+1; j < horItv.size(); ++j)
        {
            iii currItv = horItv[j];
            // If it's in the same row, continue
            if (currItv.first == upLim.first)
                continue;

            // Compute intersection
            ii intItv = intersection(upLim.second, currItv.second);
            // If no intersection, nothing to do
            if (intItv == make_pair(-1,-1))
                continue;

            // If there is intersection, it defines an area of the figure that has to be counted
            llint width = intItv.second - intItv.first;
            llint height = currItv.first - upLim.first + 1;
            total += width * height;
            // Now, the remainders of both intervals have to be properly treated
            iii currItvLeft = make_pair(currItv.first, make_pair(currItv.second.first, intItv.first));
            iii currItvRight = make_pair(currItv.first, make_pair(intItv.second, currItv.second.second));

            if (currItvLeft.second.first < currItvLeft.second.second) 
                horItv[j] = currItvLeft;
            else  
            {
                horItv.erase(horItv.begin()+j);
                --j;
            }
            if (currItvRight.second.first < currItvRight.second.second)
            {
                horItv.insert(horItv.begin()+j+1, currItvRight);
                ++j;
            }

            iii upLimLeft = make_pair(upLim.first, make_pair(upLim.second.first, intItv.first));
            iii upLimRight = make_pair(upLim.first, make_pair(intItv.second, upLim.second.second));

             if (upLimRight.second.first < upLimRight.second.second)
            {
                horItv.insert(horItv.begin()+i+1, upLimRight);
                ++j;
            }
            if (upLimLeft.second.first < upLimLeft.second.second)
            {
                upLim = upLimLeft;
            }
            else
                break;            
        }
    }

    cout << "Answer: " << total << endl;

    return 0;
}