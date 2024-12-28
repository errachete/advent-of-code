#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
using lli = long long int;


lli concat(lli num1, int num2)
{
    int num0 = log10(num2) + 1;
    return num1 * pow(10, num0) + num2;
}

bool testOperator(vector<int> const& ops, int i, lli partRes, lli res)
{
    // As only + and * are used, if partRes is bigger than res, it will never be possible to reach res
    if (partRes > res)
        return false;
    // If we reached the end of the operations, check if the result is the expected
    if (i == ops.size())
        return partRes == res;
    // In any other case, check if possible with each operator
    return testOperator(ops, i + 1, partRes + ops[i], res) ||
            testOperator(ops, i + 1, partRes * ops[i], res) ||
            testOperator(ops, i + 1, concat(partRes, ops[i]), res);
}

int main()
{
    ifstream in("input.txt");
    lli result, total = 0;
    while (in >> result)
    {
        char aux;
        vector<int> ops;
        int num;
        in.get(aux); // :
        while (aux != '\n')
        {
            in >> num;
            ops.push_back(num);
            in.get(aux);
        }

        if (testOperator(ops, 1, ops[0], result))
        {
            total += result;
        }
    }
    in.close();

    cout << "Result: " << total << endl;

    return 0;
}