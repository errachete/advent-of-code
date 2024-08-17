#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


enum Cat {x,m,a,s};

class Part
{
    vector<int> cat = vector<int>(4,0);

    public:
    Part(string & str)
    {
        str = str.substr(1,str.size()-2);
        int comma = str.find(',');
        cat[x] = stoi(str.substr(2,comma-2));
        int preComma = comma;
        comma = str.find(',',preComma+1);
        cat[m] = stoi(str.substr(preComma+3,comma-preComma-3));
        preComma = comma;
        comma = str.find(',',preComma+1);
        cat[a] = stoi(str.substr(preComma+3,comma-preComma-3));
        cat[s] = stoi(str.substr(comma+3));
    }

    int get(Cat idx) const
    {
        return cat[idx];
    }

    int sum() const
    {
        return accumulate(cat.begin(), cat.end(), 0);
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

    string apply(Part part) const
    {
        if (type == '>')
            return (part.get(cat) > value) ? dest : "";
        else
            return (part.get(cat) < value) ? dest : "";
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

    string apply(Part part) const
    {
        for (int i = 0; i < rules.size(); ++i)
        {
            string result = rules[i].apply(part);
            if (result != "") return result;
        }
        return end;
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
    int total = 0;
    // Read and apply the parts
    while(getline(fin,line))
    {
        Part p(line);
        string res = system["in"].apply(p);
        while (res != "A" && res != "R")
            res = system[res].apply(p);

        if (res == "A") total += p.sum();
    }

    cout << "Answer: " << total << endl;
    return 0;
}