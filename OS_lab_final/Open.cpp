#include <iostream>
#include <fcntl.h> // for open
#include <unistd.h> // for close
using namespace std;
int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644); // Create file with write permission
    if (fd == -1) {
        cerr << "Error opening file\n";
        return 1;
    }
    cout << "File opened successfully with descriptor " << fd << "\n";
    close(fd); // Close the file
    return 0;
}