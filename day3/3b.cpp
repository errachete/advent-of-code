#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main ()
{
    ifstream fin("input.txt");

    vector<vector<char>> schema;
    string line = "";
    while(getline(fin, line))
    {
        vector<char> row(line.size());
        for (int i = 0; i < line.size(); ++i)
            row[i] = line[i];
        schema.push_back(row);
    }
    fin.close();

    int total = 0;
    // Iterate over schematic
    for(int i = 0; i < schema.size(); ++i)
    {
        for (int j = 0; j < schema[i].size(); ++j)
        {   
            // If it may be a gear (it first has to be *)
            if (schema[i][j] == '*')
            {
                // Move around searching for numbers
                int ratio = 1;
                int numNumbers = 0;
                for (int k = -1; k <= 1 && numNumbers <= 2; ++k)
                {
                    for (int l = -1; l <= 1 && numNumbers <= 2; ++l)
                    {
                        // Check it is inside bounds
                        if (i+k >= 0 && i+k < schema.size() && j+l >= 0 && j+l < schema[i+k].size()) {
                            if (isdigit(schema[i+k][j+l]))
                            {
                                // If too many numbers stop
                                ++numNumbers;
                                if (numNumbers > 2)
                                    break;

                                // Move left and right to capture whole number
                                string number = "";
                                number.push_back(schema[i+k][j+l]);
                                schema[i+k][j+l] = '.';
                                int m = -1;
                                while (j+l+m >= 0 && isdigit(schema[i+k][j+l+m]))
                                {
                                    number.insert(0,1,schema[i+k][j+l+m]);
                                    schema[i+k][j+l+m] = '.';
                                    --m;
                                }
                                m = 1;
                                while (j+l+m < schema[i+k].size() && isdigit(schema[i+k][j+l+m]))
                                {
                                    number.push_back(schema[i+k][j+l+m]);
                                    schema[i+k][j+l+m] = '.';
                                    ++m;
                                }
                                ratio *= stoi(number);
                            }
                        }
                    }
                }

                // If it is indeed a gear (* and 2 numbers)
                if (numNumbers == 2)
                    total += ratio;
            }
        }
    }
    
    cout << "Answer: " << total << '\n';
    return 0;
}