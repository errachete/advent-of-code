#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;
using ii = pair<int,int>;
using llint = long long int;

struct point {
    llint x, y, z;
};

llint distance(const point & a, const point & b) {
    return (a.x - b.x) * (a.x - b.x) +
           (a.y - b.y) * (a.y - b.y) +
           (a.z - b.z) * (a.z - b.z);
}

class UFDS {
private:
    vector<int> parent;
    int comp_count;

public:
    UFDS(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
        comp_count = n;
    }

    int find_set(int i) {
        if (parent[i] != i)
            parent[i] = find_set(parent[i]);
        return parent[i];
    }

    int union_set(int i, int j) {
        i = find_set(i);
        j = find_set(j);
        if (i != j)
        {
            parent[j] = i;
            --comp_count;
        }
        return comp_count;
    }

};

int main()
{
    ifstream fin("input.txt");

    vector<point> joints;
    llint x, y, z;
    char aux;
    while (fin >> x >> aux >> y >> aux >> z) {
        joints.push_back({x, y, z});
    }
    fin.close();

    priority_queue<pair<llint, ii>, vector<pair<llint, ii>>, greater<pair<llint, ii>>> conn_prio;
    for (int i = 0; i < joints.size(); ++i) {
        for (int j = i + 1; j < joints.size(); ++j) {
            llint dist = distance(joints[i], joints[j]);
            conn_prio.push({dist, {i, j}});
        }
    }

    UFDS ufds(joints.size());
    int num_comp = joints.size();
    pair<llint, ii> conn;
    do
    {
        conn = conn_prio.top();
        conn_prio.pop();
        num_comp = ufds.union_set(conn.second.first, conn.second.second);
    } while (num_comp > 1);

    llint result = joints[conn.second.first].x * joints[conn.second.second].x;
    cout << "Result: " << result << '\n';
    return 0;
}