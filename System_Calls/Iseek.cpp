#include <iostream>
#include <fcntl.h> // for open
#include <unistd.h> // for lseek, close

int main() {
    int fd = open("example.txt", O_RDWR);
    if (fd == -1) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    off_t offset = lseek(fd, 5, SEEK_SET); // Move the file pointer 5 bytes from the start
    if (offset == -1) {
        std::cerr << "Error seeking in file\n";
    } else {
        std::cout << "File pointer set to position " << offset << "\n";
    }

    close(fd);
    return 0;
}
