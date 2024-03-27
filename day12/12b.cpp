#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using llint = long long int;

int fill(int iHot, string & hotsp, int hotSize)
{
    int count = 0;
    while (iHot < hotsp.size())
    {
        if (hotsp[iHot] == '#')
        {
            ++count;
            if (count > hotSize)
                return -1;
        }
        else if (hotsp[iHot] == '.')
        {
            // Success
            if (count == hotSize)
                return iHot;
            else
                return -1;
        }
        else // '?'
        {
            // If too short, put '#'
            if (count < hotSize)
            {
                hotsp[iHot] = '#';
                ++count;
            }
            else
            {
                hotsp[iHot] = '.';
                return iHot;
            }
        }
        ++iHot;
    }

    // If end of chain, check if matched
    if (count == hotSize)
        return iHot;
    else
        return -1;
}

llint evaluate(int iHot, string hotsp, int iPat, const vector<int> & pattern, vector<vector<llint>> & dp)
{
    // If end of chain
    if (iHot >= hotsp.size())
    {
        if (iPat == pattern.size())
            return 1;
        else
            return 0;
    }

    // If all patterns matched, check if more '#' are left
    if (iPat == pattern.size())
    {
        if (hotsp.find("#", iHot) == string::npos)
            return 1;
        else
            return 0;
    }

    // If already computed, directly return the number
    if (dp[iHot][iPat] != -1)
        return dp[iHot][iPat];

    // If '.', advance without adding any pattern match
    if (hotsp[iHot] == '.')
    {
        dp[iHot][iPat] = evaluate(iHot+1, hotsp, iPat, pattern, dp);
        return dp[iHot][iPat];
    }
    else if (hotsp[iHot] == '#')
    {
        int nHot = fill(iHot, hotsp, pattern[iPat]);
        if (nHot == -1)
            dp[iHot][iPat] = 0;
        else
            dp[iHot][iPat] = evaluate(nHot+1, hotsp, iPat+1, pattern, dp);
        return dp[iHot][iPat];
    }
    else // '?'
    {
        // Using '.'
        hotsp[iHot] = '.';
        llint point = evaluate(iHot+1, hotsp, iPat, pattern, dp);
        // Using '#'
        hotsp[iHot] = '?';
        llint hash = 0;
        int nHot = fill(iHot, hotsp, pattern[iPat]);
        if (nHot != -1)
            hash = evaluate(nHot+1, hotsp, iPat+1, pattern, dp);
        dp[iHot][iPat] = point + hash;
        return dp[iHot][iPat];
    }
}

int main() 
{
    ifstream fin("input.txt");
    llint total = 0;
    char aux;
    string line, hotsp;
    vector<int> pattern;
    while (getline(fin, line))
    {
        // Read case
        istringstream sline(line);
        sline >> hotsp;
        int num = 0;
        pattern.clear();
        while (sline >> num) {
            pattern.push_back(num);
            sline.get(aux);
        }

        // Unfold
        string uHotsp = hotsp;
        vector<int> uPattern = pattern;
        for(int i = 1; i < 5; ++i)
        {
            uHotsp += '?' + hotsp;
            uPattern.insert(uPattern.end(), pattern.begin(), pattern.end());
        }

        // Prepare DP table
        vector<vector<llint>> dp(uHotsp.size(), vector<llint>(uPattern.size(), -1));

        // Solve case
        llint caseRes = evaluate(0, uHotsp, 0, uPattern, dp);
        cout << caseRes << '\n';
        total += caseRes;
    }
    fin.close();

    cout << "Answer: " << total << '\n';

    return 0;
}