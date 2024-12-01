#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;


int main()
{
    string sequence = "", node = "", left = "", right = "", aux = "";
    unordered_map<string, pair<string, string>> map;
    ifstream fin("input.txt");
    fin >> sequence;
    while (fin >> node >> aux >> left >> right)
        map[node] = make_pair(left.substr(1,3), right.substr(0,3));
    fin.close();

    int steps = 0, i = 0;
    string currentNode = "AAA";
    while (currentNode != "ZZZ")
    {
        ++steps;
        currentNode = sequence[i] == 'L' ? map[currentNode].first : map[currentNode].second;
        i = (i + 1) % sequence.size();
    }

    cout << "Answer: " << steps << '\n';

    return 0;
}