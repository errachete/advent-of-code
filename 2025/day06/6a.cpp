#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using llint = long long int;


int main()
{
    ifstream fin("input.txt");

    string line;
    vector<istringstream> sin;
    while(getline(fin, line))
        sin.push_back(istringstream(line));
    fin.close();

    llint result = 0;
    string op = "";
    while (sin.back() >> op)
    {
        llint part_res = (op == "+") ? 0 : 1;
        for (int i = 0; i < sin.size() - 1; ++i)
        {
            llint val;
            sin[i] >> val;
            if (op == "+")
                part_res += val;
            else if (op == "*")
                part_res *= val;
        }
        result += part_res;
    }

    cout << "Result: " << result << '\n';
    return 0;
}