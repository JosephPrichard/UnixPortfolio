#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

//Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
//       n: 0  1  2  3  4  5  6   7   8  ...

int numThreads = 0;

void* compute_fib(void* ptr) {
    intptr_t n = (intptr_t) ptr;

    if (n <= 1) {
        return (void*) n;
    }

    pthread_t thread1;
    pthread_t thread2;

    intptr_t n1 = n - 1;
    intptr_t n2 = n - 2;

    if (pthread_create(&thread1, NULL, compute_fib, (void*) n1)) {
        puts("Cannot create thread.");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, compute_fib, (void*) n2)) {
        puts("Cannot create thread.");
        exit(1);
    }

    numThreads += 2;

    void* r1;
    pthread_join(thread1, &r1);

    void* r2;
    pthread_join(thread2, &r2);

    intptr_t r = ((intptr_t) r1) + ((intptr_t) r2);
    printf("%d\n", r);

    return (void*) r;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(1);
    }

    pthread_t thread1;

    intptr_t n1 = atoi(argv[1]);

    if (pthread_create(&thread1, NULL, compute_fib, (void*) n1)) {
        puts("Cannot create thread.");
        exit(1);
    }

    numThreads++;

    void* rPtr;
    pthread_join(thread1, &rPtr);

    printf("\nResult: %d\n", rPtr);
    printf("\n# of threads: %d\n", numThreads);
    exit(0);
}
