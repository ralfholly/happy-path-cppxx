
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

#define assert_type_is(obj, type) static_assert(is_same<decltype(obj), type>::value, "Type mismatch");


//////////////////////////////////////////////////
// Basic 'auto' type deduction.
//
void auto_with_values() {
    auto i = 42;
    assert_type_is(i, int);

    auto d = 3.14;
    assert_type_is(d, double);

    auto s = "The quick brown fox";
    assert_type_is(s, const char*);

    auto vec = vector<double>{1.0, 2.0, 3.0};
    assert_type_is(vec, vector<double>);

    auto str = string("The quick brown fox");
    assert_type_is(str, string);

    const auto cai = i;
    assert_type_is(cai, const int);

    const int ci = 42;
    auto ai = ci;
    assert_type_is(ai, int);            // const is dropped on value copy.

    volatile int vi = 42;
    auto ai2 = vi;
    assert_type_is(ai2, int);           // volatile is dropped on value copy.
}


//////////////////////////////////////////////////
// 'auto' type dedcution in conjunction with
// references.
//
void auto_with_references() {
    int i;
    auto& ri = i;
    assert_type_is(ri, int&);

    auto i2 = ri;
    assert_type_is(i2, int);            // Rerence is dropped on copy.

    auto& ri2 = ri;
    assert_type_is(ri2, int&);

    const auto& cri = ri;
    assert_type_is(cri, const int&);

    auto&& rvr = 42;                    // Universal reference auto&& ...
    assert_type_is(rvr, int&&);         // ... becomes rvalue reference.
//  auto& lvr = 42;                     // Error: lvale reference can't bind to rvalue.

    auto&& lvr = i;                     // Universal reference auto&& ...
    assert_type_is(lvr, int&);          // ... becomes lvalue reference.

    const auto&& crvr = 42;
    assert_type_is(crvr, const int&&);  // const rvalue reference.

//  const auto&& clvr = i;              // Error: does not compile (expected: type deduction to const int&).
}


//////////////////////////////////////////////////
// 'auto' type dedcution in conjunction with
// pointers..
//
void auto_with_pointers() {
    int i;
    auto* pi = &i;
    assert_type_is(pi, int*);

    auto* pi2 = pi;
    assert_type_is(pi2, int*);

    auto pi3 = pi;
    assert_type_is(pi3, int*);

    auto ppi1 = &pi;
    assert_type_is(ppi1, int**);

    auto** ppi2 = &pi;
    assert_type_is(ppi2, int**);

    auto* ppi3 = &pi;
    assert_type_is(ppi3, int**);

    const auto cpi = pi;                // const pointer to non-const int.
    *cpi = 42;
//  ++cpi;                              // Error.
    assert_type_is(cpi, int* const);
}


int main() {
    auto_with_values();
    auto_with_references();
    auto_with_pointers();

    return 0;
}
