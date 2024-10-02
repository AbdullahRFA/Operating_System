#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5

sem_t forks[N]; // Semaphore representing forks

void* philosopher(void* num) {
    int id = *(int*)num;
    
    // Philosopher attempts to pick up left and right forks
    sem_wait(&forks[id]);                  // Take left fork
    sem_wait(&forks[(id + 1) % N]);        // Take right fork
    
    printf("Philosopher %d is eating\n", id);
    
    // Philosopher finishes eating and puts down both forks
    sem_post(&forks[id]);                  // Put down left fork
    sem_post(&forks[(id + 1) % N]);        // Put down right fork
    
    printf("Philosopher %d is thinking\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores (forks)
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for philosophers to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}