#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;


// Map containing, for each number, all that must be after it
unordered_map<int, unordered_set<int>> rules;

bool rules_before (int num1, int num2)
{
    return rules[num1].count(num2);
}

int main()
{

    ifstream in("input.txt");
    string aux;

    // Read rules
    getline(in, aux);
    while (aux != "")
    {
        istringstream sin(aux);
        int pre, post;
        char c;
        sin >> pre >> c >> post;
        if (!rules.count(pre))
            rules[pre] = unordered_set<int>();
        rules[pre].insert(post);
        getline(in, aux);
    }

    // Read and process sequences
    int total = 0;
    while (getline(in, aux))
    {
        istringstream sin(aux);
        int num;
        char c;
        vector<int> seq;
        while (sin >> num >> c)
        {
            seq.push_back(num);
        }
        seq.push_back(num);

        bool correct = true;
        for (int i = 0; i < seq.size() && correct; ++i)
        {
            for (int j = i+1; j < seq.size() && correct; ++j)
            {
                if (!rules[seq[i]].count(seq[j]) && rules[seq[j]].count(seq[i]))
                    correct = false;
            }
        }
        if (correct)
            continue;

        // Fix incorrect
        sort(seq.begin(), seq.end(), rules_before);
        total += seq[seq.size()/2];

    }
    in.close();

    cout << "Result: " << total << endl;

    return 0;
}
