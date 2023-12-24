#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

// Different cards:    5,       4,       3,         3,         2,        2,        1
enum HandType { highCard, onePair, twoPair, threeKind, fullHouse, fourKind, fiveKind };

// Return true if card one < other
bool lessValueCard(const char one, const char other)
{   
    if (one == 'J' && other == 'J')
        return false;
    else if (one == 'J')
        return true;
    else if (other == 'J')
        return false;

    if (isdigit(one) && isdigit(other))
        return one < other;
    else if (isdigit(one))
        return true;
    else if (isdigit(other))
        return false;
    else
    {
        switch(one)
        {
            case 'T':
                if (other == 'T')
                    return false;
                else
                    return true;
            case 'Q':
                if (other == 'A' || other == 'K')
                    return true;
                else
                    return false;
            case 'K':
                if (other == 'A')
                    return true;
                else
                    return false;
            case 'A':
                return false;
        }
    }

    return false;
}

// Comparer between two strings (hands) according to card values instead of lexicographic
bool lessHandStr(const string & one, const string & other)
{
    for (int i = 0; i < one.size(); ++i) {
        if (one[i] != other[i])
            return lessValueCard(one[i], other[i]);
    }
    return false;
}

class Hand {
public:
    string handStr;
    HandType type;

    HandType computeType(const string & handStr)
    {
        unordered_map<char, int> groups;
        for (char c : handStr)
            ++groups[c];

        if (groups.count('J') && groups.size()>1) 
        {
            auto it = groups.begin();
            char maxKey = ' ';
            int maxValue = 0;
            while (it != groups.end())
            {
                if (it->second > maxValue && it->first != 'J')
                {
                    maxValue = it->second;
                    maxKey = it->first;
                }
                ++it;
            }

            groups[maxKey] += groups['J'];
            groups.erase('J');
        }
        
        if (groups.size() == 5) return highCard;
        if (groups.size() == 4) return onePair;
        if (groups.size() == 3)
        {
            for (auto kv : groups)
                if (kv.second == 3) return threeKind;
            return twoPair;
        }
        if (groups.size() == 2)
        {
            for (auto kv : groups)
                if (kv.second == 4) return fourKind;
            return fullHouse;
        }
        if (groups.size() == 1) return fiveKind;

        return highCard;
    }
    
    Hand(string handStr) 
    {
        this->handStr = handStr;
        this->type = computeType(handStr);
    }
};

// Comparer between two hands according to type of hand, or relaying in the comparison between handStr
struct handComparator
{
    bool operator()(const Hand & one, const Hand & other) const
    {
        if (one.type == other.type)
            return lessHandStr(one.handStr, other.handStr);
        else
            return one.type < other.type;

    }
};

int main() 
{
    map<Hand, int, handComparator> input;

    string hand;
    int value;
    ifstream fin("input.txt");
    while (fin >> hand >> value)
    {
        input[hand] = value;
    }
    fin.close();

    int result = 0, rank = 1;
    for (auto it = input.begin(); it != input.end(); ++it)
    {
        result += rank++ * it->second;
    }

    cout << "Answer: " << result << '\n';

    return 0;
}