#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;
using ii = pair<int,int>;

enum dir {U=1, R=2, D=4, L=8};
unordered_map<dir,ii> dir2pair = {{U,{-1,0}},{R,{0,1}},{D,{1,0}},{L,{0,-1}}};
struct pos
{
    int i;
    int j;
    dir d;
};

dir turn90(const dir d)
{
    switch(d)
    {
        case U: return R;
        case R: return D;
        case D: return L;
        case L: return U;
    }
    return U;
}

bool repeated(int cell, dir d)
{
    return cell != -1 && ((cell & d) == d);
}

bool move(vector<vector<int>> & map, pos & cur)
{
    // Mark current cell as visited with given direction
    map[cur.i][cur.j] |= cur.d;
    // Check the next cell
    ii next = {cur.i + dir2pair[cur.d].first, cur.j + dir2pair[cur.d].second};
    if (next.first < 0 || next.first >= map.size() ||
        next.second < 0 || next.second >= map[0].size() ||
        repeated(map[next.first][next.second], cur.d))
        return false;
    // If obstacle, turn right and try to move again
    if (map[next.first][next.second] == -1)
    {
        cur.d = turn90(cur.d);
        return move(map, cur);
    }
    // If free cell, move to it
    cur.i = next.first;
    cur.j = next.second;
    return true;
}


int main()
{
    // Read input map
    ifstream in("input.txt");
    vector<vector<int>> map;
    string aux;
    pos cur;
    int i = 0;
    while (getline(in,aux))
    {
        vector<int> line;
        for (int j = 0; j < aux.size(); ++j)
        {
            line.push_back(aux[j] == '#' ? -1 : 0);
            if (aux[j] == '^')
                cur = {i, j, dir(U)};
        }
        map.push_back(line);
        ++i;
    }
    in.close();

    int passed = 1;
    while (move(map, cur))
    {
        if (map[cur.i][cur.j] == 0)
            ++passed;
    }

    cout << "Result: " << passed << endl;

    return 0;
}