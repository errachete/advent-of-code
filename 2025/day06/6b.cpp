#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;
using llint = long long int;


llint operate(const vector<llint>& numbers, char op)
{
    llint result = (op == '+') ? 0 : 1;
    for (const auto& num : numbers)
    {
        if (op == '+')
            result += num;
        else
            result *= num;
    }
    return result;
}


int main()
{
    ifstream fin("input.txt");

    string line;
    vector<string> homework;
    while(getline(fin, line))
        homework.push_back(line);
    fin.close();

    llint result = 0;
    vector<llint> numbers;
    char op = '+';
    for(int j = homework[0].size()-1; j >= 0; --j)
    {
        string number = "";
        for (int i = 0; i < homework.size(); ++i)
        {
            if (isdigit(homework[i][j]))
                number.push_back(homework[i][j]);
            else if (homework[i][j] == '+' || homework[i][j] == '*')
                op = homework[i][j];
        }
        if (!number.empty())
            numbers.push_back(stoll(number));
        else
        {
            result += operate(numbers, op);
            numbers.clear();
        }
    }
    result += operate(numbers, op);

    cout << "Result: " << result << '\n';
    return 0;
}