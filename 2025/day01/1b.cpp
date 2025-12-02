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
        if (value >= 100)
        {
            result += value / 100;
            value = value % 100;
        }

        if (value == 0)
            continue;

        if (cur == 0)
        {
            if (dir == 'L')
                cur = 100 - value;
            else // dir == 'R'
                cur = value;
        }
        else
        {
            if (dir == 'L')
                cur -= value;
            else // dir == 'R'
                cur += value;

            if (cur <= 0 || cur >= 100)
            {
                ++result;
                cur = (cur + 100) % 100;
            }
        }
    }
    fin.close();

    cout << "Result: " << result << '\n';
    return 0;
}