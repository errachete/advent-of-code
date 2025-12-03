#include <iostream>
#include <fstream>

using namespace std;
using llint = long long int;

int main()
{
    ifstream fin("input.txt");

    llint result = 0;
    string line = "";
    while (fin >> line)
    {
        string best = line.substr(0,12);
        for (int i = 1; i <= line.size() - 12; ++i)
        {
            for (int j = 0; j < 12; ++j)
            {
                if (line[i + j] > best[j])
                {
                    best = best.substr(0, j) + line.substr(i+j, 12 - j);
                    break;
                }
            }
        }
        result += stoll(best);
    }


    cout << "Result: " << result << '\n';
    return 0;
}