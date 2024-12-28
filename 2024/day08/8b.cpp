#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;
using ii = pair<int, int>;


bool inBounds(int i, int j, const vector<vector<bool>>& map)
{
    return i >= 0 && i < map.size() && j >= 0 && j < map[i].size();
}

int main()
{
    ifstream in("input.txt");
    vector<vector<bool>> map;
    unordered_map<char, vector<ii>> antList;
    string aux;
    while (getline(in, aux))
    {
        map.push_back(vector<bool>(aux.size(), false));
        for (int i = 0; i < aux.size(); ++i)
        {
            if (aux[i] != '.')
            {
                if (antList.count(aux[i]) == 0)
                    antList[aux[i]] = vector<ii>();
                antList[aux[i]].push_back(ii(map.size()-1, i));
            }
        }
    }
    in.close();

    int antiCount = 0;
    for (auto ant : antList)
    {
        for (int i = 0; i < ant.second.size() && ant.second.size() != 1; ++i)
        {

            if (!map[ant.second[i].first][ant.second[i].second])
            {
                map[ant.second[i].first][ant.second[i].second] = true;
                ++antiCount;
            }

            for (int j = i+1; j < ant.second.size(); ++j)
            {
                int iDiff = ant.second[i].first - ant.second[j].first;
                int jDiff = ant.second[i].second - ant.second[j].second;

                int k = 1;
                int antiI = ant.second[i].first + iDiff*k;
                int antiJ = ant.second[i].second + jDiff*k;
                while (inBounds(antiI, antiJ, map))
                {
                    if (!map[antiI][antiJ])
                    {
                        map[antiI][antiJ] = true;
                        ++antiCount;
                    }
                    ++k;
                    antiI = ant.second[i].first + iDiff*k;
                    antiJ = ant.second[i].second + jDiff*k;
                }

                k = 1;
                antiI = ant.second[j].first - iDiff*k;
                antiJ = ant.second[j].second - jDiff*k;
                while (inBounds(antiI, antiJ, map))
                {
                    if (!map[antiI][antiJ])
                    {
                        map[antiI][antiJ] = true;
                        ++antiCount;
                    }
                    ++k;
                    antiI = ant.second[j].first - iDiff*k;
                    antiJ = ant.second[j].second - jDiff*k;
                }
            }
        }
    }

    cout << "Result: " << antiCount << endl;

    return 0;
}