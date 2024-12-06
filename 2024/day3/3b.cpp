#include <iostream>
#include <fstream>
#include <regex>

using namespace std;


int main()
{
    ifstream in("input.txt");

    regex rgx ("(mul\\(\\d{1,3},\\d{1,3}\\))|(do\\(\\))|(don't\\(\\).*?do\\(\\))");
    int total = 0;
    string line = "", full_file = "";

    while (getline(in, line))
        full_file += line;
    in.close();

    smatch match;
    while (regex_search(full_file, match, rgx))
    {
        string block = match.str();
        if (block.substr(0,3) == "mul")
        {
            int comma = block.find(',');
            int first = stoi(block.substr(4,comma-4));
            int second = stoi(block.substr(comma+1,block.size()-comma-1));
            total += first*second;

        }
        full_file = match.suffix().str();
    }

    cout << "Result: " << total << endl;

    return 0;
}