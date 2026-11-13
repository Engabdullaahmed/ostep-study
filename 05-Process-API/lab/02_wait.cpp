
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed\n";
        return 1;
    }

    if (pid == 0) {
        cout << "Child: Started\n";

        sleep(3);

        cout << "Child: Finished\n";
        return 0;
    }
    else {
        cout << "Parent: Waiting for child...\n";

        int status;
        wait(&status);

        cout << "Parent: Child has finished\n";
    }

    return 0;
}
