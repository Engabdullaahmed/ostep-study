
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed\n";
        return 1;
    }

    if (pid == 0) {
        cout << "Child: Running... PID = "
             << getpid() << endl;

        while (true) {
            cout << "Child: Working...\n";
            sleep(1);
        }
    }
    else {
        cout << "Parent: Child created\n";

        sleep(3);

        cout << "Parent: Sending SIGTERM\n";

        kill(pid, SIGTERM);

        int status;
        waitpid(pid, &status, 0);

        if (WIFSIGNALED(status)) {
            cout << "Child terminated by signal: "
                 << WTERMSIG(status) << '\n';
        }

        cout << "Parent: Finished\n";
    }

    return 0;
}
