#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void lookDiskScheduling(int currentPosition, std::vector<int>& requests, bool direction) {
    int totalSeekTime = 0;
    std::vector<int> seekSequence;

    // Sort the requests
    std::sort(requests.begin(), requests.end());

    // Find the position of the current head in the sorted requests
    int pos = std::find(requests.begin(), requests.end(), currentPosition) - requests.begin();

    // Add the current position to the sequence
    seekSequence.push_back(currentPosition);

    // If moving towards the end (high end)
    if (direction) {
        // Service requests to the right of the current position
        for (int i = pos; i < requests.size(); ++i) {
            seekSequence.push_back(requests[i]);
        }

        // Reverse direction: Service requests on the left side
        for (int i = pos - 1; i >= 0; --i) {
            seekSequence.push_back(requests[i]);
        }
    } else { // If moving towards the start (low end)
        // Service requests to the left of the current position
        for (int i = pos; i >= 0; --i) {
            seekSequence.push_back(requests[i]);
        }

        // Reverse direction: Service requests on the right side
        for (int i = pos + 1; i < requests.size(); ++i) {
            seekSequence.push_back(requests[i]);
        }
    }

    // Calculate total seek time
    for (size_t i = 1; i < seekSequence.size(); ++i) {
        totalSeekTime += std::abs(seekSequence[i] - seekSequence[i - 1]);
    }

    // Output the seek sequence and total seek time
    std::cout << "Seek Sequence: ";
    for (size_t i = 0; i < seekSequence.size(); ++i) {
        std::cout << seekSequence[i] << " ";
    }
    std::cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main() {
    int currentPosition = 50; // Initial position of the disk head
     std::vector<int> requests;
    requests.push_back(82);
    requests.push_back(170);
    requests.push_back(43);
    requests.push_back(140);
    requests.push_back(24);
    requests.push_back(16);
    requests.push_back(190);
    bool direction = true; // true for moving towards the end (right), false for start (left)

    lookDiskScheduling(currentPosition, requests, direction);

    return 0;
}