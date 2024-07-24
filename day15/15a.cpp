#include <iostream>
#include <fstream>

using namespace std;

int hashFun(const string & s)
{
    int value = 0;
    for (char c : s)
    {
        value += int(c);
        value *= 17;
        value %= 256;
    }
    return value;
}

int main() 
{
    ifstream fin("input.txt");
    string item;
    int total;
    while (getline(fin, item, ','))
    {
        total += hashFun(item);
    }
    fin.close();

    cout << "Answer: " << total << '\n';

    return 0;
}