#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main() 
{
    vector<pair<int,int>> galaxies;
    vector<int> emptyRows;
    ifstream fin("input.txt");
    string line; int row = 0;
    // Row 0
    getline(fin,line);
    vector<bool> emptyColsB(line.size(), true);
    int galIdx = line.find('#');
    if (galIdx == string::npos)
        emptyRows.push_back(row);
    while(galIdx != string::npos)
    {
        galaxies.emplace_back(row, galIdx);
        emptyColsB[galIdx] = false;
        galIdx = line.find('#', galIdx+1);
    }
    while(getline(fin,line))
    {
        ++row;
        galIdx = line.find('#');
        if (galIdx == string::npos)
            emptyRows.push_back(row);
        while(galIdx != string::npos)
        {
            galaxies.emplace_back(row, galIdx);
            emptyColsB[galIdx] = false;
            galIdx = line.find('#', galIdx+1);
        }
    }
    fin.close();

    vector<int> emptyCols;
    for (int i = 0; i < emptyColsB.size(); ++i)
        if (emptyColsB[i]) emptyCols.push_back(i);

    
    int total = 0;

    for (int i = 0; i < galaxies.size(); ++i)
        for (int j = i+1; j < galaxies.size(); ++j)
        {
            int rowDiff = abs(galaxies[i].first - galaxies[j].first);
            int colDiff = abs(galaxies[i].second - galaxies[j].second);
            int addRow = abs(lower_bound(emptyRows.begin(), emptyRows.end(), galaxies[i].first) - 
                             lower_bound(emptyRows.begin(), emptyRows.end(), galaxies[j].first));
            int addCols = abs(lower_bound(emptyCols.begin(), emptyCols.end(), galaxies[i].second) -
                             lower_bound(emptyCols.begin(), emptyCols.end(), galaxies[j].second));
            total += rowDiff + colDiff + addRow + addCols;
        }
    

    cout << "Answer: " << total << '\n';

    return 0;
}