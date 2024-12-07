#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main()
{
    ifstream in("input.txt");

    vector<string> soup;
    string aux;
    while (in >> aux)
        soup.push_back(aux);
    in.close();

    string word = "XMAS";
    int appear = 0;
    // Horizontal forward
    for (int i = 0; i < soup.size(); ++i)
    {
        int w = 0;
        for (int j = 0; j < soup[i].size(); ++j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Horizontal backwards
    for (int i = 0; i < soup.size(); ++i)
    {
        int w = 0;
        for (int j = soup[i].size()-1; j >= 0; --j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Vertical downwards
    for (int j = 0; j < soup[0].size(); ++j)
    {
        int w = 0;
        for (int i = 0; i < soup.size(); ++i)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Vertical upwards
    for (int j = 0; j < soup[0].size(); ++j)
    {
        int w = 0;
        for (int i = soup.size()-1; i >= 0; --i)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Diagonal forward and downwards
    for (int k = soup.size()-1; k > 0; --k)
    {
        int w = 0;
        for (int i = k, j = 0; i < soup.size() && j < soup[i].size(); ++i, ++j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    for (int k = 0; k < soup[0].size(); ++k)
    {
        int w = 0;
        for (int i = 0, j = k; i < soup.size() && j < soup[i].size(); ++i, ++j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Diagonal backwards and upwards
    for (int k = 0; k < soup.back().size()-1; ++k)
    {
        int w = 0;
        for (int i = soup.back().size()-1, j = k; i >= 0 && j >= 0; --i, --j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    for (int k = soup.size()-1; k >= 0; --k)
    {
        int w = 0;
        for (int i = k, j = soup[i].size()-1; i >= 0 && j >= 0; --i, --j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Diagonal forward and upwards
    for (int k = 0; k < soup.size()-1; ++k)
    {
        int w = 0;
        for (int i = k, j = 0; i >= 0 && j < soup[i].size(); --i, ++j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    for (int k = 0; k < soup.back().size(); ++k)
    {
        int w = 0;
        for (int i = soup.size()-1, j = k; i >= 0 && j < soup[i].size(); --i, ++j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    // Diagonal backwards and downwards
    for (int k = 0; k < soup[0].size()-1; ++k)
    {
        int w = 0;
        for (int i = 0, j = k; i < soup.size() && j >= 0; ++i, --j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }
    for (int k = 0; k < soup.size(); ++k)
    {
        int w = 0;
        for (int i = k, j = soup[i].size()-1; i < soup.size() && j >= 0; ++i, --j)
        {
            if (soup[i][j] == word[w]) ++w;
            else w = soup[i][j] == word[0] ? 1 : 0;
            if (w == word.size())
            {
                w = 0;
                ++appear;
            }
        }
    }

    cout << "Result: " << appear << endl;

    return 0;
}