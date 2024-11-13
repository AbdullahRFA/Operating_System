#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    pid_t p;
    printf("Before fork\n");
    
    p = fork();
    
    if (p < 0) {
        // Error handling for fork failure
        perror("Fork failed");
        return 1;
    }
    
    if (p == 0) { // Child process
        printf("I am the child having ID %d\n", getpid());
        printf("My parent's ID is %d\n", getppid());
    } else { // Parent process
        wait(NULL); // Wait for child process to complete
        printf("My child's ID is %d\n", p);
        printf("I am the parent having ID %d\n", getpid());
    }
    
    printf("Common\n");
    return 0;
}
