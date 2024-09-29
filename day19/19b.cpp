#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;


using llint = long long int;

enum Cat {x,m,a,s};

class PartSet
{
    vector<int> minCat = vector<int>(4);
    vector<int> maxCat = vector<int>(4);

    public:
    PartSet()
    {
        for (int i = 0; i < minCat.size(); ++i)
        {
            minCat[i] = 1;
            maxCat[i] = 4000;
        }
    }

    PartSet(PartSet p, bool setMin, Cat cat, int value)
    {
        minCat = p.minCat;
        maxCat = p.maxCat;

        if (setMin) minCat[cat] = value;
        else maxCat[cat] = value;
    }

    int getMin(Cat cat) const
    {
        return minCat[cat];
    }

    int getMax(Cat cat) const
    {
        return maxCat[cat];
    }

    llint comb() const
    {
        llint result = 1;
        for (int i = 0; i < minCat.size(); ++i)
        {
            result *= (maxCat[i]-minCat[i]+1);
        }
        return result;
    }
};

class Rule
{
    Cat cat;
    char type;
    int value;
    string dest;

    public:
    Rule(const string & str)
    {
        switch(str[0])
        {
            case 'x': cat = x; break;
            case 'm': cat = m; break;
            case 'a': cat = a; break;
            case 's': cat = s; break;
        }
        type = str[1];
        value = stoi(str.substr(2,str.find(':')-2));
        dest = str.substr(str.find(':')+1);
    }

    vector<pair<string,PartSet>> apply(PartSet p) const
    {
        vector<pair<string,PartSet>> result;
        if (type == '>')
        {
            if (p.getMin(cat) > value) result.emplace_back(dest, p);
            else if (value >= p.getMax(cat)) result.emplace_back("", p);
            else
            {
                result.emplace_back("", PartSet(p, false, cat, value));
                result.emplace_back(dest, PartSet(p, true, cat, value+1));
            }
        }
        else
        {
            if (value <= p.getMin(cat)) result.emplace_back("", p);
            else if (p.getMax(cat) < value) result.emplace_back(dest, p);
            else
            {
                result.emplace_back(dest, PartSet(p, false, cat, value-1));
                result.emplace_back("", PartSet(p, true, cat, value));
            }
        }
        return result;
    }
};

class Workflow
{
    string name;
    vector<Rule> rules;
    string end;

    public:
    Workflow(){}

    Workflow(const string & str)
    {
        int open = str.find('{');
        name = str.substr(0,open);
        int preComma = open, comma = str.find(',');
        while (comma != string::npos)
        {
            rules.emplace_back(str.substr(preComma+1,comma-preComma-1));
            preComma = comma;
            comma = str.find(',',preComma+1);
        }
        end = str.substr(preComma+1, str.size()-preComma-2);
    }

    string getName() const
    {
        return name;
    }

    vector<pair<string,PartSet>> apply(PartSet p) const
    {
        vector<pair<string,PartSet>> endResult;
        queue<PartSet> pending;
        pending.push(p);
        for (int i = 0; i < rules.size(); ++i)
        {
            queue<PartSet> stays;
            while (!pending.empty())
            {
                PartSet ps = pending.front();
                pending.pop();

                auto result = rules[i].apply(ps);

                for (auto e : result)
                {
                    if (e.first == "")
                        stays.push(e.second);
                    else
                        endResult.push_back(e);
                }
            }
            pending = stays; 
        }

        while(!pending.empty())
        {
            endResult.emplace_back(end,pending.front());
            pending.pop();
        }

        return endResult;
    }
};

int main()
{
    ifstream fin("input.txt");
    string line = "";
    unordered_map<string,Workflow> system;
    // Read the workflows
    getline(fin, line);
    while (line != "")
    {
        Workflow w(line);
        system[w.getName()] = w;
        getline(fin, line);
    }
    fin.close();

    llint acc = 0, rej = 0;
    queue<pair<string,PartSet>> pending;
    pending.emplace("in",PartSet());
    while (!pending.empty())
    {
        auto ps = pending.front();
        pending.pop();

        auto result = system[ps.first].apply(ps.second);
        for (auto e : result)
        {
            if (e.first == "A")
                acc += e.second.comb();
            else if (e.first == "R")
                rej += e.second.comb();
            else
                pending.emplace(e.first, e.second);
        }
    }

    cout << "Answer: " << acc << endl;
    return 0;
}