#include <iostream>
#include <vector>
#include <algorithm>

void scanDiskScheduling(int currentPosition, std::vector<int> requests, int diskSize) {
    std::vector<int> seekSequence;
    int totalSeekTime = 0;

    // Sort the request array
    std::sort(requests.begin(), requests.end());

    // Process requests to the right of the current position
    for (int request : requests) {
        if (request >= currentPosition) {
            seekSequence.push_back(request);
            totalSeekTime += abs(currentPosition - request);
            currentPosition = request;
        }
    }

    // Move to the end of the disk
    totalSeekTime += abs(currentPosition - (diskSize - 1));
    currentPosition = diskSize - 1; // Move to end

    // Process requests to the left of the current position
    for (int i = requests.size() - 1; i >= 0; --i) {
        if (requests[i] < currentPosition) {
            seekSequence.push_back(requests[i]);
            totalSeekTime += abs(currentPosition - requests[i]);
            currentPosition = requests[i];
        }
    }

    // Output the seek sequence and total seek time
    std::cout << "Seek Sequence: ";
    for (int request : seekSequence) {
        std::cout << request << " ";
    }
    std::cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main() {
    int currentPosition = 50; // Initial position of the disk head
    std::vector<int> requests = { 82, 170, 43, 140, 24, 16, 190 };
    int diskSize = 200; // Total size of the disk

    scanDiskScheduling(currentPosition, requests, diskSize);

    return 0;
}