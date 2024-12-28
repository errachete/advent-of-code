#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int total = 0;
    string line = "";
    while (getline(fin, line)) 
    {
        istringstream sline(line);
        int id = 0;
        string aux = "";
        sline >> aux >> id >> aux; // Game and ID and :
        // Explore sets
        int number = 0;
        string colour = "";
        unordered_map<string, int> cubes = {{"red",0},{"green",0},{"blue",0}};
        while (sline >> number >> colour) 
        {
            if (colour.back() == ',' || colour.back() == ';')
                colour.pop_back();
            
            cubes[colour] = max(cubes[colour], number);
        }
        
        total += (cubes["red"] * cubes["green"] * cubes["blue"]);

    }
    fin.close();

    cout << "Answer: " << total << '\n';
    return 0;
}