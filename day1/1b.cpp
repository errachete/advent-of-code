#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

const vector<string> numbers{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
                            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
    ifstream fin("input.txt");

    int total = 0;
    string line = "";
    while (getline(fin, line)) 
    {
        int minIdx = 10000, maxIdx = -1, first = -1, last = -1;
        
        for (int i = 0; i < numbers.size(); ++i)
        {
            int idx = line.find(numbers[i]);
            if (idx != string::npos) {
                if (idx < minIdx) {
                    minIdx = idx;
                    first = i % 10;
                }
            }
            idx = line.rfind(numbers[i]);
            if (idx != string::npos) {
                if (idx > maxIdx) {
                    maxIdx = idx;
                    last = i % 10;
                }
            }
        }
        
        total += first * 10 + last;
    }
    fin.close();

    cout << "Total: " << total << '\n';
    return 0;
}