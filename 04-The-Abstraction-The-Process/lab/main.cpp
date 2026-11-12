#include <bits/stdc++.h>
using namespace std;
/*
# process Lifecycle simulator

A simple C++ project that simulates how an operating system manages processes throughout their lifecycle

project demonstrates process creation process states CPU execution I/O operations and context switching

It also implements FCFS scheduling and calculates performance metrics such as CPU utilization waiting time response time and turnaround time

our goal is to understand how the os manage processes and shares CPU resources in effecient way
*/
// the four type of state of process
enum class State
{
    READY,
    RUNNING,
    BLOCKED,
    EXIT
};

struct Process
{
    int pid;

    int cpuBeforeIO;
    int ioBurst;
    int cpuAfterIO;

    int remainingCPU;
    int remainingIO;

    int waitingTime = 0;
    int responseTime = -1;
    int completionTime = 0;

    bool hasIO;
    bool ioCompleted = false;

    State state = State::READY;
};

string getState(State state)
{
    switch (state)
    {
    case State::READY:
        return "READY";
    case State::RUNNING:
        return "RUNNING";
    case State::BLOCKED:
        return "BLOCKED";
    case State::EXIT:
        return "EXIT";
    }

    return "UNKNOWN";
}

int main()
{

    // create processes
    vector<Process> processes = {
        {0, 3, 2, 2, 3, 0, 0, -1, 0, true},
        {1, 4, 0, 0, 4, 0, 0, -1, 0, false},
        {2, 2, 3, 1, 2, 0, 0, -1, 0, true}};

    int time = 0;
    int completed = 0;
    int contextSwitches = 0;
    int busyTime = 0;

    int currentProcess = -1;
    int lastProcess = -1;

    vector<string> timeline;

    while (completed < processes.size())
    {

        // 1. Handle I/O completion
        for (auto &p : processes)
        {

            if (p.state == State::BLOCKED && p.remainingIO == 0)
            {

                p.state = State::READY;
                p.ioCompleted = true;
                p.remainingCPU = p.cpuAfterIO;
            }
        }

        // 2. Select next READY process (FCFS)
        if (currentProcess == -1)
        {

            for (int i = 0; i < processes.size(); i++)
            {

                if (processes[i].state == State::READY)
                {
                    currentProcess = i;
                    break;
                }
            }
        }

        // processes that were blocked
        // at the beginning of this time unit
        vector<int> blockedProcesses;

        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].state == State::BLOCKED)
            {
                blockedProcesses.push_back(i);
            }
        }

        // 3. Execute CPU
        if (currentProcess != -1)
        {

            Process &p = processes[currentProcess];

            if (p.pid != lastProcess)
            {
                if (lastProcess != -1)
                    contextSwitches++;

                lastProcess = p.pid;
            }

            p.state = State::RUNNING;

            if (p.responseTime == -1)
                p.responseTime = time;

            p.remainingCPU--;

            busyTime++;
            timeline.push_back("P" + to_string(p.pid));

            // CPU burst completed
            if (p.remainingCPU == 0)
            {

                if (p.hasIO && !p.ioCompleted)
                {

                    // Process requests I/O
                    p.state = State::BLOCKED;
                    p.remainingIO = p.ioBurst;
                }
                else
                {

                    // Process finished
                    p.state = State::EXIT;
                    p.completionTime = time + 1;
                    completed++;
                }

                currentProcess = -1;
            }
        }
        else
        {

            timeline.push_back("IDLE");
        }

        // 4. Update waiting time
        for (auto &p : processes)
        {
            if (p.state == State::READY)
                p.waitingTime++;
        }

        // 5. Update I/O operations
        for (int i : blockedProcesses)
        {
            if (processes[i].remainingIO > 0)
                processes[i].remainingIO--;
        }

        time++;
    }

    // 6. Display execution timeline
    cout << "\n========== CPU TIMELINE ==========\n";

    for (int i = 0; i < timeline.size(); i++)
    {
        cout << i << " [" << timeline[i] << "] ";
    }

    cout << time << "\n";

    // 7. Display process information
    cout << "\n========== PROCESS REPORT ==========\n";

    cout << left
         << setw(10) << "PID"
         << setw(15) << "STATE"
         << setw(15) << "WAITING"
         << setw(15) << "RESPONSE"
         << setw(15) << "COMPLETION"
         << "\n";

    int totalWaiting = 0;
    int totalTurnaround = 0;
    int totalResponse = 0;

    for (const auto &p : processes)
    {

        cout << left
             << setw(10) << p.pid
             << setw(15) << getState(p.state)
             << setw(15) << p.waitingTime
             << setw(15) << p.responseTime
             << setw(15) << p.completionTime
             << "\n";

        totalWaiting += p.waitingTime;
        totalTurnaround += p.completionTime;
        totalResponse += p.responseTime;
    }

    // 8. Performance metrics
    cout << "\n========== PERFORMANCE ==========\n";

    cout << fixed << setprecision(2);

    cout << "CPU Utilization: "
         << (double)busyTime / time * 100 << "%\n";

    cout << "Average Waiting Time: "
         << (double)totalWaiting / processes.size() << "\n";

    cout << "Average Turnaround Time: "
         << (double)totalTurnaround / processes.size() << "\n";

    cout << "Average Response Time: "
         << (double)totalResponse / processes.size() << "\n";

    cout << "Context Switches: "
         << contextSwitches << "\n";

    cout << "Total Execution Time: "
         << time << "\n";

    return 0;
}
