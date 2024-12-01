#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int number = 0, card = 0;
    string aux = "";
    vector<int> numCards(219, 1);
    while (fin >> aux >> card >> aux) // Card >> X >> : 
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

        for (int i = 0; i < inters.size() && card+i < numCards.size(); ++i)
        {
            numCards[card+i] += numCards[card-1];
        }
    }
    fin.close();

    cout << "Answer: " << accumulate(numCards.begin(), numCards.end(), 0) << '\n';
    return 0;
}