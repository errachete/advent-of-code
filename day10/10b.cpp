#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// Directions and coordinates to move
enum dir {N,E,S,W,O,NE,SE,SW,NW};
vector<pair<int,int>> coords = {{-1,0},{0,1},{1,0},{0,-1},{0,0},{-1,1},{1,1},{1,-1},{-1,-1}};

bool inRange(const vector<vector<char>> & map, const pair<int,int> & pos)
{
    return pos.first >= 0 && pos.second >= 0 && pos.first < map.size() && pos.second < map[pos.first].size();
}

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

void floodFill(const vector<vector<bool>> & pipeMap, vector<vector<char>> & map, const pair<int, int> & pos, char fill)
{
    if (inRange(map, pos) &&
        pipeMap[pos.first][pos.second] == false && map[pos.first][pos.second] != 'I' && map[pos.first][pos.second] != 'O')
    {
        map[pos.first][pos.second] = fill;
        for (int i = 0; i < 4; ++i)
            floodFill(pipeMap, map, {pos.first+coords[i].first,pos.second+coords[i].second}, fill);
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

void moveAndFlood(const vector<vector<bool>> & pipeMap, vector<vector<char>> & map, pair<int,int> & pos,
                 dir & from, pair<int,int> & left, char charL, pair<int,int> & right, char charR)
{
    floodFill(pipeMap, map, left, charL);
    floodFill(pipeMap, map, right, charR);
    dir aux;
    switch(map[pos.first][pos.second])
    {   
        case '|':
            aux = inverse(from);
            left = {left.first + coords[aux].first, left.second + coords[aux].second};
            right = {right.first + coords[aux].first, right.second + coords[aux].second};
            break;
        case '-':
            aux = inverse(from);
            left = {left.first + coords[aux].first, left.second + coords[aux].second};
            right = {right.first + coords[aux].first, right.second + coords[aux].second};
            break;
        case 'L':
            if (from == N)
            {
                from = W;
                floodFill(pipeMap, map, {right.first+coords[S].first, right.second+coords[S].second}, charR);
                floodFill(pipeMap, map, {right.first+coords[SE].first, right.second+coords[SE].second}, charR);
                right = {left.first + coords[S].first, left.second + coords[S].second};
                left = {left.first + coords[N].first, left.second + coords[N].second};
            }
            else // from == E
            {
                from = S;
                floodFill(pipeMap, map, {left.first+coords[W].first, left.second+coords[W].second}, charL);
                floodFill(pipeMap, map, {left.first+coords[NW].first, left.second+coords[NW].second}, charL);
                left = {right.first + coords[W].first, right.second + coords[W].second};
                right = {right.first + coords[E].first, right.second + coords[E].second};
            }
            break;
        case 'J':
            if (from == N)
            {
                from = E;
                floodFill(pipeMap, map, {left.first+coords[S].first, left.second+coords[S].second}, charL);
                floodFill(pipeMap, map, {left.first+coords[SW].first, left.second+coords[SW].second}, charL);
                left = {right.first + coords[S].first, right.second + coords[S].second};
                right = {right.first + coords[N].first, right.second + coords[N].second};
            }
            else // from == W
            {
                from = S;
                floodFill(pipeMap, map, {right.first+coords[E].first, right.second+coords[E].second}, charR);
                floodFill(pipeMap, map, {right.first+coords[NE].first, right.second+coords[NE].second}, charR);
                right = {left.first + coords[E].first, left.second + coords[E].second};
                left = {left.first + coords[W].first, left.second + coords[W].second};
            }
            break;
        case '7':
            if (from == S)
            {
                from = E;
                floodFill(pipeMap, map, {right.first+coords[N].first, right.second+coords[N].second}, charR);
                floodFill(pipeMap, map, {right.first+coords[NW].first, right.second+coords[NW].second}, charR);
                right = {left.first + coords[N].first, left.second + coords[N].second};
                left = {left.first + coords[S].first, left.second + coords[S].second};
            }
            else // from == W
            {
                from = N;
                floodFill(pipeMap, map, {left.first+coords[E].first, left.second+coords[E].second}, charL);
                floodFill(pipeMap, map, {left.first+coords[SE].first, left.second+coords[SE].second}, charL);
                left = {right.first + coords[E].first, right.second + coords[E].second};
                right = {right.first + coords[W].first, right.second + coords[W].second};
            }
            break;
        case 'F':
            if (from == S)
            {
                from = W;
                floodFill(pipeMap, map, {left.first+coords[N].first, left.second+coords[N].second}, charL);
                floodFill(pipeMap, map, {left.first+coords[NE].first, left.second+coords[NE].second}, charL);
                left = {right.first + coords[N].first, right.second + coords[N].second};
                right = {right.first + coords[S].first, right.second + coords[S].second};
            }
            else // from == E
            {
                from = N;
                floodFill(pipeMap, map, {right.first+coords[W].first, right.second+coords[W].second}, charR);
                floodFill(pipeMap, map, {right.first+coords[SW].first, right.second+coords[SW].second}, charR);
                right = {left.first + coords[W].first, left.second + coords[W].second};
                left = {left.first + coords[E].first, left.second + coords[E].second};
            }
            break;
    }

    dir to = inverse(from);
    pos = {pos.first + coords[to].first, pos.second + coords[to].second};
    
}

void paint(const vector<vector<char>> & map)
{
    ofstream fout("output.txt");
    for (auto v: map)
    {
        for (auto c: v)
            fout << c;
        fout << '\n';
    }
    fout.close();
}


int main()
{
    ifstream fin("input.txt");
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
    fin.close();

    // First find a direction suitable to start
    pair<int,int> current_pos = s_coords;
    dir from;
    dir s_dirs = O;
    // North suitable?
    if (map[s_coords.first+coords[N].first][s_coords.second+coords[N].second] == '|' ||
        map[s_coords.first+coords[N].first][s_coords.second+coords[N].second] == 'F' ||
        map[s_coords.first+coords[N].first][s_coords.second+coords[N].second] == '7')
        {   
            s_dirs = N;
            from = S;
            current_pos = {s_coords.first+coords[N].first, s_coords.second+coords[N].second};
        }
    // East suitable?
    if (map[s_coords.first+coords[E].first][s_coords.second+coords[E].second] == '-' ||
        map[s_coords.first+coords[E].first][s_coords.second+coords[E].second] == 'J' ||
        map[s_coords.first+coords[E].first][s_coords.second+coords[E].second] == '7')
        {   
            if (s_dirs == N)
                map[s_coords.first][s_coords.second] = 'L';
            else
                s_dirs = E;
            from = W;
            current_pos = {s_coords.first+coords[E].first, s_coords.second+coords[E].second};
        }
    // South suitable?
    if (map[s_coords.first+coords[S].first][s_coords.second+coords[S].second] == '|' ||
        map[s_coords.first+coords[S].first][s_coords.second+coords[S].second] == 'J' ||
        map[s_coords.first+coords[S].first][s_coords.second+coords[S].second] == 'L')
        {
            switch(s_dirs)
            {
                case N:
                    map[s_coords.first][s_coords.second] = '|';
                    break;
                case E:
                    map[s_coords.first][s_coords.second] = 'F';
                    break;
                default:
                    s_dirs = S;
            }
            from = N;
            current_pos = {s_coords.first+coords[S].first, s_coords.second+coords[S].second};
        }
    // West suitable?
    if (map[s_coords.first+coords[W].first][s_coords.second+coords[W].second] == '|' ||
        map[s_coords.first+coords[W].first][s_coords.second+coords[W].second] == 'J' ||
        map[s_coords.first+coords[W].first][s_coords.second+coords[W].second] == 'L')
        {
            switch(s_dirs)
            {
                case N:
                    map[s_coords.first][s_coords.second] = 'J';
                    break;
                case E:
                    map[s_coords.first][s_coords.second] = '-';
                    break;
                case S:
                    map[s_coords.first][s_coords.second] = '7';
                    break;
            }
            from = E;
            current_pos = {s_coords.first+coords[W].first, s_coords.second+coords[W].second};
        }

    // Traverse the pipe until back to the source
    vector<vector<bool>> pipeMap(map.size(), vector<bool>(map[0].size(), false));
    pipeMap[s_coords.first][s_coords.second] = true;
    while (current_pos != s_coords)
    {
        pipeMap[current_pos.first][current_pos.second] = true;
        moveCell(map, current_pos, from);
    }

    // Flood from the corners
    floodFill(pipeMap, map, {0,0}, 'O');
    floodFill(pipeMap, map, {0,map[0].size()-1}, 'O');
    floodFill(pipeMap, map, {map.size()-1,0}, 'O');
    floodFill(pipeMap, map, {map.size()-1,map[map.size()-1].size()-1}, 'O');

    // Traverse the pipe flooding its sides with I or O
    // Find a piece of pipe to start
    bool found = false;
    int i = 0, j = 0;
    for (i = 0; i < map.size() && !found; ++i)
        for(j = 0; j < map[i].size() && !found; ++j)
            if (pipeMap[i][j])
                found = true;
    s_coords = {i-1,j-1};

    // Because of the search method (row by row), first pipe must be F
    // For this reason, outside and inside configuration must be
    //   O O .
    //   O F .
    //   . . I
    // Fill inside and outside accordingly also following the logic inside moveAndFlood function, giving
    //   . . .
    //   O F I
    //   . . .
    pair<int,int> outside = {s_coords.first+coords[W].first, s_coords.second+coords[W].second};
    pair<int,int> inside = {s_coords.first+coords[E].first, s_coords.second+coords[E].second};
    current_pos = s_coords; from = S;
    moveAndFlood(pipeMap, map, current_pos, from, outside, 'O', inside, 'I');
    while(current_pos != s_coords)
    {
        moveAndFlood(pipeMap, map, current_pos, from, outside, 'O', inside, 'I');
        //paint(map);
    }

    int count = 0;
    for (auto v : map)
        for (auto c : v)
            if (c == 'I')
                ++count;
    
    

    cout << "Answer: " << count << '\n';

    return 0;
}