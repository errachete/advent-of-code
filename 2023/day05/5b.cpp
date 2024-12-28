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

vector<pllint> transform(const llint & start, const llint & end, const map<llint, pllint> & map)
{   
    vector<pllint> output;
    // Get transformation for beggining and end
    auto startTrans = map.upper_bound(start);
    auto endTrans = map.upper_bound(end);
    // If both are equal
    if (startTrans == endTrans) 
    {
        // If both are begin, the whole range is before the first transformation, so it transforms into itself
        if (startTrans == map.begin())
        {
            output.emplace_back(start, end);
            return output;
        }
        // If not, take previous transformation
        --startTrans;
        llint sOrigStart = startTrans->first, sOrigEnd = startTrans->second.first, sDestStart = startTrans->second.second;
        // If start is not in range of transformation, the whole range transforms into itself
        if (start >= sOrigEnd)
        {
            output.emplace_back(start, end);
            return output;
        } 
        // If start is inside range, have to check whether end is too (whole range is transformed) or not (has to be split in two)
        else 
        {   
            // End is inside range
            if (end <= sOrigEnd)
            {   
                output.emplace_back(sDestStart + (start - sOrigStart), sDestStart + (end - sOrigStart));
                return output;
            }
            // It is divided, but both are in this transformation, so first part is transformed and second stays the same
            else
            {
                output.emplace_back(sDestStart + (start - sOrigStart), sDestStart + (sOrigEnd - sOrigStart));
                output.emplace_back(sOrigEnd, end);
                return output;
            }
        }
    }
    // They are in different transformations, so loop through the map and transform the interval in each transformation
    else
    {
        // Treat start
        // If starts before begin, that interval remains untransformed
        if (startTrans == map.begin())
        {
            output.emplace_back(start, startTrans->first);
        }
        else
        {
            // Pick previous to start
            auto prevStart = startTrans; --prevStart;
            llint sOrigStart = prevStart->first, sOrigEnd = prevStart->second.first, sDestStart = prevStart->second.second;
            // Full interval outside transformation
            if (start >= sOrigEnd)
            {
                output.emplace_back(start, startTrans->first);
            }
            // Split in two parts, first transforms and second stays the same
            else
            {
                output.emplace_back(sDestStart + (start - sOrigStart), sDestStart + (sOrigEnd - sOrigStart));
                output.emplace_back(sOrigEnd, startTrans->first);
            }    
        }
                
        // Loop through the rest of transformations until the last one
        --endTrans;
        for (auto currTrans = startTrans; currTrans != endTrans; ++currTrans)
        {
            auto nextTrans = currTrans; ++nextTrans;
            llint cOrigStart = currTrans->first, cOrigEnd = currTrans->second.first, cDestStart = currTrans->second.second;
            output.emplace_back(cDestStart, cDestStart + (cOrigEnd - cOrigStart));
            output.emplace_back(cOrigEnd, nextTrans->first);
        }

        // Treat end
        llint eOrigStart = endTrans->first, eOrigEnd = endTrans->second.first, eDestStart = endTrans->second.second;
        // Full interval transforms
        if (end <= eOrigEnd)
        {
            output.emplace_back(eDestStart, eDestStart + (end - eOrigStart));
        }
        // Split in two parts, first transforms and second stays the same
        else
        {
            output.emplace_back(eDestStart, eDestStart + (eOrigEnd - eOrigStart));
            output.emplace_back(eOrigEnd, end);
        }
        return output;
    }
}

vector<pllint> process(vector<pllint> input, const map<llint, pllint> & map)
{
    vector<pllint> output;
    for (const pllint & inputPair : input)
    {
        vector<pllint> transformedPair = transform(inputPair.first, inputPair.second, map);
        output.insert(output.end(), transformedPair.begin(), transformedPair.end());
    }
    return output;
}

int main()
{
    ifstream fin("input.txt");
    vector<pllint> seeds; // List of tupples of seeds starts and ends
    map<llint, pllint> seeds2soil, soil2fert, fert2water, water2light, light2temp, temp2humid, humid2loc; // Maps having <origStart, <origEnd, destStart>>

    // Load input into variables
    string line = "", aux = "";
    llint seedStart = 0, seedLength = 0;

    // Read seeds
    getline(fin, line);
    istringstream sline(line);
    sline >> aux; // seeds:
    while(sline >> seedStart >> seedLength)
        seeds.push_back(make_pair(seedStart, seedStart + seedLength));
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
    vector<pllint> output;
    output = process(seeds, seeds2soil);
    output = process(output, soil2fert);
    output = process(output, fert2water);
    output = process(output, water2light);
    output = process(output, light2temp);
    output = process(output, temp2humid);
    output = process(output, humid2loc);

    auto it = output.begin();
    while (it != output.end()) 
    {
        if (it->first == it->second)
            it = output.erase(it);
        else
            ++it;
    }

    // Some intervals may be of length 0 so they should not exist
    // Delete them so not to take them in the minimum search
    llint minim = output.begin()->first;
    for (int i = 1; i < output.size(); ++i)
        minim = min(minim, output[i].first);

    cout << "Answer: " << minim << '\n';

    return 0;
}