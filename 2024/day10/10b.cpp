#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
using ii = pair<int, int>;

vector<ii> dirs = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int num(char c)
{
    return int(c) - int('0');
}

bool in_bounds(vector<vector<int>> const& map, int i, int j)
{
    return i >= 0 && i < map.size() && j >= 0 && j < map[i].size();
}

int main()
{
    ifstream in("input.txt");
    vector<vector<int>> map;
    vector<ii> trailHeads;
    string line;
    while (in >> line)
    {
        map.push_back(vector<int>());
        for (char c : line)
        {
            map.back().push_back(num(c));
            if (c == '0')
                trailHeads.push_back({ map.size()-1, map.back().size()-1 });
        }
    }
    in.close();

    int totalTrails = 0;
    for (ii const& th : trailHeads)
    {
        queue<ii> pending;
        pending.push(th);
        vector<vector<bool>> marks(map.size(), vector<bool>(map[0].size(), false));

        while (!pending.empty())
        {
            ii curr = pending.front();
            pending.pop();

            marks[curr.first][curr.second] = true;

            if (map[curr.first][curr.second] == 9)
                ++totalTrails;

            for (ii const& dir : dirs)
            {
                ii next = { curr.first + dir.first, curr.second + dir.second };
                if (in_bounds(map, next.first, next.second) &&
                    !marks[next.first][next.second] &&
                    map[next.first][next.second] - map[curr.first][curr.second] == 1)
                {
                    pending.push(next);
                }
            }
        }
    }

    cout << "Result: " << totalTrails << endl;

    return 0;
}