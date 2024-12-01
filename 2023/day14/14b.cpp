#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

ostream &operator<<(ostream & out, const vector<vector<char>> & v)
{
    for (auto r : v) 
    {
        for (auto c : r)
            out << c;
        out << '\n';
    }
    out << '\n';
    return out;
}

void tiltNorth(vector<vector<char>> & plat)
{
    for (int j = 0; j < plat[0].size(); ++j)
    {
        int lim = 0;
        for (int i = 0; i < plat.size(); ++i)
        {
            if (plat[i][j] == 'O')
            {
                plat[i][j] = '.';
                plat[lim][j] = 'O';
                ++lim;
            }
            else if (plat[i][j] == '#')
            {
                lim = i + 1;
            }
        }
    }
}

void tiltEast(vector<vector<char>> & plat)
{
    for (int i = 0; i < plat.size(); ++i)
    {
        int lim = plat[i].size() - 1;
        for (int j = plat[i].size() - 1; j >= 0; --j)
        {
            if (plat[i][j] == 'O')
            {
                plat[i][j] = '.';
                plat[i][lim] = 'O';
                --lim;
            }
            else if (plat[i][j] == '#')
            {
                lim = j - 1;
            }
        }
    }
}

void tiltSouth(vector<vector<char>> & plat)
{
    for (int j = 0; j < plat[0].size(); ++j)
    {
        int lim = plat.size() - 1;
        for (int i = plat.size() - 1; i >= 0; --i)
        {
            if (plat[i][j] == 'O')
            {
                plat[i][j] = '.';
                plat[lim][j] = 'O';
                --lim;
            }
            else if (plat[i][j] == '#')
            {
                lim = i - 1;
            }
        }
    }
}

void tiltWest(vector<vector<char>> & plat)
{
    for (int i = 0; i < plat.size(); ++i)
    {
        int lim = 0;
        for (int j = 0; j < plat[i].size(); ++j)
        {
            if (plat[i][j] == 'O')
            {
                plat[i][j] = '.';
                plat[i][lim] = 'O';
                ++lim;
            }
            else if (plat[i][j] == '#')
            {
                lim = j + 1;
            }
        }
    }
}

void cycle(vector<vector<char>> & plat) 
{
    tiltNorth(plat);
    tiltWest(plat);
    tiltSouth(plat);
    tiltEast(plat);
}

int load(const vector<vector<char>> & plat)
{
    int rowLoad = plat.size(), load = 0;
    for (int i = 0; i < plat.size(); ++i)
    {
        for (int j = 0; j < plat[i].size(); ++j)
        {
            if (plat[i][j] == 'O')
                load += rowLoad;
        }
        --rowLoad;
    }
    return load;
}

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

    cout << plat;

    // Solve
    // Iterate until reaching a cycle
    vector<vector<vector<char>>> seq(1, plat);
    set<vector<vector<char>>> prev;
    prev.insert(plat);
    cycle(plat);
    while (!prev.count(plat)) 
    {
        seq.push_back(plat);
        prev.insert(plat);
        cycle(plat);
    }

    // Find previous ocurrence
    int cyPoint = seq.size() - 1;
    while (cyPoint >= 0 && seq[cyPoint] != plat)
        --cyPoint;
    int cySize = seq.size() - cyPoint;

    // Find equivalence class of target cycle: 1000000000
    int target = 1000000000;
    int eq = (target - cyPoint) % cySize + cyPoint;

    cout << "Answer: " << load(seq[eq]) << '\n';

    return 0;
}