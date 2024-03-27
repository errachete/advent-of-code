#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool healthCheck(int idx, const string & hotsp, const vector<int> & pattern)
{
    int i = 0, p = 0, acum = 0;
    while (i < idx)
    {
        // If point and some accumulated, check it is correct
        if (hotsp[i] == '.' && acum != 0) 
        {
            // No more patterns to match or matching is not right
            if (p == pattern.size() || acum != pattern[p]) 
                return false;
            else 
            {
                acum = 0;
                ++p;
                ++i;
            }
        }
        else if (hotsp[i] == '.')
        {
            ++i;
        }
        else
        {
            ++acum;
            ++i;
        }
    }

    // If hotsp is fully determined
    if (i == hotsp.size())
    {
        if (acum == 0)
            return p == pattern.size();
        else
            return p == pattern.size()-1 && acum == pattern[p];
    }

    return true;
}

int evaluate(int idx, string hotsp, const vector<int> & pattern)
{
    if (idx == hotsp.size())
        return 1;
    
    if (hotsp[idx] == '?')
    {
        int total = 0;
        hotsp[idx] = '.';
        if (healthCheck(idx+1, hotsp, pattern))
            total += evaluate(idx+1, hotsp, pattern);
        hotsp[idx] = '#';
        if (healthCheck(idx+1, hotsp, pattern))
            total += evaluate(idx+1, hotsp, pattern);
        return total;
    }

    if (healthCheck(idx+1, hotsp, pattern))
        return evaluate(idx+1, hotsp, pattern);
    
    return 0;
}

int main() 
{
    ifstream fin("input.txt");
    int total = 0;
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

        // Solve case
        total += evaluate(0, hotsp, pattern);
    }
    fin.close();

    cout << "Answer: " << total << '\n';

    return 0;
}