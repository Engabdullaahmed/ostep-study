#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;
/*
    if we have task 1 and task 2 willl be out put like that
    task 1
    task 2
    task 1
    task 1
    task 2
    task 1
     Multiple things running together
*/
void task1()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Task 1\n";
    }
}

void task2()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Task 2\n";
    }
}

int counter = 0; // share data
mutex mtx;       // help me to protect that share data
void increament()
{
    for (int i = 0; i < 100000; i++)
    {
        mtx.lock();
        counter++;
        mtx.unlock();
    }
}
int main()
{
    // thread t1(task1);
    // thread t2(task2);

    thread t1(increament);
    thread t2(increament);
    t1.join();
    // wait untill thread finish
    t2.join();
    // after we add mutex the counter will be Counter: 200000 as we have been saved the shareed data
    cout << "Counter: " << counter << endl;

    // the counter not 20000 which has been process run together
    // not sequential and two is share data has been change it
    // that is race condition

    // like we have bank account and two man has make operation at bank account at same
    // time
    /*
    join = synchronization of thread completion
    mutex = synchronization/protection of shared data
    */
    return 0;
}
