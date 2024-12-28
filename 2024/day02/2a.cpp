#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main()
{
    ifstream in("input.txt");
    string str;
    int total = 0;
    // Read line by line
    while (getline(in,str))
    {
        // Process each line
        istringstream sin(str);
        int first, second;
        sin >> first >> second;
        // Evaluate first pair
        bool safe = (first != second) && (abs(first - second) <= 3);
        bool inc = second > first;
        // Iterate the rest of the line
        first = second;
        while (safe && sin >> second)
        {
            safe = (first != second) && (abs(first - second) <= 3) &&
                ((inc && second > first) || (!inc && second < first));
            first = second;
        }
        if (safe)
            ++total;
    }
    in.close();

    cout << "Result: " << total << endl;

    return 0;
}