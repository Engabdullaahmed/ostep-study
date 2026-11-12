/* Multiprocessor Scheduling Simulator
 * A C++ project that simulates how an operating system
 * schedules processes across multiple CPU cores.
 *
 * The project implements and compares:
 * - Single-Queue Multiprocessor Scheduling (SQMS)
 * - Job Migration
 * - Work Stealing
 *
 * The goal is to understand how different scheduling
 * approaches affect CPU utilization load balancing
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;
    int total_cpu_time;
    int remian_time;
};

void SQMS(vector<Process> processes, int number_cpu, int quantum)
{

    queue<Process> readyQueue;

    for (auto p : processes){
        readyQueue.push(p);
    }

    vector<int> cpu(number_cpu, -1);
    vector<int> timeused(number_cpu, 0);

    cout << "\n=== SQMS ===\n";

    while (!readyQueue.empty() ||
           count(cpu.begin(), cpu.end(), -1) != number_cpu)
    {

        for (int i = 0; i < number_cpu; i++)
        {

            if (cpu[i] == -1 && !readyQueue.empty())
            {
                cpu[i] = readyQueue.front().id;
                readyQueue.pop();
                timeused[i] = 0;
            }

            if (cpu[i] != -1)
            {
                cout << "CPU " << i << " runs P" << cpu[i] << endl;
                timeused[i]++;

                // process finishes or quantum expires
                if (timeused[i] == quantum)
                {
                    cout << "CPU " << i << " releases P" << cpu[i] << endl;
                    cpu[i] = -1;
                }
            }
        }
    }
}

int main()
{

    vector<Process> processes = {
        {1, 5, 5},
        {2, 4, 4},
        {3, 3, 3}};

    int number_cpu = 2;
    int quantum = 2;

    SQMS(processes, number_cpu, quantum);

    return 0;
}
