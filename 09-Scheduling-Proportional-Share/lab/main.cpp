
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

/*
Lottery Scheduling:
- A proportional-share CPU scheduling algorithm.
- Each process receives a number of tickets.
- More tickets -> higher probability of winning the lottery.
- The scheduler generates a random winning ticket.
- The process that owns the winning ticket gets the CPU.
- Each winner runs for one time quantum.
- Winning does not decrease the process's tickets.
- Each process has a remainingTime counter.
- When remainingTime reaches 0, the process finishes and is removed.
- Its tickets are removed from the total active tickets.
*/

/*
Stride Scheduling:
- A deterministic CPU scheduling algorithm.
- Each process has Tickets, Stride, and Pass.
- Stride = K / Tickets.
- K is a fixed constant used to calculate Stride.
- More tickets -> smaller Stride.
- The scheduler selects the process with the lowest Pass.
- After running, Pass += Stride.
- Each process has a remainingTime counter.
- When remainingTime reaches 0, the process finishes and is removed.
*/
// we have three process and try to scheduling using two way  
const int K = 10000;

struct Process
{
    string name;
    int tickets;
    int wins = 0;

    int stride;
    int pass = 0;
};

// Lottery Scheduling
void lotteryScheduling(vector<Process> processes, int rounds)
{

    cout << "\n=== Lottery Scheduling ===\n";

    random_device rd;
    // gen number from one to number of ticket
    mt19937 gen(rd());

    int totalTickets = 0;

    for (auto &p : processes)
    {
        totalTickets += p.tickets;
    }

    uniform_int_distribution<int> dist(1, totalTickets);

    for (int i = 0; i < rounds; i++)
    {

        int winner = dist(gen);
        int counter = 0;

        for (auto &p : processes)
        {

            counter += p.tickets;

            if (counter >= winner)
            {
                p.wins++;

                cout << "Round " << i + 1
                     << " -> " << p.name << endl;

                break;
            }
        }
    }

    cout << "\nLottery Results:\n";

    for (auto &p : processes)
    {
        cout << p.name << " won "
             << p.wins << " times\n";
    }
}

// Stride Scheduling
void strideScheduling(vector<Process> processes, int rounds)
{

    cout << "\n=== Stride Scheduling ===\n";

    for (auto &p : processes)
    {
        p.stride = K / p.tickets;
        p.pass = 0;
        p.wins = 0;
    }

    for (int i = 0; i < rounds; i++)
    {

        int winnerIndex = 0;

        // Find process with lowest Pass
        for (int j = 1; j < processes.size(); j++)
        {

            if (processes[j].pass <
                processes[winnerIndex].pass)
            {

                winnerIndex = j;
            }
        }

        Process &winner = processes[winnerIndex];

        winner.wins++;

        cout << "Round " << i + 1
             << " -> " << winner.name
             << " | Pass: " << winner.pass;

        winner.pass += winner.stride;

        cout << " | New Pass: " << winner.pass << endl;
    }

    cout << "\nStride Results:\n";

    for (auto &p : processes)
    {
        cout << p.name << " won "
             << p.wins << " times\n";
    }
}

int main()
{

    vector<Process> processes = {
        {"A", 100},
        {"B", 50},
        {"C", 250}};

    int rounds = 20;

    lotteryScheduling(processes, rounds);

    strideScheduling(processes, rounds);

    return 0;
}
