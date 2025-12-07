#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;
using llint = long long int;
using ii = pair<int,int>;

llint count_endings(const ii & beam, unordered_map<int, vector<int>> & mirrors, map<ii, llint> & endings)
{
    int mir_col = beam.first;
    auto mir_row = upper_bound(mirrors[mir_col].begin(), mirrors[mir_col].end(), beam.second);
    ii mir = {mir_col, (mir_row != mirrors[mir_col].end()) ? *mir_row : -1};

    if (mir.second == -1)
    {
        endings[mir] = 1;
        return endings[mir];
    }

    if (endings[mir] != -1)
        return endings[mir];

    ii left = {mir_col - 1, *mir_row};
    ii right = {mir_col + 1, *mir_row};
    endings[mir] = count_endings(left, mirrors, endings) + count_endings(right, mirrors, endings);
    return endings[mir];
}


int main()
{
    ifstream fin("input.txt");

    string line;
    int row = 0;
    ii beam;
    unordered_map<int, vector<int>> mirrors;
    map<ii, llint> endings;
    while(fin >> line) {
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == 'S')
                beam = {i, row};
            else if (line[i] == '^')
            {
                if (mirrors.count(i) == 0)
                    mirrors[i] = vector<int>();
                mirrors[i].push_back(row);
                endings[{i, row}] = -1;
            }
        }
        ++row;
    }
    fin.close();

    llint result = count_endings(beam, mirrors, endings);

    cout << "Result: " << result << '\n';
    return 0;
}