#include <iostream>
#include <fcntl.h> // for open
#include <unistd.h> // for read, close

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1); // Read up to 99 bytes
    if (bytesRead == -1) {
        std::cerr << "Error reading from file\n";
    } else {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        std::cout << "Read " << bytesRead << " bytes: " << buffer << "\n";
    }

    close(fd);
    return 0;
}
