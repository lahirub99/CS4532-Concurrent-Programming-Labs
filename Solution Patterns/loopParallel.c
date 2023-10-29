// Loop Parallel

// If each iteration in a loop only depends on that iteration results + read-only data, each iteration can run in a different thread
// As it’s based on data, also called data parallelism

// OpenMP example

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

# pragma omp parallel for num_threads(thread_count) reduction(+: approx)
for (i = 0; i < n -1 ; i++) {
    approx += f(a + i * h);
}
approx = h * approx;