#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-variable"

//////////////////////////////////////////////////
// General rule: if you can take the address,
// it's an lvalue otherwise, it's an rvalue.
// (rvalue: mostly temporaries and literals)
//

int foo() { return 23; }

void test_basics() {
    int x = 42;
    int *px = &x;           // 'x' is an lvalue.
    // int *px1 = &42;      // Error: '42' is an rvalue.
    // int *px2 = &foo();   // Error: 'foo's return value is an rvalue.
    int (*pfoo)() = &foo;   // 'foo' (the function itself) is an lvalue.
}


void test_lvalue_references() {
    int x = 42;
    int& rx = x;                // 'rx' is an lvalue reference...
    int* prx = &rx;             // ... which itself is an lvalue because we can take its address!

    const int& rfun = foo();    // Can bind a const lvalue reference to an rvalue.
                                // This extends the life-time of the temporary.
    // int& rfun = foo();       // Error: can't bind rvalue to a non-const lvalue reference.
}


void test_rvalue_references() {
    int&& rfun = foo();
    int* prfun = &rfun;         // rvalue reference itself is an lvalue, we can take its address!

    int&& r42 = 42;             // Can bind rvalue reference to literal.
    int x = 42;
    // int&& rx = x;            // Error: can't bind lvalue to an rvalue reference.
    int&& rx = std::move(x);    // std::move() converts lvalue to rvalue.

    // int&& rx2 = rx;          // Error: can't bind lvalue (rx) to rvalue reference.
    int&& rx2 = std::move(rx);  // That's the right way to duplicate rvalue references.

    // Wow! Changing rvalue through rvalue reference is possible.
    // Looks crazy, but is required to set object to invalid state
    // in move constructor/move assignment op.
    r42 = 23;
    rfun = 32;
    rx = 11;
}


int main() {
    test_basics();
    test_lvalue_references();
    test_rvalue_references();

    return 0;
}
