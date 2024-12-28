#include <iostream>
#include <fstream>

using namespace std;
using llint = long long int;


llint blockChecksum(int id, int init, int size)
{
    return llint(id) * size * (2*init + size-1) / 2;
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
    string disk;
    in >> disk;
    in.close();

    // Two pointers and file IDs, one for the front and one for the back
    int fIdx = 0, fFid = 0;
    int bIdx = ((disk.size()-1) % 2 == 0) ? disk.size()-1 : disk.size()-2, bFid = disk.size() / 2;
    int diskPos = 0;

    llint checksum = 0;
    bool fIsFile = true;
    // Traverse the disk until front pointer meets back pointer
    while (fIdx <= bIdx)
    {
        // If front pointer is on file, directly add to checksum
        if (fIsFile)
        {
            checksum += blockChecksum(fFid, diskPos, num(disk[fIdx]));
            diskPos += num(disk[fIdx]);
            ++fFid;
            ++fIdx;
            fIsFile = !fIsFile;
        }
        // If front pointer is on free space, use back pointer to move files
        else
        {
            // If back file is bigger than free space
            if (num(disk[bIdx]) > num(disk[fIdx]))
            {
                checksum += blockChecksum(bFid, diskPos, num(disk[fIdx]));
                diskPos += num(disk[fIdx]);
                disk[bIdx] = chr(num(disk[bIdx]) - num(disk[fIdx]));
                ++fIdx;
                fIsFile = !fIsFile;
            }
            // If back file is smaller or equal than free space
            else
            {
                checksum += blockChecksum(bFid, diskPos, num(disk[bIdx]));
                diskPos += num(disk[bIdx]);
                disk[fIdx] = chr(num(disk[fIdx]) - num(disk[bIdx]));
                bIdx -= 2;
                --bFid;
            }
        }
    }

    cout << "Result: " << checksum << endl;

    return 0;
}