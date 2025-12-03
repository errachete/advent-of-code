#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int result = 0;
    string line = "";
    while (fin >> line)
    {
        char max = line[0], next = line[1];
        for (int i = 1; i < line.size(); ++i)
        {
            if (line[i] > max && i < line.size() - 1)
            {
                max = line[i];
                next = line[i+1];
            }
            else if (line[i] > next)
            {
                next = line[i];
            }
        }
        result += stoi(string("") + max + next);
    }


    cout << "Result: " << result << '\n';
    return 0;
}