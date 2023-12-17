#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
using llint = long long int;


int main ()
{
    ifstream fin("input.txt");
    string aux = "";
    // Read times
    vector<llint> times(4, 0);
    fin >> aux; // Time:
    for (llint & t : times)
        fin >> t;
    // Read records
    vector<llint> records(4, 0);
    fin >> aux; // Distance:
    for (llint & r : records)
        fin >> r;

    fin.close();

    // Join times and records to create a single number
    llint time = times.back(), record = records.back();
    for (int i = times.size()-2; i >= 0; --i) {
        time += times[i] * pow(10, ceil(log10(time)));
        record += records[i] * pow(10, ceil(log10(record)));
    }


    // d(t) = t * (T - t) = Tt - t^2
    // t(d) = (T +- sqrt(T^2 - 4d)) / 2
    float t1 = (time - sqrt(time*time - 4*record)) / 2.0;
    float t2 = (time + sqrt(time*time - 4*record)) / 2.0;
    
    llint total = ceil(t2-1) - floor(t1+1) + 1;

    cout << "Answer: " << total << '\n';

    return 0;
}