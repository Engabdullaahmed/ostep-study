
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
/*
Goal: Measure the time required for Parent and Child to exchange messages using two Pipes.

fork create new child 
pip create new channle to communicatio 
read and write share data 
wait to finish child

each iteration child send byte to parent 
parent recieve the byte 
and still that cycle 
*/
using namespace std;

int main() {
    const int iterations = 10000;

    int pipe1[2]; // Child -> Parent
    int pipe2[2]; // Parent -> Child

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t rc = fork();

    if (rc < 0) {
        perror("fork");
        return 1;
    }

    if (rc == 0) {
        // Child
        close(pipe1[0]);
        close(pipe2[1]);

        char buffer;

        for (int i = 0; i < iterations; i++) {
            write(pipe1[1], "x", 1);
            read(pipe2[0], &buffer, 1);
        }

        close(pipe1[1]);
        close(pipe2[0]);
    }
    else {
        // Parent
        close(pipe1[1]);
        close(pipe2[0]);

        char buffer;

        struct timeval start, end;

        gettimeofday(&start, NULL);

        for (int i = 0; i < iterations; i++) {
            read(pipe1[0], &buffer, 1);
            write(pipe2[1], "x", 1);
        }

        gettimeofday(&end, NULL);

        long long start_us =
            start.tv_sec * 1000000LL + start.tv_usec;

        long long end_us =
            end.tv_sec * 1000000LL + end.tv_usec;

        long long total_time = end_us - start_us;

        cout << "Total time: "
             << total_time << " microseconds" << endl;

        cout << "Average time per exchange: "
             << (double)total_time / iterations
             << " microseconds" << endl;

        cout << "Approx. time per process handoff: "
             << (double)total_time / (2 * iterations)
             << " microseconds" << endl;

        close(pipe1[0]);
        close(pipe2[1]);

        waitpid(rc, NULL, 0);
    }

    return 0;
}
