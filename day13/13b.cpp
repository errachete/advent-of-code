#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

bool is2power(int a) 
{
    float logRes = log(a)/log(2);
    return a != 0 && logRes == int(logRes);
}

int solveCase(const vector<vector<bool>> & map)
{
    int result = 0;
    // Construct vector of integer interpretation of rows
    vector<int> rowInt = vector<int>(map.size(), 0);
    vector<int> posMirr = vector<int>();
    for (int i = 0; i < rowInt.size(); ++i)
    {
        rowInt[i] = accumulate(map[i].begin(), map[i].end(), 0, [](int x, int y) {return (x << 1) + y;});
        if (i > 0 && (rowInt[i] == rowInt[i-1] || is2power(rowInt[i]^rowInt[i-1])))
            posMirr.push_back(i);
    }

    // If there where possible mirrors, check them
    for(int i = 0; i < posMirr.size(); ++i)
    {
        bool smudge = false;
        int up = posMirr[i]-1;
        int down = posMirr[i];
        while(up >= 0 && down < rowInt.size() && 
            (rowInt[up]==rowInt[down] || (!smudge && is2power(rowInt[up]^rowInt[down])))) 
        {
            if (rowInt[up] != rowInt[down])
                smudge = true;
            --up;
            ++down;
        }
        if ((up < 0 || down >= rowInt.size()) && smudge) {
            return 100*posMirr[i];
        }
    }

    // Search for vertical mirrors
    // Transpose matrix
    vector<vector<bool>> tMap(map[0].size(), vector<bool>(map.size()));
    for (int i = 0; i < map.size(); ++i)
        for (int j = 0; j < map[i].size(); ++j)
            tMap[j][i] = map[i][j];
    
    // Construct vector of integer interpretation of columns
    vector<int> colInt = vector<int>(tMap.size(), 0);
    posMirr.clear();
    for (int i = 0; i < colInt.size(); ++i)
    {
        colInt[i] = accumulate(tMap[i].begin(), tMap[i].end(), 0, [](int x, int y) {return (x << 1) + y;});
        if (i > 0 && (colInt[i] == colInt[i-1] || is2power(colInt[i]^colInt[i-1])))
            posMirr.push_back(i);
    }

    // If there where possible mirrors, check them
    for(int i = 0; i < posMirr.size(); ++i)
    {
        bool smudge = false;
        int left = posMirr[i]-1;
        int right = posMirr[i];
        while(left >= 0 && right < colInt.size() && 
            (colInt[left]==colInt[right] || (!smudge && is2power(colInt[left]^colInt[right])))) 
        {
            if (colInt[left] != colInt[right])
                smudge = true;
            --left;
            ++right;
        }
        if ((left < 0 || right >= colInt.size()) && smudge) {
            return posMirr[i];
        }
    }

    return 0;
}

int main() 
{
    ifstream fin("input.txt");
    int total = 0;
    string line;
    vector<vector<bool>> map;
    while(getline(fin, line))
    {
        // Part of case, append and continue reading
        if (line != "")
        {
            map.push_back(vector<bool>());
            for (int i = 0; i < line.size(); ++i)
                map.back().push_back(line[i]=='#');
        }
        // End of case, process and reset
        else
        {
            total += solveCase(map);
            map.clear();
        }
    }    
    fin.close();
    
    // Solve last case
    total += solveCase(map);

    cout << "Answer: " << total << '\n';

    return 0;
}