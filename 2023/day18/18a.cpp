#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

using ii = pair<int,int>;

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
dir toDir(char direc)
{
    switch(direc)
    {
        case 'U': return U;
        case 'R': return R;
        case 'D': return D;
        case 'L': return L;
    }
    return U;
}

void floodFill(vector<vector<char>> & map, int row, int col, char fill, char empty)
{
    if (map[row][col] == empty)
    {
        map[row][col] = fill;
        for (int i = 0; i < dCoords.size(); ++i)
        {
            int newRow = row + dCoords[i].first;
            int newCol = col + dCoords[i].second;
            if (map[newRow][newCol] == empty)
                floodFill(map,newRow,newCol,fill,empty);
        }
    }
}

void printMap(const vector<vector<char>> & map)
{
    ofstream out("output.txt");
    for (auto r : map)
    {
        for (auto c : r)
            out << c;
        out << '\n';
    }
    out.close();
}

int main() 
{
    ifstream fin("input.txt");
    string line;
    vector<pair<int,dir>> instr;
    int maxU = 0, maxR = 0, maxD = 0, maxL = 0, row = 0, col = 0;
    // Read the instruccions and compute the necessary map size
    while (getline(fin, line))
    {
        istringstream in(line);
        int steps;
        char dirChar;
        in >> dirChar >> steps;
        dir direc = toDir(dirChar);
        instr.emplace_back(steps, direc);

        row += dCoords[direc].first * steps;
        col += dCoords[direc].second * steps;

        maxU = maxU < row ? maxU : row;
        maxD = maxD > row ? maxD : row;
        maxL = maxL < col ? maxL : col;
        maxR = maxR > col ? maxR : col;
    }
    fin.close();

    vector<vector<char>> map(maxD-maxU+1, vector<char>(maxR-maxL+1, '.'));
    int sRow = -maxU, sCol = -maxL; // Start point to avoid getting out of the map

    // Follow the instructions painting the map accordingly
    for (int i = 0; i < instr.size(); ++i)
    {
        for (int j = 0; j < instr[i].first; ++j)
        {
            sRow += dCoords[instr[i].second].first;
            sCol += dCoords[instr[i].second].second;
            map[sRow][sCol] = '#';
        }
    }

    // Search for first corner cell. As the search is done row by row and left to right,
    // the cell down and right to the first found must be "inside"
    // .F#
    // .#.
    int i = 0;
    while (map[0][i] == '.') ++i;
    int iRow = 1, iCol = i+1;

    // Flood fill from the inside cell found
    floodFill(map, iRow, iCol, '#', '.');
    
    // Count filled cells
    int count = 0;
    for (auto r : map)
        for (auto c : r)
            if (c == '#') ++count;

    //printMap(map);

    cout << "Answer: " << count << endl;

    return 0;
}