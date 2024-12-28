#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using llint = long long int;


llint blockChecksum(llint id, int init, int size)
{
    return id * size * (2*init + size-1) / 2;
}

int num(char c)
{
    return c - '0';
}

char chr(int n)
{
    return n + '0';
}

int main()
{
    ifstream in("input.txt");
    string diskStr;
    in >> diskStr;
    in.close();

    vector<int> disk(diskStr.size(), 0), diskPos(diskStr.size(), 0);
    disk[0] = num(diskStr[0]);
    diskPos[0] = 0;
    for (int i = 1; i < diskStr.size(); ++i)
    {
        disk[i] = num(diskStr[i]);
        diskPos[i] = diskPos[i-1] + disk[i-1];
    }

    // Pointer to next file to be moved and ID (starts in last file)
    int fileIdx = ((disk.size()-1) % 2 == 0) ? disk.size()-1 : disk.size()-2, fileId = disk.size() / 2;

    llint checksum = 0;
    while (fileIdx >= 0)
    {
        // For each file, look for a place to move it
        int gapIdx = 1;
        while (gapIdx < fileIdx && disk[gapIdx] < disk[fileIdx]) gapIdx += 2;
        // If file could not be moved, directly add to checksum
        if (gapIdx > fileIdx)
            checksum += blockChecksum(fileId, diskPos[fileIdx], disk[fileIdx]);
        // If file was moved, also update disk information
        else
        {
            checksum += blockChecksum(fileId, diskPos[gapIdx], disk[fileIdx]);
            disk[gapIdx] -= disk[fileIdx];
            diskPos[gapIdx] += disk[fileIdx];
        }
        fileIdx -= 2;
        --fileId;
    }

    cout << "Result: " << checksum << endl;

    return 0;
}