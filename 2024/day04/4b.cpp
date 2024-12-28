#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Checks if any "x" pattern is valid
bool checkCross(const vector<string> & m, int i, int j)
{
    bool forslash = (m[i+1][j-1] == 'M' && m[i-1][j+1] == 'S') || (m[i+1][j-1] == 'S' && m[i-1][j+1] == 'M');
    bool backslash = (m[i-1][j-1] == 'M' && m[i+1][j+1] == 'S') || (m[i-1][j-1] == 'S' && m[i+1][j+1] == 'M');
    return forslash && backslash;
}

int main()
{
    ifstream in("input.txt");

    vector<string> soup;
    string aux;
    while (in >> aux)
        soup.push_back(aux);
    in.close();

    int total = 0;
    for (int i = 1; i < soup.size()-1; ++i)
    {
        for (int j = 1; j < soup[i].size()-1; ++j)
        {
            if (soup[i][j] == 'A' && checkCross(soup,i,j)) ++total;
        }
    }

    cout << "Result: " << total << endl;

    return 0;
}