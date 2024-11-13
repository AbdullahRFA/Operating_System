#include <iostream>
#include <vector>
using namespace std;

int n = 5, m = 4; // Number of processes and resources
int f[5], ans[5], ind = 0, req[4], check_p[5];
int pro_no;

int alloc[5][4] = {{2, 0, 0, 1},  // P0 // Allocation Matrix
                   {3, 1, 2, 1},  // P1
                   {2, 1, 0, 3},  // P2
                   {1, 3, 1, 2},  // P3
                   {1, 4, 3, 2}}; // P4

int MAX[5][4] = {{4, 2, 1, 2},  // P0 // MAX Matrix
                 {5, 2, 5, 2},  // P1
                 {2, 3, 1, 6},  // P2
                 {1, 4, 2, 4},  // P3
                 {3, 6, 6, 5}}; // P4

int avail[4] = {3, 3, 2, 1}; // Available Resources

int need[5][4]; // Need Matrix

void display()
{
    cout << "Process\t\tAllocation\t\tMAX\t\tNeed\t\tAvailable" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << alloc[i][j] << " ";
        }
        cout << "\t\t";
        for (int j = 0; j < m; j++)
        {
            cout << MAX[i][j] << " ";
        }
        cout << "\t";
        for (int j = 0; j < m; j++)
        {
            cout << need[i][j] << " ";
        }
        if (i == 0)
        { // Display available resources only once
            cout << "\t";
            for (int j = 0; j < m; j++)
            {
                cout << avail[j] << " ";
            }
        }
        cout << endl;
    }
}

// Banker's Algorithm: Find a safe sequence
void find_safe_sequence()
{
    // Reset flags and index
    fill(f, f + n, 0);
    ind = 0;

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        flag = 1;
                        // cout<<"Does not satisty the P"<<k+1<<endl;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                    {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Check if all processes are finished
    bool safe = true;
    for (int i = 0; i < n; i++)
    {
        if (f[i] == 0)
        {
            safe = false;

            for (int i = 0; i < n; i++)
            {

                if (ans[i] == 0)
                {
                    cout << " P" << i + 1 << " is not satisfied with the available reasource" << endl;
                }
                else
                {
                    cout << " P" << i + 1 << " is satisfied with the available reasource" << endl;
                }
            }
            cout << "The given sequence is not safe" << endl;
            cout << "So, The resource request is not granted" << endl;

            for (int i = 0; i < m; i++)
            {
                avail[i] += req[i];
                alloc[pro_no - 1][i] -= req[i];
                need[pro_no - 1][i] += req[i];
                MAX[pro_no - 1][i] += req[i];
            }
            break;
        }
    }

    if (safe)
    {
        cout << "So, The resource request is granted" << endl;
        cout << "Following is the SAFE Sequence:" << endl;
        for (int i = 0; i < n - 1; i++)
            cout << " P" << ans[i] << " ->";
        cout << " P" << ans[n - 1] << endl;
    }
}

// Calculate Need Matrix
void calculate_need_matrix()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = MAX[i][j] - alloc[i][j];
        }
    }
}

// Check if a specific request is safe and allocate resources if safe
void is_request_safe()
{

    cout << "Enter process number (1-" << n << "): ";
    cin >> pro_no;

    // Validate process number
    if (pro_no < 1 || pro_no > n)
    {
        cout << "Invalid process number!" << endl;
        return;
    }

    cout << "Enter Request for resources (separated by spaces): ";
    for (int i = 0; i < m; i++)
    {
        cin >> req[i];
    }

    // Check if the request is valid and safe
    bool safe = true;
    for (int i = 0; i < m; i++)
    {
        if (req[i] > need[pro_no - 1][i] || req[i] > avail[i])
        {
            safe = false;
            break;
        }
    }

    if (safe)
    {
        // Temporarily allocate resources

        for (int i = 0; i < m; i++)
        {
            avail[i] -= req[i];
            alloc[pro_no - 1][i] += req[i];
            need[pro_no - 1][i] -= req[i];
            MAX[pro_no - 1][i] -= req[i];
        }

        // After confirming the system remains in a safe state, keep the allocation
        cout << "The resources have been allocated to process P" << pro_no - 1 << "." << endl;
    }
    else
    {
        cout << "This request is not safe and cannot be allocated." << endl;
    }
}
int main()
{
    // Initialize finish array to track if a process has finished
    fill(f, f + n, 0);
    fill(check_p, check_p + n, 0);

    // Calculate the Need matrix
    calculate_need_matrix();

    cout << endl;
    display();
    cout << endl;

    // Loop to check multiple requests for safety
    string response;
    while (true)
    {
        cout << "Do you want to check a request for safety? (yes/no): ";
        cin >> response;
        if (response == "yes" || response == "YES")
        {
            is_request_safe();
            cout << endl;
            display();
            cout << endl;
        }
        else
        {
            break;
        }
    }

    // Find initial safe sequence
    find_safe_sequence();

    cout << endl;
    display();
    cout << endl;

    return 0;
}