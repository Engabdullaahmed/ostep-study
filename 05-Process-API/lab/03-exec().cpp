
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Main program started\n";

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed\n";
        return 1;
    }

    if (pid == 0) {
        cout << "Child: Before exec()\n";

        execlp("ls", "ls", "-l", nullptr);

        // This executes only if exec fails
        cerr << "exec failed\n";
        return 1;
    }
    else {
        wait(nullptr);

        cout << "Parent: Child execution completed\n";
    }

    return 0;
}
