#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;
using ii = pair<int,int>;


int main()
{
    ifstream fin("input.txt");

    string line;
    int row = 0;
    queue<ii> beam;
    unordered_map<int, vector<int>> mirrors;
    while(fin >> line) {
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == 'S')
                beam.push({i, row});
            else if (line[i] == '^')
            {
                if (mirrors.count(i) == 0)
                    mirrors[i] = vector<int>();
                mirrors[i].push_back(row);
            }
        }
        ++row;
    }
    fin.close();

    int result = 0;
    set<ii> used, rep_beams;
    while(!beam.empty())
    {
        ii cur = beam.front();
        beam.pop();
        int mir_col = cur.first;
        auto mir_row = upper_bound(mirrors[mir_col].begin(), mirrors[mir_col].end(), cur.second);
        if (mir_row != mirrors[mir_col].end())
        {
            ii left = {mir_col - 1, *mir_row};
            ii right = {mir_col + 1, *mir_row};
            if (rep_beams.count(left) == 0)
            {
                rep_beams.insert(left);
                beam.push({mir_col - 1, *mir_row});
            }
            if (rep_beams.count(right) == 0)
            {
                rep_beams.insert(right);
                beam.push({mir_col + 1, *mir_row});
            }
            if (used.count({mir_col, *mir_row}) == 0)
            {
                used.insert({mir_col, *mir_row});
                ++result;
            }
        }
    }

    cout << "Result: " << result << '\n';
    return 0;
}