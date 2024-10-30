#include <iostream>
#include <vector>
using namespace std;

int n = 5, m = 3; // Number of processes and resources
int f[5], ans[5], ind = 0;

int alloc[5][3] = {{0, 1, 0},  // P0 // Allocation Matrix
                   {2, 0, 0},  // P1
                   {3, 0, 2},  // P2
                   {2, 1, 1},  // P3
                   {0, 0, 2}}; // P4

int MAX[5][3] = {{7, 5, 3},  // P0 // MAX Matrix
                 {3, 2, 2},  // P1
                 {9, 0, 2},  // P2
                 {2, 2, 2},  // P3
                 {4, 3, 3}}; // P4

int avail[3] = {3, 3, 2}; // Available Resources

int need[5][3]; // Need Matrix

void display() {
    cout << "Process\t\tAllocation\t\tNeed\t\tAvailable" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t\t";
        for (int j = 0; j < m; j++) {
            cout << alloc[i][j] << " ";
        }
        cout << "\t\t\t";
        for (int j = 0; j < m; j++) {
            cout << need[i][j] << " ";
        }
        if (i == 0) { // Display available resources only once
            cout << "\t\t";
            for (int j = 0; j < m; j++) {
                cout << avail[j] << " ";
            }
        }
        cout << endl;
    }
}

// Banker's Algorithm: Find a safe sequence
void find_safe_sequence() {
    // Reset flags and index
    fill(f, f + n, 0);
    ind = 0;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Check if all processes are finished
    bool safe = true;
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            safe = false;
            cout << "The given sequence is not safe" << endl;
            break;
        }
    }

    if (safe) {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
    }
}

// Calculate Need Matrix
void Calculate_the_Need_matrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = MAX[i][j] - alloc[i][j];
        }
    }
}

// Check if a specific request is safe
void is_request_safe() {
    int req[3], pro_no;
    cout << "Enter process number (1-" << n << "): ";
    cin >> pro_no;

    // Validate process number
    if (pro_no < 1 || pro_no > n) {
        cout << "Invalid process number!" << endl;
        return;
    }

    cout << "Enter Request: ";
    for (int i = 0; i < m; i++) {
        cin >> req[i];
    }

    // Check if the request is valid and safe
    bool safe = true;
    for (int i = 0; i < m; i++) {
        if (req[i] > need[pro_no - 1][i] || req[i] > avail[i]) {
            safe = false;
            break;
        }
    }

    if (safe) {
        // Temporarily allocate resources
        for (int i = 0; i < m; i++) {
            avail[i] -= req[i];
            alloc[pro_no - 1][i] += req[i];
            need[pro_no - 1][i] -= req[i];
        }

        // Check if the system is still safe
        cout << "This request is safe. Recalculating safe sequence..." << endl;
        find_safe_sequence();

        // Restore original state after the safe check
        for (int i = 0; i < m; i++) {
            avail[i] += req[i];
            alloc[pro_no - 1][i] -= req[i];
            need[pro_no - 1][i] += req[i];
        }
    } else {
        cout << "This request is not safe." << endl;
    }
}

int main() {
    // Initialize finish array to track if a process has finished
    fill(f, f + n, 0);

    // Calculate the Need matrix
    Calculate_the_Need_matrix();

    cout << endl;
    display();
    cout << endl;

    // Find initial safe sequence
    find_safe_sequence();

    cout << endl;
    display();
    cout << endl;

    // Loop to check multiple requests for safety
    string response;
    while (true) {
        cout << "Do you want to check a request for safety? (yes/no): ";
        cin >> response;
        if (response == "yes" || response == "YES") {
            is_request_safe();
            cout << endl;
            display();
            cout << endl;
        } else {
            break;
        }
    }

    return 0;
}