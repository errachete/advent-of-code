#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
using llint = long long int;
using ii = pair<int,int>;

struct vertex
{
    int x;
    int y;
    int in;
    int out;
};

int find_quadrant(const vertex &p1, const vertex &p2)
{
    if (p1.x == p2.x && p1.y < p2.y) return 270;
    else if (p1.x == p2.x && p1.y > p2.y) return 90;
    else if (p1.y == p2.y && p1.x < p2.x) return 0;
    else if (p1.y == p2.y && p1.x > p2.x) return 180;
    else if (p1.x < p2.x && p1.y > p2.y) return 45;
    else if (p1.x > p2.x && p1.y > p2.y) return 135;
    else if (p1.x > p2.x && p1.y < p2.y) return 225;
    else // p1.x < p2.x && p1.y < p2.y
        return 315;
}

bool valid_position(const vertex &p1, const vertex &p2)
{
    int quadrant = find_quadrant(p1, p2);
    if (p1.out < p1.in)
        return (p1.in <= quadrant && quadrant <= 360) || (0 <= quadrant && quadrant <= p1.out);
    else
        return p1.in <= quadrant && quadrant <= p1.out;
}

llint area(const vertex &p1, const vertex &p2)
{
    llint side_1 = abs(p1.x - p2.x) + 1;
    llint side_2 = abs(p1.y - p2.y) + 1;
    return side_1 * side_2;
}

bool contains(const vertex &p1, const vertex &p2, const vertex &p)
{
    int x_min = min(p1.x, p2.x);
    int x_max = max(p1.x, p2.x);
    int y_min = min(p1.y, p2.y);
    int y_max = max(p1.y, p2.y);
    return (x_min < p.x && p.x < x_max && y_min < p.y && p.y < y_max);
}

bool intersects(const vertex &p1, const vertex &p2, const vertex &q1, const vertex &q2)
{
    bool p_horiz = (p1.y == p2.y);
    bool q_horiz = (q1.y == q2.y);

    if (p_horiz == q_horiz)
        return false; // Parallel lines cannot intersect

    if (p_horiz)
        return min(q1.y, q2.y) < p1.y && p1.y < max(q1.y, q2.y) &&
                min(p1.x, p2.x) < q1.x && q1.x < max(p1.x, p2.x);
    else
        return min(p1.y, p2.y) < q1.y && q1.y < max(p1.y, p2.y) &&
                min(q1.x, q2.x) < p1.x && p1.x < max(q1.x, q2.x);
}


int main()
{
    ifstream fin("input.txt");

    // Read positions
    vector<vertex> red_tiles;
    int x, y;
    char aux;
    while (fin >> x >> aux >> y)
        red_tiles.push_back({x, y, 0, 0});
    red_tiles.push_back(red_tiles[0]);
    fin.close();

    // Traverse positions determining directions of in and out
    red_tiles[0].in = find_quadrant(red_tiles[0], red_tiles[red_tiles.size()-1]);
    red_tiles[0].out = find_quadrant(red_tiles[0], red_tiles[1]);
    for (int i = 1; i < red_tiles.size()-1; ++i)
    {
        red_tiles[i].in = find_quadrant(red_tiles[i], red_tiles[i-1]);
        red_tiles[i].out = find_quadrant(red_tiles[i], red_tiles[i+1]);
    }
    red_tiles[red_tiles.size()-1].in = find_quadrant(red_tiles[red_tiles.size()-1], red_tiles[red_tiles.size()-2]);
    red_tiles[red_tiles.size()-1].out = find_quadrant(red_tiles[red_tiles.size()-1], red_tiles[0]);

    // Compute areas for possibly valid rectangles
    priority_queue<pair<llint, ii>> areas;
    for (int i = 0; i < red_tiles.size()-1; ++i)
        for (int j = i+1; j < red_tiles.size()-1; ++j)
            if (valid_position(red_tiles[i], red_tiles[j]) && valid_position(red_tiles[j], red_tiles[i]))
                areas.push({area(red_tiles[i], red_tiles[j]), {i,j}});

    // Find the largest valid rectangle
    bool found = false;
    llint result = 0;
    while (!found && !areas.empty())
    {
        pair<llint, ii> current = areas.top();
        areas.pop();
        result = current.first;
        vertex p1 = red_tiles[current.second.first];
        vertex p2 = red_tiles[current.second.second];
        found = true;
        // Check no vertex inside the rectangle
        for (int k = 0; k < red_tiles.size()-1; ++k)
        {
            if (contains(p1, p2, red_tiles[k]))
            {
                found = false;
                break;
            }
        }
        // Check no edge instersects the rectangle
        if (found)
        {
            vertex p12 = {p2.x, p1.y, 0, 0};
            vertex p21 = {p1.x, p2.y, 0, 0};
            for (int k = 0; k < red_tiles.size()-1; ++k)
            {
                if (intersects(p1, p12, red_tiles[k], red_tiles[k+1]) ||
                    intersects(p12, p2, red_tiles[k], red_tiles[k+1]) ||
                    intersects(p2, p21, red_tiles[k], red_tiles[k+1]) ||
                    intersects(p21, p1, red_tiles[k], red_tiles[k+1]))
                {
                    found = false;
                    break;
                }
            }
            found &= !(intersects(p1, p12, red_tiles[red_tiles.size()-1], red_tiles[0]) ||
                       intersects(p12, p2, red_tiles[red_tiles.size()-1], red_tiles[0]) ||
                       intersects(p2, p21, red_tiles[red_tiles.size()-1], red_tiles[0]) ||
                       intersects(p21, p1, red_tiles[red_tiles.size()-1], red_tiles[0]));
        }
    }

    cout << "Result: " << result << '\n';
    return 0;
}