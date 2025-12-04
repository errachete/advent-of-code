#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using ii = pair<int,int>;

const vector<ii> dirs = {{-1, -1},   {-1, 0},    {-1, 1},
                                    {0, -1},                {0, 1},
                                    {1, -1},    {1, 0},     {1, 1}};

ii operator+(const ii & a, const ii & b)
{
    return {a.first + b.first, a.second + b.second};
}

bool inside(const vector<vector<char>> & diag, ii pos)
{
    return pos.first >= 0 && pos.first < diag.size() &&
           pos.second >= 0 && pos.second < diag[pos.first].size();
}

int count(const vector<vector<char>> & diag, ii pos)
{
    int total = 0;
    for (const auto & dir : dirs)
    {
        ii cur = pos + dir;
        if (inside(diag, cur) && diag[cur.first][cur.second] == '@')
            ++total;
    }
    return total;
}

int main()
{
    ifstream fin("input.txt");

    vector<vector<char>> diag = vector<vector<char>>(0);
    string line = "";
    while (fin >> line)
        diag.push_back(vector<char>(line.begin(), line.end()));
    fin.close();

    int result = 0;
    for (int i = 0; i < diag.size(); ++i)
    for (int j = 0; j < diag[i].size(); ++j)
    {
        if (diag[i][j] == '@' && count(diag, {i,j}) < 4)
            ++result;
    }

    cout << "Result: " << result << '\n';
    return 0;
}