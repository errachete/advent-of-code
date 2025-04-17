#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;
using llint = long long int;

int DEPTH = 25;


int numDigits(llint n)
{
    int digits = 0;
    while (n > 0)
    {
        n /= 10;
        ++digits;
    }
    return digits;
}

int numStones(unordered_map<llint, vector<int>> & dp, llint n, int steps)
{
    if (!dp.count(n))
        dp[n] = vector<int>(DEPTH+1, -1);

    if (steps == 0)
        dp[n][steps] = 1;
    else if (dp[n][steps] == -1)
    {
        if (n == 0)
            dp[n][steps] = numStones(dp, 1, steps - 1);
        else if (numDigits(n) % 2 == 0)
        {
            string numStr = to_string(n);
            int firstHalf = stoi(numStr.substr(0, numStr.size() / 2));
            int secondHalf = stoi(numStr.substr(numStr.size() / 2));
            dp[n][steps] = numStones(dp, firstHalf, steps - 1) + numStones(dp, secondHalf, steps - 1);
        }
        else
        {
            dp[n][steps] = numStones(dp, n*2024, steps - 1);
        }
    }

    return dp[n][steps];
}

int main()
{
    ifstream in("input.txt");
    vector<int> startStones;
    int n;
    while (in >> n)
        startStones.push_back(n);
    in.close();

    unordered_map<llint, vector<int>> dp;

    int totalStones = 0;
    for (int i = 0; i < startStones.size(); ++i)
        totalStones += numStones(dp, startStones[i], DEPTH);

    cout << "Result: " << totalStones << endl;

    return 0;
}