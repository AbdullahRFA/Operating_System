#include <iostream>
#include <fcntl.h>   // for openyes
#include <unistd.h>  // for close, read, write
#include <cstring>   // for strlen
using namespace std;
int main() {
    //int fd = open("example.txt", O_CREAT | O_RDWR, 0644); // Open file for read/write
    int fd = open("example.txt", O_CREAT | O_RDWR | O_TRUNC, 0644); 
    if (fd == -1) {
        cerr << "Error opening file\n";
        return 1;
    }

    cout << "File opened successfully with descriptor " << fd << "\n";

    // Ask user if they want to write to the file
    string response;
    cout << "Do you want to write something to the file? (yes/no): ";
    cin >> response;

    if (response == "yes") {
        cin.ignore(); // Clear the newline left in the input buffer
        string input;
        cout << "Enter text to write to the file: ";
        getline(cin, input);

        // Write to file
        ssize_t bytes_written = write(fd, input.c_str(), input.length());
        if (bytes_written == -1) {
            cerr << "Error writing to file\n";
            close(fd);
            return 1;
        }
        cout << "Text written to file successfully.\n";
    }

    // Ask user if they want to read from the file
    cout << "Do you want to read the content of the file? (yes/no): ";
    cin >> response;

    if (response == "yes") {
        // Move the file pointer to the beginning of the file for reading
        lseek(fd, 0, SEEK_SET);

        // Read the content of the file
        char buffer[1024];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read == -1) {
            cerr << "Error reading from file\n";
            close(fd);
            return 1;
        }

        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        cout << "File content:\n" << buffer << "\n";
    }

    // Close the file
    close(fd);
    return 0;
}