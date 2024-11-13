#include <iostream>
#include <fcntl.h> // for open
#include <unistd.h> // for write, close

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    const char* text = "Hello, world!\n";
    ssize_t bytesWritten = write(fd, text, 13); // Write 13 bytes

    if (bytesWritten == -1) {
        std::cerr << "Error writing to file\n";
    } else {
        std::cout << "Wrote " << bytesWritten << " bytes to the file.\n";
    }

    close(fd);
    return 0;
}
