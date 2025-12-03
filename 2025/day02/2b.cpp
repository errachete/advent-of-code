#include <iostream>
#include <fstream>

using namespace std;
using llint = long long int;

bool pattern(llint n)
{
    string s = to_string(n);
    for (int i = 1; i <= s.size() / 2; ++i)
    {
        string pattern = s.substr(0, i);
        if (s.size() % pattern.size() != 0)
            continue;
        int j = pattern.size();
        while (j < s.size() && s.substr(j, pattern.size()) == pattern)
            j += pattern.size();
        if (j == s.size())
            return true;
    }
    return false;
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