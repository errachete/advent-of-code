#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <queue>

using namespace std;

enum Pulse {none, high, low};

class FlipFlop
{
    bool state_on;

    public:
    FlipFlop () : state_on(false) {}
    Pulse receive(Pulse pulse)
    {
        if (pulse == high) 
            return none;
        
        state_on = !state_on;
        if (state_on) 
            return high;
        return low;
    }
    bool init_state()
    {
        return state_on == false;
    }
};

class Conjunction
{
    unordered_map<string, Pulse> state;

    public:
    Conjunction () : state(unordered_map<string, Pulse>()) {}
    void add_input(string name)
    {
        state[name] = low;
    }
    Pulse receive(string name, Pulse pulse)
    {
        state[name] = pulse;
        if (this->all_high())
            return low;
        return high;
    }
    bool init_state()
    {
        return all_low();
    }

    private:
    bool all_high() const
    {
        for (auto a : state)
            if (a.second == low) 
                return false;
        return true;
    }
    bool all_low() const
    {
        for (auto a : state)
            if (a.second == high)
                return false;
        return true;
    }
};


int main()
{
    ifstream fin("input.txt");
    string line = "";
    unordered_map<string,FlipFlop> flipList;
    unordered_map<string,Conjunction> conjList;
    unordered_map<string,vector<string>> system;
    // Read the component sequence
    while(getline(fin, line))
    {
        istringstream in(line);
        string name, aux;
        in >> name;
        switch(name[0])
        {
            case '%':
                name.erase(name.begin());
                flipList.emplace(name, FlipFlop());
                break;
            case '&':
                name.erase(name.begin());
                conjList.emplace(name, Conjunction());
                break;
            default:
                break;
        }
        in >> aux;
        system[name] = vector<string>();
        while(in >> aux)
        {
            if (aux.back() == ',')
                aux.pop_back();
            system[name].push_back(aux);
        }
    }
    fin.close();
    // Add input list to Conjunctions
    for (auto list : system)
    {
        for (auto dest : list.second)
        {
            if (conjList.count(dest))
                conjList[dest].add_input(list.first);
        }
    }
    // Send low from broadcaster until all components are back in "init_state" again
    bool stop = false;
    int cycleSize = 0, lows = 0, highs = 0;
    while (!stop && cycleSize < 1000)
    {
        queue<pair<Pulse,pair<string,string>>> pending;
        for (auto comp : system["broadcaster"]) 
            pending.emplace(low,make_pair("broadcaster",comp));
        ++lows;

        // Propagate pulses until finish
        while (!pending.empty())
        {
            auto move = pending.front();
            pending.pop();
            Pulse pulse = move.first;
            string origin = move.second.first;
            string dest = move.second.second;
            if (pulse == low) ++lows;
            else ++highs;

            if (conjList.count(dest))
            {
                Pulse out = conjList[dest].receive(origin,pulse);
                for (auto next : system[dest])
                    pending.emplace(out,make_pair(dest,next));
            }
            else if (flipList.count(dest))
            {
                Pulse out = flipList[dest].receive(pulse);
                if (out == none)
                    continue;
                for (auto next : system[dest])
                    pending.emplace(out,make_pair(dest,next));
            }
        }

        // Determine stop condition
        stop = true;
        for (auto comp : flipList)
        {
            if (!comp.second.init_state())
            {
                stop = false;
                break;
            }
        }
        if (stop)
            for (auto comp: conjList)
            {
                if (!comp.second.init_state())
                {
                    stop = false;
                    break;
                }
            }
        ++cycleSize;
    }

    int numCycles = 1000 / cycleSize;

    cout << "Answer: " << lows * numCycles * highs * numCycles << endl;
    return 0;
}