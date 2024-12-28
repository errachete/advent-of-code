#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;
using ii = pair<int, int>;


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
        for (int i = 0; i < ant.second.size(); ++i)
        {
            for (int j = i+1; j < ant.second.size(); ++j)
            {
                int iDiff = ant.second[i].first - ant.second[j].first;
                int jDiff = ant.second[i].second - ant.second[j].second;

                int antiI = ant.second[i].first + iDiff;
                int antiJ = ant.second[i].second + jDiff;

                if (antiI >= 0 && antiI < map.size() && antiJ >= 0 && antiJ < map[antiI].size() && !map[antiI][antiJ])
                {
                    map[antiI][antiJ] = true;
                    ++antiCount;
                }

                antiI = ant.second[j].first - iDiff;
                antiJ = ant.second[j].second - jDiff;

                if (antiI >= 0 && antiI < map.size() && antiJ >= 0 && antiJ < map[antiI].size() && !map[antiI][antiJ])
                {
                    map[antiI][antiJ] = true;
                    ++antiCount;
                }
            }
        }
    }

    cout << "Result: " << antiCount << endl;

    return 0;
}