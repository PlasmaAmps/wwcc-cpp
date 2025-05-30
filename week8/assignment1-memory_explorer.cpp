#include <iostream>
using namespace std;

// Function that modifies values using references
void modifyByReference(int &x, int &y) {
    x *= 10;
    y *= 10;
}

// Function that modifies values using pointers
void modifyByPointer(int *a, int *b) {
    if (a && b) { // Null pointer safety check
        *a *= 10;
        *b *= 10;
    }
}

int main() {
    cout << "MEMORY ADDRESS EXPLORER\n";
    cout << "-----------------------\n\n";

    // PART 1: Variable Memory Locations
    cout << "PART 1: Variable Memory Locations\n";
    cout << "---------------------------------\n";
    int intVar = 42;
    double doubleVar = 3.14;
    char charVar = 'A';

    cout << "Integer variable: " << intVar << " at address " << &intVar << endl;
    cout << "Double variable: " << doubleVar << " at address " << &doubleVar << endl;
    cout << "Character variable: '" << charVar << "' at address " << static_cast<void*>(&charVar) << "\n\n";

    // PART 2: Reference Demonstration
    cout << "PART 2: Reference Demonstration\n";
    cout << "-------------------------------\n";
    int x = 10, y = 20;
    cout << "Before reference function: x = " << x << ", y = " << y << endl;
    modifyByReference(x, y);
    cout << "After reference function: x = " << x << ", y = " << y << endl;
    cout << "(References allow direct modification of original variables)\n\n";

    // PART 3: Pointer Demonstration
    cout << "PART 3: Pointer Demonstration\n";
    cout << "-----------------------------\n";
    int a = 5, b = 15;
    cout << "Before pointer function: a = " << a << ", b = " << b << endl;
    cout << "Pointer addresses: a at " << &a << ", b at " << &b << endl;
    modifyByPointer(&a, &b);
    cout << "After pointer function: a = " << a << ", b = " << b << endl;
    cout << "(Pointers access original variables through their addresses)\n\n";

    // PART 4: Array and Pointer Relationship
    cout << "PART 4: Array and Pointer Relationship\n";
    cout << "--------------------------------------\n";
    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr; // points to the first element

    cout << "Array: [";
    for (int i = 0; i < 5; ++i) {
        cout << arr[i];
        if (i < 4) cout << ", ";
    }
    cout << "]\n";

    cout << "Array name address: " << arr << endl;
    cout << "First element address: " << &arr[0] << " (same as array name!)\n";
    cout << "Second element via pointer arithmetic: " << *(ptr + 1) << endl;
    cout << "Third element via pointer arithmetic: " << *(ptr + 2) << endl;

    cout << "\n(Pointer arithmetic shows how arrays and pointers are closely related)\n";

    return 0;
}
