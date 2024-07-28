#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>

using namespace std;

using ii = pair<int, int>;

vector<pair<ii, char>> moveOnPoint(ii pos, char dir)
{
    vector<pair<ii, char>> dest;
    switch (dir)
    {
        case 'U':
            dest.emplace_back(make_pair(pos.first-1, pos.second), dir);
            break;
        case 'D':
            dest.emplace_back(make_pair(pos.first+1, pos.second), dir);
            break;
        case 'L':
            dest.emplace_back(make_pair(pos.first, pos.second-1), dir);
            break;
        case 'R':
            dest.emplace_back(make_pair(pos.first, pos.second+1), dir);
            break;
    }
    return dest;
}

vector<pair<ii, char>> moveOnPipe(ii pos, char dir)
{
    vector<pair<ii, char>> dest;
    switch (dir)
    {
        case 'U':
            dest.emplace_back(make_pair(pos.first-1, pos.second), dir);
            break;
        case 'D':
            dest.emplace_back(make_pair(pos.first+1, pos.second), dir);
            break;
        case 'L':
        case 'R':
            dest.emplace_back(make_pair(pos.first-1, pos.second), 'U');
            dest.emplace_back(make_pair(pos.first+1, pos.second), 'D');
            break;
    }
    return dest;
}

vector<pair<ii, char>> moveOnHyphen(ii pos, char dir)
{
    vector<pair<ii, char>> dest;
    switch (dir)
    {
        case 'U':
        case 'D':
            dest.emplace_back(make_pair(pos.first, pos.second-1), 'L');
            dest.emplace_back(make_pair(pos.first, pos.second+1), 'R');
            break;
        case 'L':
            dest.emplace_back(make_pair(pos.first, pos.second-1), dir);
            break;
        case 'R':
            dest.emplace_back(make_pair(pos.first, pos.second+1), dir);
            break;
    }
    return dest;
}

vector<pair<ii, char>> moveOnForwslash(ii pos, char dir)
{
    vector<pair<ii, char>> dest;
    switch (dir)
    {
        case 'U':
            dest.emplace_back(make_pair(pos.first, pos.second+1), 'R');
            break;
        case 'D':
            dest.emplace_back(make_pair(pos.first, pos.second-1), 'L');
            break;
        case 'L':
            dest.emplace_back(make_pair(pos.first+1, pos.second), 'D');
            break;
        case 'R':
            dest.emplace_back(make_pair(pos.first-1, pos.second), 'U');
            break;
    }
    return dest;
}

vector<pair<ii, char>> moveOnBackslash(ii pos, char dir)
{
    vector<pair<ii, char>> dest;
    switch (dir)
    {
        case 'U':
            dest.emplace_back(make_pair(pos.first, pos.second-1), 'L');
            break;
        case 'D':
            dest.emplace_back(make_pair(pos.first, pos.second+1), 'R');
            break;
        case 'L':
            dest.emplace_back(make_pair(pos.first-1, pos.second), 'U');
            break;
        case 'R':
            dest.emplace_back(make_pair(pos.first+1, pos.second), 'D');
            break;
    }
    return dest;
}

void move(const vector<vector<char>> & cont, map<ii, unordered_set<char>> & visit, queue<pair<ii, char>> & pending)
{
    pair<ii, char> curr = pending.front();
    pending.pop();
    ii pos = curr.first;
    char dir = curr.second;

    // Already visited with that direction, return
    if (visit.count(pos) && visit[pos].count(dir))
        return;

    // Not visited yet, add to visit map
    if (!visit.count(pos))
        visit[pos] = unordered_set<char>();
    visit[pos].insert(dir);

    // Evaluate cell and compute new cells depending on content
    vector<pair<ii, char>> dest;
    switch (cont[pos.first][pos.second])
    {
        case '.':
            dest = moveOnPoint(pos, dir);
            break;
        case '|':
            dest = moveOnPipe(pos, dir);
            break;
        case '-':
            dest = moveOnHyphen(pos, dir);
            break;
        case '/':
            dest = moveOnForwslash(pos, dir);
            break;
        case '\\':
            dest = moveOnBackslash(pos, dir);
            break;
    }

    // Input destination cells in pending if in range
    for (auto elem : dest)
    {
        if (elem.first.first >= 0 && elem.first.first < cont.size() &&
            elem.first.second >= 0 && elem.first.second < cont[elem.first.first].size())
            pending.push(elem);
    }
}

int main() 
{
    ifstream fin("input.txt");
    string line;
    vector<vector<char>> cont;
    while (getline(fin, line))
    {
        cont.push_back(vector<char>());
        for(char c : line)
            cont.back().push_back(c);
    }
    fin.close();

    // Map to store alreay visited cells with a certain direction
    map<ii,unordered_set<char>> visit;
    // Queue of next cells to visit
    queue<pair<ii, char>> pending;
    pending.emplace(make_pair(0,0), 'R');

    while (!pending.empty())
    {
        move(cont, visit, pending);
    }

    cout << "Answer: " << visit.size() << '\n';

    return 0;
}