#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


bool isSafe(bool inc, int num1, int num2)
{
    if (num1 == num2)
        return false;
    if (abs(num1-num2) > 3)
        return false;
    if (inc && num1 > num2)
        return false;
    if (!inc && num1 < num2)
        return false;
    return true;
}

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
        bool safe = true;

        vector<int> seq;
        int aux;
        while (sin >> aux)
            seq.push_back(aux);

        // Check if is safe as is
        for (int i = 1; i < seq.size() && safe; ++i)
            safe &= isSafe(seq[1] - seq[0] > 0, seq[i-1], seq[i]);

        // Check if removing any element is safe
        vector<int> orig = seq;
        for (int j = 0; j < orig.size() && !safe; ++j)
        {
            seq = orig;
            seq.erase(seq.begin()+j);
            safe = true;
            for (int i = 1; i < seq.size() && safe; ++i)
                safe &= isSafe(seq[1] - seq[0] > 0, seq[i-1], seq[i]);
        }

        if (safe)
            ++total;
    }
    in.close();

    cout << "Result: " << total << endl;

    return 0;
}