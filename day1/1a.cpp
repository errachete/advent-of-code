#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int total = 0;
    string line = "";
    while (getline(fin, line)) 
    {
        string number = "";
        for (int i = 0; i < line.size(); ++i) {
            if (isdigit(line[i])) 
            {
                number.push_back(line[i]);
                break;
            }
        }
        for (int i = line.size()-1; i >= 0; --i) {
            if (isdigit(line[i]))
            {
                number.push_back(line[i]);
                break;
            }
        }

        total += stoi(number);
    }
    fin.close();

    cout << "Total: " << total << '\n';
    return 0;
}