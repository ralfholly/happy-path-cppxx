#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-variable"

//////////////////////////////////////////////////
// Variadic templates are templates that support an arbitrary number of type
// parameters/arguments. There are two major use-cases for variadic templates:
// 1. Type-safe processing of an arbitrary number of arguments.
// 2. Perfect forwarding of arguments.


//////////////////////////////////////////////////
// Type-safe processing of an arbitrary number of arguments.
// This use-case always involves recursion. A recursive template successively
// strips one (or more) arguments and calls itself with a reduced number of
// arguments. A base template ensures that the recursion ends.

// Single-argument base template to end recursion.
template<typename Arg>
Arg combine(Arg arg) {
    return arg;
}


// Multi-argument recursive template, strips one argument (FirstArg) per invocation.
template<typename FirstArg, typename... RemArgs>
FirstArg combine(FirstArg first_arg, RemArgs... rem_args) {
    // Recursive call with first element stripped and remaining args expanded into
    // a comma-seperated list of arguments.
    return first_arg + combine(rem_args...);
}


void test_variadic_templates_recursive() {
    cout << combine(1, 2, 3) << endl;
    cout << combine((string)"a", (string)"b", (string)"hello") << endl;
}


//////////////////////////////////////////////////
// Perfect forwarding of arguments.
// The goal is to forward all arguments with the exact argument types to a
// handling function. A typical use-case is a factory function that forwards all
// received arguments to a constructor.


void my_func(int a, const string& b, float* c) {
    cout << "a: " << a << ", b: " << b << ", *c: " << *c << endl;
}


void my_func(double& a) {
    cout << "a: " << a << endl;
}


void my_func() {
    cout << "no args" << endl;
}


// Forwarding function. Note that 'Args&&' is _not_ an rvalue reference but a
// so-called 'universal reference'. Universal references accept any type.
template<typename... Args>
void invoke_my_func(Args&&... args) {
    // Perfectly forward all arguments, preserving the exact types, including qualifiers.
    my_func(std::forward<Args>(args)...);
}


void test_variadic_templates_forward() {
    int i{42};
    string s{"Howdy!"};
    float f{3.14f};
    invoke_my_func(i, s, &f);

    double d{3.141592};
    invoke_my_func(d);

    invoke_my_func();

    // invoke_my_func(i, i, i);     // Error: invalid combination of argument types.
    // invoke_my_func(d, s);        // Error: wrong number of arguments.
}


int main() {
    test_variadic_templates_recursive();
    test_variadic_templates_forward();

    return 0;
}
