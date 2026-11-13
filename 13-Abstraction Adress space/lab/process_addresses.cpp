
#include <iostream>
using namespace std;

int globalVar = 100;

int main()
{
    int localVar = 200;
    int *heapVar = new int(300);

    cout << "===== Process Address Space =====\n\n";

    cout << "Global Virtual Address: "
         << &globalVar << '\n';

    cout << "Stack Virtual Address:  "
         << &localVar << '\n';

    cout << "Heap Virtual Address:   "
         << heapVar << '\n';

    cout << "\nProcess is running...\n";

    delete heapVar;

    return 0;
}
