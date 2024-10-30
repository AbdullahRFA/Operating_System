#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
void sstfDiskScheduling(int currentPosition, vector<int> &requests)
{
    int totalSeekTime = 0;
    vector<int> seekSequence;

    while (!requests.empty())
    {
        
        int closestIndex = 0;
        int minimumDistance = abs(currentPosition - requests[0]);

        for (int i = 1; i < requests.size(); ++i)
        {
            int distance = abs(currentPosition - requests[i]);
            if (distance < minimumDistance)
            {
                closestIndex = i;
                minimumDistance = distance;
            }
        }

        
        int closestRequest = requests[closestIndex];
        totalSeekTime += minimumDistance;
        currentPosition = closestRequest;
        seekSequence.push_back(closestRequest);

        requests.erase(requests.begin() + closestIndex);
    }

   
    cout << "Seek Sequence: ";
    for (int i = 0; i < seekSequence.size(); ++i)
    {
        cout << seekSequence[i] << " ";
    }
    cout << "\nTotal Seek Time: " << totalSeekTime << "\n";
}

int main()
{
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
    sstfDiskScheduling(currentPosition, requests);
    cout << endl;

    return 0;
}

// input : 82 170 43 140 24 16 190