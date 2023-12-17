#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using llint = long long int;
using pllint = pair<llint, llint>;

void readMap(map<llint, pllint> & mapper, ifstream & fin)
{   
    string line = "";
    llint destStart, origStart, length;
    getline(fin, line); // map title
    getline(fin, line); // first mapping line
    while(line.size() > 0)
    {
        istringstream sline(line);
        sline >> destStart >> origStart >> length;
        mapper[origStart] = make_pair(origStart + length, destStart);
        if (fin.eof()) break;
        getline(fin, line);
    }
}

void transform(llint & seed, const map<llint, pllint> & map)
{   
    // Gets transformation following to the one that the element could be applied to
    auto mapPos = map.upper_bound(seed);
    // If it is begin, means seed is before the first transformation, so it transforms into itself
    if (mapPos == map.begin()) return;
    // Else, take the previous transformation
    --mapPos;
    // If it is not in range of transformation, it transforms into itself
    llint origStart = mapPos->first, origEnd = mapPos->second.first, destStart = mapPos->second.second;
    if (seed > origEnd) return;
    // In other case, calculate transformed seed
    seed = destStart + (seed - origStart);
}

int main()
{
    ifstream fin("input.txt");
    vector<llint> seeds; // List of seeds
    map<llint, pllint> seeds2soil, soil2fert, fert2water, water2light, light2temp, temp2humid, humid2loc; // Maps having <origStart, <origEnd, destStart>>

    // Load input into variables
    string line = "", aux = "";
    llint number = 0;

    // Read seeds
    getline(fin, line);
    istringstream sline(line);
    sline >> aux; // seeds:
    while(sline >> number)
        seeds.push_back(number);
    getline(fin, line); // Empty line

    // Read maps
    readMap(seeds2soil, fin);
    readMap(soil2fert, fin);
    readMap(fert2water, fin);
    readMap(water2light, fin);
    readMap(light2temp, fin);
    readMap(temp2humid, fin);
    readMap(humid2loc, fin);

    fin.close();

    // Processing
    for (llint & seed : seeds)
    {
        transform(seed, seeds2soil);
        transform(seed, soil2fert);
        transform(seed, fert2water);
        transform(seed, water2light);
        transform(seed, light2temp);
        transform(seed, temp2humid);
        transform(seed, humid2loc);
    }

    cout << "Answer: " << *min_element(seeds.begin(), seeds.end()) << '\n';

    return 0;
}