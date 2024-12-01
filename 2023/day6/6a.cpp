#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main ()
{
    ifstream fin("input.txt");
    string aux = "";
    // Read times
    vector<int> times(4, 0);
    fin >> aux; // Time:
    for (int & t : times)
        fin >> t;
    // Read records
    vector<int> records(4, 0);
    fin >> aux; // Distance:
    for (int & r : records)
        fin >> r;

    fin.close();

    // d(t) = t * (T - t) = Tt - t^2
    // t(d) = (T +- sqrt(T^2 - 4d)) / 2
    int total = 1;
    for (int i = 0; i < times.size(); ++i) {
        float t1 = (times[i] - sqrt(times[i]*times[i] - 4*records[i])) / 2.0;
        float t2 = (times[i] + sqrt(times[i]*times[i] - 4*records[i])) / 2.0;

        total *= (ceil(t2-1) - floor(t1+1) + 1);
    }

    cout << "Answer: " << total << '\n';

    return 0;
}