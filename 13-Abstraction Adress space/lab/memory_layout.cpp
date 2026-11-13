
#include <iostream>
using namespace std;

// global variable: Data Segment
int globalVar = 100;

// Function: Code Segment
void myFunction()
{
    cout << "Inside myFunction\n";
}

int main()
{
    // local variable: Stack
    int localVar = 20;

    // Dynamic allocation: Heap store at heap
    int *heapVar = new int(50);

    cout << "===== Memory Layout =====\n\n";

    cout << "Code Address:   " // function location 
         << (void *)myFunction << '\n';

    cout << "Global Address: " // global variable location 
         << &globalVar << '\n';

    cout << "Stack Address:  " // stack whcih location of local varialbe 
         << &localVar << '\n';

    cout << "Heap Address:   " // store at dynamic memroy 
         << heapVar << '\n';

    cout << "\n===== Values =====\n";

    cout << "Global Value: " << globalVar << '\n';
    cout << "Stack Value:  " << localVar << '\n';
    cout << "Heap Value:   " << *heapVar << '\n';

    delete heapVar;

    return 0;
}
