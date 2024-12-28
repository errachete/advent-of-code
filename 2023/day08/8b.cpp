#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using llint = unsigned long long int;


llint gcd(llint a, llint b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int main()
{
    string sequence = "", node = "", left = "", right = "", aux = "";
    // Map of node -> (left, right )
    unordered_map<string, pair<string, string>> map;
    vector<string> currentNodes;
    ifstream fin("input.txt");
    fin >> sequence;
    while (fin >> node >> aux >> left >> right)
    {
        map[node] = make_pair(left.substr(1,3), right.substr(0,3));
        if (node.back() == 'A')
            currentNodes.push_back(node);
    }
    fin.close();

    // Calculate loop size, Z eq. class and remainders
    vector<int> rem, loopSize, zClass;
    for (int i = 0; i < currentNodes.size(); ++i)
    {
        // Store node and seqIndex as key, with number of steps as value
        unordered_map<string, int> waypoints;
        int steps = 0, seqIdx = 0;
        // Advance following sequence until repeating node with seqIdx (start of loop)
        while (!waypoints.count(currentNodes[i]+to_string(seqIdx)))
        {
            waypoints[currentNodes[i]+to_string(seqIdx)] = steps;
            if (currentNodes[i].back() == 'Z')
                zClass.push_back(steps);
            currentNodes[i] = sequence[seqIdx] == 'L' ? map[currentNodes[i]].first : map[currentNodes[i]].second;
            ++steps;
            seqIdx = (seqIdx + 1) % sequence.size();
        }
        // The current position is repeated, the loop is complete
        // Remainder size is the number of steps given when passing the repeated node for the first time
        rem.push_back(waypoints[currentNodes[i]+to_string(seqIdx)]);
        // Loop size is the total number of steps minus the remainder
        loopSize.push_back(steps - rem.back());
    }

    // After watching the results, seems that loopSize = zClass for all the sequences
    // The solution x is the solution of the system x = zClass mod loopSize
    // That is, the LCM of all the numbers

    llint result = zClass[0];
    for (int i = 1; i < zClass.size(); ++i)
    {
        result = result * zClass[i] / gcd(result, zClass[i]);
    }
    cout << "Answer: " << result << '\n';

    return 0;
}