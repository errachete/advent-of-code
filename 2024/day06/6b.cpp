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

int move(vector<vector<int>> & map, pos & cur, bool mark = true)
{
    // Mark current cell as visited with given direction
    if (mark)
        map[cur.i][cur.j] |= cur.d;
    // Check the next cell
    ii next = {cur.i + dir2pair[cur.d].first, cur.j + dir2pair[cur.d].second};
    if (next.first < 0 || next.first >= map.size() ||
        next.second < 0 || next.second >= map[0].size())
        return -1; // Outside
    if (repeated(map[next.first][next.second], cur.d))
        return 1; // Loop
    // If obstacle, turn right and try to move again
    if (map[next.first][next.second] == -1)
    {
        cur.d = turn90(cur.d);
        return move(map, cur, mark);
    }
    // If free cell, move to it
    cur.i = next.first;
    cur.j = next.second;
    return 0; // Moved normally
}

bool checkLoop(vector<vector<int>> map, pos cur)
{
    // Check if, starting from cur, the path is loop
    int movRes = move(map, cur, true);
    while (movRes == 0)
        movRes = move(map, cur, true);
    return movRes == 1;
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

    // For each cell in path, check if adding an obstacle in front of it results in a loop
    int count = 0;
    do {
        // Compute next cell without moving
        pos next = cur;
        if (move(map, next, false) != 0)
            continue;
        // Add obstacle if cell has not been used previously
        if (map[next.i][next.j] != 0)
            continue;
        map[next.i][next.j] = -1;
        // Check if loop
        if (checkLoop(map, cur))
            count++;
        // Restore previous value
        map[next.i][next.j] = 0;
    } while (move(map, cur, true) == 0);

    cout << "Resultados: " << count << endl;

    return 0;
}