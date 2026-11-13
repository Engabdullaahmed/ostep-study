
#include <iostream>
#include <unistd.h>
#include <time.h>
// Goal: Measure the average time required to execute getpid().
using namespace std;

int main() {
    const int iterations = 1e6;

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t pid;

    for (int i = 0; i < iterations; i++) {
        pid = getpid();
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long long start_ns =
        start.tv_sec * 1000000000LL + start.tv_nsec;

    long long end_ns =
        end.tv_sec * 1000000000LL + end.tv_nsec;

    long long total_time = end_ns - start_ns;

    cout << "Process ID: " << pid << endl;
    cout << "Total time: " << total_time << " nanoseconds" << endl;

    cout << "Average time per call: "
         << (double)total_time / iterations
         << " nanoseconds" << endl;
/*
getpid() returns the current Process ID.
We measure the total execution time.
We divide by iterations to calculate the average.
*/
    return 0;
}
