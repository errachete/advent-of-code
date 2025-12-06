#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
using llint = long long int;
using ll = pair<llint, llint>;

bool isFresh(const vector<ll> & intervals, llint id, int left, int right)
{
    if (left == right)
        return intervals[left].first <= id && id <= intervals[left].second;

    int mid = (right + left) / 2;
    if (id <= intervals[mid].second)
        return isFresh(intervals, id, left, mid);
    else
        return isFresh(intervals, id, mid + 1, right);
}


int main()
{
    ifstream fin("input.txt");

    string line;
    vector<ll> intervals;
    istringstream sin(line);
    llint start, end;
    char aux;
    getline(fin, line);
    while(!line.empty()){
        sin.str(line);
        sin >> start >> aux >> end;
        sin.clear();
        intervals.push_back({start, end});
        getline(fin, line);
    }

    sort(intervals.begin(), intervals.end());

    vector<ll> merged;
    int i = 0;
    while (i < intervals.size())
    {
        start = intervals[i].first;
        end = intervals[i].second;
        while (i+1 < intervals.size() && intervals[i+1].first <= end)
        {
            end = max(end, intervals[i+1].second);
            ++i;
        }
        merged.push_back({start, end});
        ++i;
    }
    fin.close();

    llint result = 0;
    for (int i = 0; i < merged.size(); ++i)
        result += merged[i].second - merged[i].first + 1;

    cout << "Result: " << result << '\n';
    return 0;
}