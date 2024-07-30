#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

using ii = pair<int,int>;

enum dir {U, R, D, L};
vector<ii> dCoords = {{-1,0},{0,1},{1,0},{0,-1}};
dir opDir(dir direc)
{
    switch(direc)
    {
        case U: return D;
        case R: return L;
        case D: return U;
        case L: return R;
    }
    return U;
}

class nodeInfo
{
    public:
        int row;
        int col;
        dir direc;
        int cons;
        int cost;

    nodeInfo(int row, int col, dir direc, int cons, int cost) : row(row), col(col), direc(direc), cons(cons), cost(cost)
    {}

    bool operator<(const nodeInfo other) const
    {
        return this->cost > other.cost;
    }
};

int dijkstra(const vector<vector<int>> & fac)
{
    // Prepare mark table (row, col, direc, cons)
    vector<vector<vector<vector<bool>>>> mark(fac.size(), 
    vector<vector<vector<bool>>>(fac[0].size(), 
    vector<vector<bool>>(dCoords.size(), 
    vector<bool>(3, false))));

    // Pending nodes pq
    priority_queue<nodeInfo> pending;
    pending.emplace(0,1,R,0,fac[0][1]);
    pending.emplace(1,0,D,0,fac[1][0]);

    // Main loop
    while (!pending.empty())
    {
        nodeInfo currNode = pending.top();
        pending.pop();

        if (mark[currNode.row][currNode.col][currNode.direc][currNode.cons])
            continue;
        mark[currNode.row][currNode.col][currNode.direc][currNode.cons] = true;

        if (currNode.row == fac.size()-1 && currNode.col == fac.back().size()-1)
            return currNode.cost;

        for (int i = 0; i < dCoords.size(); ++i)
        {
            nodeInfo nextNode = currNode;
            nextNode.row += dCoords[i].first;
            nextNode.col += dCoords[i].second;
            nextNode.direc = dir(i);
            nextNode.cons = (nextNode.direc == currNode.direc ? currNode.cons+1 : 0);

            if (nextNode.row >= 0 && nextNode.row < fac.size() &&
                nextNode.col >= 0 && nextNode.col < fac[nextNode.row].size() &&
                nextNode.cons < 3 && nextNode.direc != opDir(currNode.direc))
            {
                nextNode.cost += fac[nextNode.row][nextNode.col];
                pending.push(nextNode);
            }
        }
    }
    
    return -1;
}

int main() 
{
    ifstream fin("input.txt");
    string line;
    vector<vector<int>> fac;
    while (getline(fin, line))
    {
        fac.push_back(vector<int>());
        for(char c : line)
            fac.back().push_back(int(c)-int('0'));
    }
    fin.close();

    cout << "Answer: " << dijkstra(fac) << endl;

    return 0;
}