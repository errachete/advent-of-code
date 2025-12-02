#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int result = 0;
    char dir;
    int value, cur = 50;
    while (fin >> dir >> value)
    {
        if (dir == 'L')
        {
            cur -= value;
            cur = (cur + 100) % 100;
        }
        else // dir == 'R'
        {
            cur += value;
            cur = cur % 100;
        }

        if (cur == 0) ++result;
    }
    fin.close();

    cout << "Result: " << result << '\n';
    return 0;
}