#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using llint = long long int;
using ii = pair<int,int>;

llint area(const ii &p1, const ii &p2)
{
    llint side_1 = abs(p1.first - p2.first) + 1;
    llint side_2 = abs(p1.second - p2.second) + 1;
    return side_1 * side_2;
}

int main()
{
    ifstream fin("input.txt");

    vector<ii> red_tiles;
    int x, y;
    char aux;
    while (fin >> x >> aux >> y)
        red_tiles.emplace_back(x, y);
    fin.close();

    llint result = 0;
    for (int i = 0; i < red_tiles.size(); ++i)
        for (int j = i+1; j < red_tiles.size(); ++j)
        {
            llint a = area(red_tiles[i], red_tiles[j]);
            if (a > result)
                result = a;
        }

    cout << "Result: " << result << '\n';
    return 0;
}