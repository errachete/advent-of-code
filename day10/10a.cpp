#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Directions and coordinates to move
enum dir {N,E,S,W,O};
vector<pair<int,int>> coords = {{-1,0},{0,1},{1,0},{0,-1},{0,0}};

dir inverse(dir from)
{
    switch (from)
    {
        case N: return S;
        case S: return N;
        case E: return W;
        case W: return E;
        default: return O;
    }
}

void moveCell(const vector<vector<char>> & map, pair<int,int> & pos, dir & from)
{
    switch(map[pos.first][pos.second])
    {
        case '|':
            // From does not change
            break;
        case '-':
            // From does not change
            break;
        case 'L':
            from = from == N ? W : S;
            break;
        case 'J':
            from = from == N ? E : S;
            break;
        case '7':
            from = from == S ? E : N;
            break;
        case 'F':
            from = from == S ? W : N;
            break;
        default:
            from = O;       
    }
    dir to = inverse(from);
    pos = {pos.first + coords[to].first, pos.second + coords[to].second};
}

int main()
{
    ifstream fin("test.txt");
    string line;
    vector<vector<char>> map;
    pair<int,int> s_coords;
    int lines = 0;
    while (getline(fin, line))
    {
        vector<char> v;
        for (int i = 0; i < line.size(); ++i)
        {
            v.push_back(line[i]);
            if (line[i] == 'S')
                s_coords = make_pair(lines, i);
        }
        map.push_back(v);
        ++lines;
    }

    // First find a direction suitable to start
    int length = 0;
    pair<int,int> current_pos = s_coords;
    dir from;
    // North suitable?
    if (map[s_coords.first+coords[N].first][s_coords.second+coords[N].second] == '|' ||
        map[s_coords.first+coords[N].first][s_coords.second+coords[N].second] == 'F' ||
        map[s_coords.first+coords[N].first][s_coords.second+coords[N].second] == '7')
        {
            from = S;
            current_pos = {s_coords.first+coords[N].first, s_coords.second+coords[N].second};
            ++length;
        }
    // East suitable?
    else if (map[s_coords.first+coords[E].first][s_coords.second+coords[E].second] == '-' ||
        map[s_coords.first+coords[E].first][s_coords.second+coords[E].second] == 'J' ||
        map[s_coords.first+coords[E].first][s_coords.second+coords[E].second] == '7')
        {
            from = W;
            current_pos = {s_coords.first+coords[E].first, s_coords.second+coords[E].second};
            ++length;
        }
    // South suitable?
    else if (map[s_coords.first+coords[S].first][s_coords.second+coords[S].second] == '|' ||
        map[s_coords.first+coords[S].first][s_coords.second+coords[S].second] == 'J' ||
        map[s_coords.first+coords[S].first][s_coords.second+coords[S].second] == 'L')
        {
            from = N;
            current_pos = {s_coords.first+coords[S].first, s_coords.second+coords[S].second};
            ++length;
        }
    // West suitable?
    else if (map[s_coords.first+coords[W].first][s_coords.second+coords[W].second] == '|' ||
        map[s_coords.first+coords[W].first][s_coords.second+coords[W].second] == 'J' ||
        map[s_coords.first+coords[W].first][s_coords.second+coords[W].second] == 'L')
        {
            from = E;
            current_pos = {s_coords.first+coords[W].first, s_coords.second+coords[W].second};
            ++length;
        }

    // Traverse the pipe until back to the source
    while (current_pos != s_coords)
    {
        moveCell(map, current_pos, from);
        ++length;
    }

    cout << "Answer: " << length / 2 << '\n';

    return 0;
}