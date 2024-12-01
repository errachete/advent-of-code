#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


int main()
{
    ifstream fin("input.txt");
    string line;
    int total = 0;
    while(getline(fin, line))
    {
        // Read sequence
        istringstream sline(line);
        vector<vector<int>> sqs(1, vector<int>());
        int num;
        while (sline >> num)
            sqs[0].push_back(num);

        // Iterate sequences until all zero condition is reached
        bool allZeroes = false;
        while (!allZeroes)
        {
            allZeroes = true;
            vector<int> subseq, seq = sqs.back();
            for (int i = 1; i < seq.size(); ++i)
            {
                int value = seq[i] - seq[i-1];
                if (value != 0) allZeroes = false;
                subseq.push_back(value);
            }
            sqs.push_back(subseq);
        }

        // Construct new number
        for (int i = 0; i < sqs.size(); ++i)
            total += sqs[i].back();

    }

    cout << "Answer: " << total << '\n';

    return 0;
}