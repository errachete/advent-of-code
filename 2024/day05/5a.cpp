#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


int main()
{
    // Map containing, for each number, all that must be after it
    unordered_map<int, unordered_set<int>> rules;
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
        for (int i = 0; i < seq.size()-1 && correct; ++i)
        {
            // It is enough to check consecutive numbers, because all numbers
            // in the sequence are in the rules, and thus, there is only one
            // correct way to order them concatenating rules
            if (!rules[seq[i]].count(seq[i+1]))
                correct = false;
        }
        if (correct)
            total += seq[seq.size()/2];
    }
    in.close();

    cout << "Result: " << total << endl;

    return 0;
}
