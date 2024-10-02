#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t semaphore;
int counter = 0;
int thrd=0;

void* increment_counter(void* arg) {

    sem_wait(&semaphore); // Decrease semaphore
    thrd++;
    for (int i = 0; i < 1000000; i++) {
        counter++;
    }
    printf("Thread %d is finished with counter %d \n",thrd,counter);
    sem_post(&semaphore); // Increase semaphore
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    sem_init(&semaphore, 0, 1); // Initialize semaphore with value 1

    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semaphore);

    printf("Final counter: %d\n", counter);
    return 0;
}
