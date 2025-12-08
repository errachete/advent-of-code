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

public:
    UFDS(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find_set(int i) {
        if (parent[i] != i)
            parent[i] = find_set(parent[i]);
        return parent[i];
    }

    void union_set(int i, int j) {
        i = find_set(i);
        j = find_set(j);
        if (i != j)
            parent[j] = i;
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
    for (int i = 0; i < 1000; ++i) {
        pair<llint, ii> conn = conn_prio.top();
        conn_prio.pop();
        ufds.union_set(conn.second.first, conn.second.second);
    }

    vector<int> components = vector<int>(joints.size(), 0);
    for (int i = 0; i < joints.size(); ++i) {
        int rep = ufds.find_set(i);
        ++components[rep];
    }

    sort(components.begin(), components.end(), greater<int>());
    llint result = 1;
    for (int i = 0; i < 3; ++i)
        result *= components[i];
    cout << "Result: " << result << '\n';
    return 0;
}