#include <iostream>
#include <fcntl.h> // for open
#include <unistd.h> // for close

int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644); // Create file with write permission
    if (fd == -1) {
        std::cerr << "Error opening file\n";
        return 1;
    }
    std::cout << "File opened successfully with descriptor " << fd << "\n";
    close(fd); // Close the file
    return 0;
}
