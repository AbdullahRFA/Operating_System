#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void scanDiskScheduling(int currentPosition, std::vector<int> &requests, int diskSize, bool direction)
{
    int totalSeekTime = 0;
    std::vector<int> seekSequence;

    // Add the current position to the list of requests to ensure it's included
    requests.push_back(currentPosition);

    // Sort the requests
    std::sort(requests.begin(), requests.end());

    // Find the position of the current head
    int pos = std::find(requests.begin(), requests.end(), currentPosition) - requests.begin();

    // If moving towards the end of the disk (high end)
    if (direction)
    {
        // Service requests to the right of the current position
        for (int i = pos; i < requests.size(); ++i)
        {
            seekSequence.push_back(requests[i]);
        }
        // Move to the end of the disk if needed
        if (requests.back() != diskSize - 1)
        {
            seekSequence.push_back(diskSize - 1); // End of the disk
        }

        // Reverse direction: Service requests on the left side
        for (int i = pos - 1; i >= 0; --i)
        {
            seekSequence.push_back(requests[i]);
        }
    }
    else
    { // If moving towards the start of the disk (low end)
        // Service requests to the left of the current position
        for (int i = pos; i >= 0; --i)
        {
            seekSequence.push_back(requests[i]);
        }
        // Move to the start of the disk if needed
        if (requests.front() != 0)
        {
            seekSequence.push_back(0); // Start of the disk
        }

        // Reverse direction: Service requests on the right side
        for (int i = pos + 1; i < requests.size(); ++i)
        {
            seekSequence.push_back(requests[i]);
        }
    }

    // Calculate total seek time
    for (size_t i = 1; i < seekSequence.size(); ++i)
    {
        totalSeekTime += std::abs(seekSequence[i] - seekSequence[i - 1]);
    }

    // Output the seek sequence and total seek time
    std::cout << "Seek Sequence: ";
    for (int i = 0; i < seekSequence.size(); ++i)
    {
        std::cout << seekSequence[i] << " ";
    }
    std::cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main()
{
    int currentPosition = 50; // Initial position of the disk head
    std::vector<int> requests;
    requests.push_back(82);
    requests.push_back(170);
    requests.push_back(43);
    requests.push_back(140);
    requests.push_back(24);
    requests.push_back(16);
    requests.push_back(190);
    
    int diskSize = 200;    // Total size of the disk
    bool direction = true; // true for moving towards the end (right), false for start (left)

    scanDiskScheduling(currentPosition, requests, diskSize, direction);

    return 0;
}