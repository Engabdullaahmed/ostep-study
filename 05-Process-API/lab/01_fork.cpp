
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Before fork()\n";

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed\n";
        return 1;
    }
    else if (pid == 0) {
        // Child process
        cout << "\n[Child Process]\n";
        cout << "Child PID: " << getpid() << '\n';
        cout << "Parent PID: " << getppid() << '\n';
    }
    else {
        // Parent process
        cout << "\n[Parent Process]\n";
        cout << "Parent PID: " << getpid() << '\n';
        cout << "Child PID: " << pid << '\n';
    }

    return 0;
}
