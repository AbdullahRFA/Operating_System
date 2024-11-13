#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t t;
    t = fork();
    
    if (t < 0) {
        // Error handling for fork failure
        perror("Fork failed");
        return 1;
    }

    if (t == 0) { // Child process
        printf("Child having ID %d\n", getpid());
    } else { // Parent process
        printf("Parent having ID %d\n", getpid());
        sleep(15); // Parent sleeps; run `ps` command during this time
    }

    return 0;
}
