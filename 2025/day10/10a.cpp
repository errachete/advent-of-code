#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int fill(vector<vector<int>>& dp, const vector<int> &buttons, int lights, int button, const int goal)
{
    if (button == dp[0].size())
        return lights == goal ? 0 : -2;

    if (dp[lights][button] != -1)
        return dp[lights][button];

    if (lights == goal)
    {
        dp[lights][button] = 0;
        return dp[lights][button];
    }

    // Press the button
    int press = fill(dp, buttons, lights^buttons[button], button+1, goal);
    // Don't press the button
    int no_press = fill(dp, buttons, lights, button+1, goal);

    if (press == -2 && no_press == -2)
        dp[lights][button] = -2;
    else if (press == -2)
        dp[lights][button] = no_press;
    else if (no_press == -2)
        dp[lights][button] = press + 1;
    else if (press + 1 < no_press)
        dp[lights][button] = press + 1;
    else
        dp[lights][button] = no_press;

    return dp[lights][button];
}

int main()
{
    ifstream fin("input.txt");

    int result = 0;
    string lights_str;
    while (fin >> lights_str)
    {
        // Process lights
        int lights = lights_str[1] == '#' ? 1 : 0;
        int size = lights_str.size() - 2;
        for (int i = 2; i < lights_str.size()-1; ++i)
        {
            lights <<= 1;
            if (lights_str[i] == '#')
                lights |= 1;
        }

        // Process buttons
        vector<int> buttons;
        string button_str;
        fin >> button_str;
        while (button_str[0] == '(')
        {
            istringstream sin(button_str);
            char aux;
            int num, button = 0;
            sin >> aux;
            while (sin >> num >> aux)
                button |= (1 << (size - num - 1));
            buttons.push_back(button);
            fin >> button_str;
        }

        // Fill DP table
        int max_lights = 1 << size;
        vector<vector<int>> dp(max_lights, vector<int>(buttons.size(), -1));
        fill(dp, buttons, 0, 0, lights);
        result += dp[0][0];
    }

    cout << "Result: " << result << '\n';
    return 0;
}