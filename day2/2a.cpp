#include <iostream>
#include <fstream>
#include <sstream>

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
        bool possible = true;
        while (sline >> number >> colour) 
        {
            if (colour.back() == ',' || colour.back() == ';')
                colour.pop_back();
            
            if (colour == "red") 
            {
                if (number > 12) 
                {
                    possible = false;
                    break;
                }
            }
            else if (colour == "green")
            {
                if (number > 13) 
                {
                    possible = false;
                    break;
                }
            }
            else
            {
                if (number > 14)
                {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible)
            total += id;

    }
    fin.close();

    cout << "Answer: " << total << '\n';
    return 0;
}