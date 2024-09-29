#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <queue>

using namespace std;
using llint = long long int;

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

llint gcd(llint a, llint b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

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
    // Examining input data, rx receives signal from dt, and dt is a conjunction of ks, pm, vk and dl
    // So, for dt to send a low to rx, we need for ks, pm, vk and dl to be high at the same time
    // After examining the process, they are high just once after several button presses
    // Lets compute the needed number of button presses for each, and then the lcm
    llint buttonPress = 0, ks = 0, pm = 0, vk = 0, dl = 0;
    while ((ks * pm * vk * dl) == 0) // Any == 0
    {
        ++buttonPress;

        queue<pair<Pulse,pair<string,string>>> pending;
        for (auto comp : system["broadcaster"]) 
            pending.emplace(low,make_pair("broadcaster",comp));

        // Propagate pulses until finish
        while (!pending.empty())
        {
            auto move = pending.front();
            pending.pop();
            Pulse pulse = move.first;
            string origin = move.second.first;
            string dest = move.second.second;
            
            if (pulse == high && dest == "dt")
            {
                if (origin == "ks")
                    ks = buttonPress;
                else if (origin == "pm")
                    pm = buttonPress;
                else if (origin == "vk")
                    vk = buttonPress;
                else if (origin == "dl")
                    dl = buttonPress;
            }

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
    }

    llint lcm = ks * pm / gcd(ks,pm);
    lcm = lcm * vk / gcd(lcm,vk);
    lcm = lcm * dl / gcd(lcm,dl);

    cout << "Answer: " << lcm << endl;
    return 0;
}