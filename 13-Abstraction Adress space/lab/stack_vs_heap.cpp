
#include <iostream>
using namespace std;

void stackExample() {
    int x = 10;
    int y = 20;

    cout << "\n===== Stack Example =====\n";

    cout << "x Address: " << &x << '\n';
    cout << "y Address: " << &y << '\n';

    cout << "x Value: " << x << '\n';
    cout << "y Value: " << y << '\n';
}

void heapExample() {
    int* ptr = new int(100);

    cout << "\n===== Heap Example =====\n";

    cout << "Pointer Address: " << &ptr << '\n';
    cout << "Heap Address:    " << ptr << '\n';
    cout << "Heap Value:      " << *ptr << '\n';

    delete ptr;
}

int main() {
    stackExample();

    heapExample();

    return 0;
}
