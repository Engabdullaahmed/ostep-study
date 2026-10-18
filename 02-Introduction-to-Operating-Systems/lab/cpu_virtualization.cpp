#include <iostream>
using namespace std;

// Represent a process
struct process
{
    string name;
    int curr_time;
    int remain_time;
};

int main()
{
    // Create 3 processes with different execution times
    process p1 = {"p1", 0, 5};
    process p2 = {"p2", 0, 3};
    process p3 = {"p3", 0, 4};

    // Time allowed for each process
    int quantum = 2;

    // Run P1 for one time quantum
    // p1.curr_time += quantum;
    // p1.remain_time -= quantum;
    // cout << p1.curr_time << endl;
    // cout << p1.remain_time << endl;

    int current = 0;
    while (p1.remain_time > 0 ||
           p2.remain_time > 0 ||
           p3.remain_time > 0)
    {
        int run_time;

        switch (current)
        {
        case 0:
            if (p1.remain_time > 0)
            {
                run_time = min(quantum, p1.remain_time);

                p1.curr_time += run_time;
                p1.remain_time -= run_time;

                cout << "CPU -> " << p1.name << endl;
            }
            else
            {
                cout << p1.name << " has finished" << endl;
            }
            break;

        case 1:
            if (p2.remain_time > 0)
            {
                run_time = min(quantum, p2.remain_time);

                p2.curr_time += run_time;
                p2.remain_time -= run_time;

                cout << "CPU -> " << p2.name << endl;
            }
            else
            {
                cout << p2.name << " has finished" << endl;
            }
            break;

        case 2:
            if (p3.remain_time > 0)
            {
                run_time = min(quantum, p3.remain_time);

                p3.curr_time += run_time;
                p3.remain_time -= run_time;

                cout << "CPU -> " << p3.name << endl;
            }
            else
            {
                cout << p3.name << " has finished" << endl;
            }
            break;
        }

        current = (current + 1) % 3; // to handle cycle can if 4 return to process one
    }
    cout << "All processes have finished." << endl;

    return 0;
}
