#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

//////////////////////////////////////////////////
// Lambda expressions are function-like objects
// that allow easy, in-place definition of
// functionality. Lambda expressions save you
// from having to write out-of-place functors
// or global functions.
//
void test_lambda_simple() {
    vector<int> scores { 101, 190, -2, 22, 39 };

    // Use a lambda expression as an in-place predicate.
    auto target = find_if(scores.begin(), scores.end(),
        [](int score) -> bool {   // Lambda expression takes an int and returns a bool.
            return score < 0;
        }
    );

    assert(*target == -2);
}


//////////////////////////////////////////////////
// Lambda expressions can be stored in auto
// variables and thus can be used to emulate local
// (nested) functions.
//
void test_lambda_stored() {
    auto my_sum = [](int a, int b) -> int {
        return a + b;
    };
    assert(my_sum(1, 2) == 3);
}


//////////////////////////////////////////////////
// Objects from outside of the lambda expression
// must be captured (imported) or else are not
// accessible.
//
void test_captures() {
    int answer = 42;

    // No capture.
    auto fun1 = []() {
        // assert(answer == 42);    // Error: 'answer' is not visible.
    };

    // Capture by value.
    // 'answer' inside lambda is a copy of the original 'answer' value.
    auto fun2 = [answer]() {
        assert(answer == 42);
        // ++answer;                // Error: 'answer' is captured but read-only.
    };

    // Capture by (non-const) reference.
    auto fun3 = [&answer]() {
        ++answer;
    };

    // Capture everything by value.
    // 'answer' inside lambda is a copy of the original 'answer' value.
    auto fun4 = [=]() {
        assert(answer == 42);
        // ++answer;                // Error: 'answer' is captured but read-only.
    };

    // Capture everything by (non-const) reference.
    auto fun5 = [&]() {
        ++answer;
    };

    fun1();
    assert(answer == 42);
    fun2();
    assert(answer == 42);
    fun3();
    assert(answer == 43);
    fun4();
    assert(answer == 43);
    fun5();
    assert(answer == 44);
}


//////////////////////////////////////////////////
// In some cases, parts of lambda expressions
// can be omitted.
//
void test_lambda_simplifications() {
    // No return value type needed if single return statement.
    auto answer_provider = []() { return 42; };

    // No return value type needed if void function.
    auto name_greeter = [](const string& name) { cout << "Hi there, " << name << "!" << endl; };

    // No () needed if no parameters present.
    auto world_greeter = [] { cout << "Hello, world!" << endl; };
}


int main() {
    test_lambda_simple();
    test_lambda_stored();
    test_captures();
    test_lambda_simplifications();

    return 0;
}
