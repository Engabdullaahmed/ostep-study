
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
/*
MLFQ CPU Scheduling Simulator

 Project Description

A simple CPU Scheduling Simulator implemented in C++ to demonstrate the basic concept of **Multi-Level Feedback Queue (MLFQ)** scheduling.

The program manages multiple processes using three priority queues (Q2, Q1, and Q0). Each queue has a different priority and time quantum.

New processes start in the highest-priority queue. The scheduler selects a process from the highest non-empty queue and executes it for the smaller of its remaining CPU time or the queue's time quantum.

If a process does not finish within its quantum, it moves to a lower-priority queue. The program tracks the current execution time and displays the order in which processes use the CPU.

 Main Objectives
- Understand how CPU scheduling works.
- Demonstrate priority-based scheduling.
- Understand Time Quantum and Process Demotion.
- Simulate the execution of multiple processes.
- Visualize the scheduling timeline.
*/
struct Process
{
    string name;
    int remainingTime;
};

int main()
{
    queue<Process> queues[3];

    // add processes to the highest priority queue
    queues[2].push({"A", 15});
    queues[2].push({"B", 5});

    int quantum[3] = {2, 5, 10};

    int currentTime = 0;

    // run while at least one queue is not empty
    while (!queues[0].empty() ||
           !queues[1].empty() ||
           !queues[2].empty())
    {

        // select the highest non-empty queue
        int q = 2;

        while (q >= 0 && queues[q].empty())
        {
            q--;
        }

        Process p = queues[q].front();
        queues[q].pop();

        int executionTime =
            min(p.remainingTime, quantum[q]);

        cout << currentTime << " - "
             << currentTime + executionTime
             << " : " << p.name
             << " (Q" << q << ")" << endl;

        currentTime += executionTime;
        p.remainingTime -= executionTime;

        if (p.remainingTime > 0)
        {
            if (q > 0)
            {
                queues[q - 1].push(p);
            }
            else
            {
                queues[q].push(p);
            }
        }
    }

    return 0;
}
