#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
void fcfsDiskScheduling(int currentPosition, const vector<int>& requests) {
    int totalSeekTime = 0;
    int previousPosition = currentPosition;

    cout << "Seek Sequence: ";

    for (size_t i = 0; i < requests.size(); ++i) {
        int seekTime = abs(previousPosition - requests[i]);
        totalSeekTime += seekTime;
        cout << requests[i] << " ";
        previousPosition = requests[i];
    }
    
    cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main() {
    int currentPosition = 50; 
    
    
    vector<int> requests;
    int n, k;
    cout << "\nEnter the number of requests: ";
    cin >> n;
    cout << "\nRequests are : ";
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        requests.push_back(k);
    }
    cout << endl;
    fcfsDiskScheduling(currentPosition, requests);
    cout << endl;

    return 0;
}

//// input : 82 170 43 140 24 16 190