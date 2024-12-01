#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int total = 0, number = 0;
    string aux = "";
    while (fin >> aux >> aux) // Card X: 
    {
        vector<int> winning(10, 0);
        vector<int> having(25, 0);
        for (int & w : winning)
            fin >> w;
        fin >> aux; // |
        for (int & h : having)
            fin >> h;

        sort(winning.begin(), winning.end());
        sort(having.begin(), having.end());

        vector<int> inters(25,0);
        auto intEnd = set_intersection(winning.begin(), winning.end(), having.begin(), having.end(), inters.begin());
        inters.resize(intEnd - inters.begin());

        if (inters.size() > 0)
            total += pow(2, inters.size()-1);
    }
    fin.close();

    cout << "Answer: " << total << '\n';
    return 0;
}