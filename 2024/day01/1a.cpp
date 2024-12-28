#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


int main()
{
    vector<int> list1;
    vector<int> list2;

    // Read both lists
    int aux;
    ifstream in("input.txt");
    while (in >> aux)
    {
        list1.push_back(aux);
        in >> aux;
        list2.push_back(aux);
    }
    in.close();

    // Sort the lists
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    // Iterate the lists adding the differences between the two numbers
    int total = 0;
    for (int i = 0; i < list1.size(); ++i)
        total += abs(list1[i] - list2[i]);

    cout << "Result: " << total << endl;

    return 0;
}