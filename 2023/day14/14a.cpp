#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() 
{
    ifstream fin("input.txt");
    string line;
    vector<vector<char>> plat;
    while (getline(fin, line))
    {
        plat.push_back(vector<char>());
        for(char c : line)
            plat.back().push_back(c);
    }
    fin.close();
    
    // Solve
    // Iterate by columns counting rocks
    int total = 0, maxWeight = plat.size();
    for (int j = 0; j < plat[0].size(); ++j) 
    {
        int limWeight = maxWeight;
        for (int i = 0; i < plat.size(); ++i) 
        {
            if (plat[i][j] == 'O') 
            {
                total += limWeight;
                --limWeight;
            }
            else if (plat[i][j] == '#')
            {
                limWeight = maxWeight - i - 1;
            }
        }
    }

    cout << "Answer: " << total << '\n';

    return 0;
}