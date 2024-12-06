#include <iostream>
#include <fstream>
#include <regex>

using namespace std;


int main()
{
    ifstream in("input.txt");

    regex rgx ("mul\\(\\d{1,3},\\d{1,3}\\)");
    int total = 0;
    string line = "";
    while (getline(in, line))
    {
        smatch match;
        while (regex_search(line, match, rgx))
        {
            string res = match.str();
            int comma = res.find(',');
            int first = stoi(res.substr(4,comma-4));
            int second = stoi(res.substr(comma+1,res.size()-comma-1));
            total += first*second;
            line = match.suffix().str();
        }
    }
    in.close();

    cout << "Result: " << total << endl;

    return 0;
}