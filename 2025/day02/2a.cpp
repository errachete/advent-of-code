#include <iostream>
#include <fstream>

using namespace std;
using llint = long long int;

bool pattern(llint n)
{
    string s = to_string(n);
    if (s.size() % 2 != 0)
        return false;
    else
        return s.substr(0, s.size() / 2) == s.substr(s.size() / 2);
}

int main()
{
    ifstream fin("input.txt");

    llint result = 0;
    llint start, end;
    char aux;
    do
    {
        fin >> start >> aux >> end;
        for (llint n = start; n <= end; ++n)
        {
            if (pattern(n))
                result += n;
        }
    } while (fin >> aux);

    fin.close();

    cout << "Result: " << result << '\n';
    return 0;
}