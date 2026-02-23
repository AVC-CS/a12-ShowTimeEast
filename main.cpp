#include <iostream>
#include <cstdlib>   // malloc/free
#include <cstdint>   // uintptr_t

using namespace std;

// DATA segment: initialized globals
int data1 = 100;
int data2 = 200;

// BSS segment: uninitialized globals (zeroed by OS)
int bss1;
int bss2;

static void printAddr(const char* label, const void* p) {
    cout << label << " " << p << endl;
}

void checkStack(int* parentAddr) {
    int childVar = 0;

    cout << "STACK" << endl;
    printAddr("parentAddr (main local address):", parentAddr);
    printAddr("&parentAddr (parameter address):", &parentAddr);
    printAddr("&childVar (child local address):", &childVar);

    uintptr_t p = reinterpret_cast<uintptr_t>(parentAddr);
    uintptr_t c = reinterpret_cast<uintptr_t>(&childVar);

    if (p > c) cout << "Stack grows: DOWN" << endl;
    else       cout << "Stack grows: UP" << endl;

    cout << endl;
}

int main() {
    int localVar = 10;

    void* heap1 = malloc(1024);
    void* heap2 = malloc(1024);

    cout << "=== MEMORY SEGMENT BOUNDARIES ===\n\n";

    cout << "TEXT" << endl;
    printAddr("Address of main:", reinterpret_cast<void*>(&main));
    printAddr("Address of checkStack:", reinterpret_cast<void*>(&checkStack));
    cout << endl;

    cout << "DATA" << endl;
    printAddr("data1 address:", &data1);
    cout << "data1 value: " << data1 << endl;
    printAddr("data2 address:", &data2);
    cout << "data2 value: " << data2 << endl;
    cout << endl;

    cout << "BSS" << endl;
    printAddr("bss1 address:", &bss1);
    cout << "bss1 value: " << bss1 << endl;
    printAddr("bss2 address:", &bss2);
    cout << "bss2 value: " << bss2 << endl;
    cout << endl;

    checkStack(&localVar);

    cout << "HEAP" << endl;
    printAddr("heap1 address:", heap1);
    printAddr("heap2 address:", heap2);

    uintptr_t h1 = reinterpret_cast<uintptr_t>(heap1);
    uintptr_t h2 = reinterpret_cast<uintptr_t>(heap2);

    if (h2 > h1) cout << "Heap grows: UP" << endl;
    else         cout << "Heap grows: DOWN" << endl;
    cout << endl;

    cout << "=== RELATIVE POSITION SUMMARY ===" << endl;
    cout << "Compare printed addresses above (typical: TEXT lowest, STACK highest)." << endl;

    free(heap1);
    free(heap2);

    return 0;
}
