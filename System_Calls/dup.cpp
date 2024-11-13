#include <iostream>
#include <fcntl.h> // for open
#include <unistd.h> // for dup, close

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    int new_fd = dup(fd); // Duplicate the file descriptor
    if (new_fd == -1) {
        std::cerr << "Error duplicating file descriptor\n";
    } else {
        std::cout << "Original FD: " << fd << ", New FD: " << new_fd << "\n";
    }

    close(fd);
    close(new_fd);
    return 0;
}
