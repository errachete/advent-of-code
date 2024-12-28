#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;


int main()
{
    // Two maps containing <number, appearances>
    unordered_map<int,int> counts1;
    unordered_map<int,int> counts2;

    // Read both lists counting the number of times each number appears
    int aux;
    ifstream in("input.txt");
    while (in >> aux)
    {
        if (!counts1.count(aux))
            counts1[aux] = 0;
        ++counts1[aux];

        in >> aux;

        if (!counts2.count(aux))
            counts2[aux] = 0;
        ++counts2[aux];
    }
    in.close();

    // Iterate the first map checking count of the number in both
    int total = 0;
    for (auto a : counts1)
        if (counts2.count(a.first))
            total += a.first * counts2[a.first] * a.second;

    cout << "Result: " << total << endl;

    return 0;
}