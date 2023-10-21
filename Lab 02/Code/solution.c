/* Problem: The Senate Bus problem
This problem was originally based on the Senate bus at Wellesley College. Riders
come to a bus stop and wait for a bus. When the bus arrives, all the waiting
riders invoke boardBus, but anyone who arrives while the bus is boarding has
to wait for the next bus. The capacity of the bus is 50 people; if there are more
than 50 people waiting, some will have to wait for the next bus.
When all the waiting riders have boarded, the bus can invoke depart. If the
bus arrives when there are no riders, it should depart immediately.
Puzzle: Write synchronization code that enforces all of these constraints
*/

/* Here are the variables I used in my solution:

1 riders = 0
2 mutex = Semaphore (1)
3 multiplex = Semaphore (50)
4 bus = Semaphore (0)
5 allAboard = Semaphore (0)
mutex protects riders, which keeps track of how many riders are waiting;
multiplex makes sure there are no more than 50 riders in the boarding area.
Riders wait on bus, which gets signaled when the bus arrives. The bus waits
on allAboard, which gets signaled by the last student to board.
*/

/*
Here is the code for the bus. Again, we are using the “Pass the baton” pattern.

Bus problem solution (bus)
1 mutex . wait ()
2 if riders > 0:
3 bus . signal () # and pass the mutex
4 allAboard . wait () # and get the mutex back
5 mutex . signal ()
6
7 depart ()

When the bus arrives, it gets mutex, which prevents late arrivals from entering the boarding area. If there are no riders, it departs immediately. Otherwise,
it signals bus and waits for the riders to board.


Here is the code for the riders:

Bus problem solution (riders)
1 multiplex . wait ()
2 mutex . wait ()
3 riders += 1
4 mutex . signal ()
5
6 bus . wait () # and get the mutex
7 multiplex . signal ()
8
9 boardBus ()
10
11 riders -= 1
12 if riders == 0:
13 allAboard . signal ()
14 else :
15 bus . signal () # and pass the mutex


The multiplex controls the number of riders in the waiting area, although
strictly speaking, a rider doesn’t enter the waiting area until she increments
riders.
Riders wait on bus until the bus arrives. When a rider wakes up, it is
understood that she has the mutex. After boarding, each rider decrements
riders. If there are more riders waiting, the boarding rider signals bus and
pass the mutex to the next rider. The last rider signals allAboard and passes
the mutex back to the bus.
Finally, the bus releases the mutex and departs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_RIDERS 100

int riders = 0;
sem_t mutex, multiplex, bus, allAboard;

void *bus_thread(void *arg) {
    while (1) {
        sem_wait(&mutex);
        if (riders > 0) {
            sem_post(&bus);
            sem_wait(&allAboard);
        }
        sem_post(&mutex);
        printf("Bus departed\n");
        sleep(1);
    }
}

void *rider_thread(void *arg) {
    sem_wait(&multiplex);
    sem_wait(&mutex);
    riders++;
    sem_post(&mutex);

    sem_wait(&bus);
    sem_post(&multiplex);

    printf("Rider boarded\n");

    sem_wait(&mutex);
    riders--;
    if (riders == 0) {
        sem_post(&allAboard);
    } else {
        sem_post(&bus);
    }
    sem_post(&mutex);

    pthread_exit(NULL);
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&multiplex, 0, 50);
    sem_init(&bus, 0, 0);
    sem_init(&allAboard, 0, 0);

    pthread_t bus_t, rider_t[MAX_RIDERS];

    pthread_create(&bus_t, NULL, bus_thread, NULL);

    for (int i = 0; i < MAX_RIDERS; i++) {
        pthread_create(&rider_t[i], NULL, rider_thread, NULL);
        sleep(1);
    }

    for (int i = 0; i < MAX_RIDERS; i++) {
        pthread_join(rider_t[i], NULL);
    }

    pthread_cancel(bus_t);

    sem_destroy(&mutex);
    sem_destroy(&multiplex);
    sem_destroy(&bus);
    sem_destroy(&allAboard);

    return 0;
}
