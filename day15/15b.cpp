#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int hashFun(const string & s)
{
    int value = 0;
    for (char c : s)
    {
        value += int(c);
        value *= 17;
        value %= 256;
    }
    return value;
}

int focusPower(const vector<vector<pair<string,int>>> & boxes)
{
    int total = 0;
    for (int i = 0; i < boxes.size(); ++i)
        for (int j = 0; j < boxes[i].size(); ++j)
            total += (i+1) * (j+1) * boxes[i][j].second;
    return total;
}

int main() 
{
    ifstream fin("input.txt");
    string item;
    vector<vector<pair<string, int>>> boxes (256, vector<pair<string,int>>());
    while (getline(fin, item, ','))
    {
        // Read item
        istringstream in(item);
        char aux;
        item = "";
        in.get(aux);
        while (aux != '-' && aux != '=')
        {
            item.push_back(aux);
            in.get(aux);
        }

        // Process item
        int box = hashFun(item);
        if (aux == '-')
        {
            for (int i = 0; i < boxes[box].size(); ++i) 
                if (boxes[box][i].first == item)
                {
                    boxes[box].erase(boxes[box].begin()+i);
                    break;
                }
        }
        else if (aux == '=')
        {
            bool found = false;
            for (int i = 0; i < boxes[box].size() && !found; ++i)
                if (boxes[box][i].first == item)
                {
                    in >> boxes[box][i].second;
                    found = true;
                }
            if (!found)
            {
                int num = 0;
                in >> num;
                boxes[box].emplace_back(item, num);
            }
        }
    }
    fin.close();

    cout << "Answer: " << focusPower(boxes) << '\n';

    return 0;
}