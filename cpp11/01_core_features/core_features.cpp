#include <initializer_list>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

#define UNUSED(x) ((void)(x))


//////////////////////////////////////////////////
// Check C++ version via value of __cplusplus
// preprocessor define.
//
void test_cpp_version() {
    cout << "__cplusplus: " << __cplusplus << ", means ";
#if __cplusplus == 199711L
    cout << "C++98 or C++03";
#elif __cplusplus == 201103L
    cout << "C++11";
#elif __cplusplus == 201402L
    cout << "C++14";
#else
    cout << "Huh?";
#endif
    cout << endl;
}


//////////////////////////////////////////////////
// 'static_assert' is a keyword that checks
// assertions at compile-time.
//
void test_static_assert() {
    static_assert(1 + 2 == 3, "Basic arithmetic failed");
    // String argument (ie. error message) is mandatory until C++17.
    static_assert(sizeof(long) >= sizeof(int), "");
    int a = 42;
//  static_assert(a == 42, ""); // Error: non-const expression not allowed.
    UNUSED(a);
}


//////////////////////////////////////////////////
// 'nullptr' is a type-safe null pointer constant.
//
void fun(int) { cout << "fun(int i)" << endl; }
void fun(int*) { cout << "fun(int*)" << endl; }

void test_nullptr() {
    int* p1 = nullptr;  // Since C++11
    int* p2 = 0;        // Before C++11
    int* p3 = NULL;     // Before C++11

    fun(nullptr);       // Calls fun(int*)
    fun(0);             // Calls fun(int)

    UNUSED(p1); UNUSED(p2); UNUSED(p3);
}


//////////////////////////////////////////////////
// Automatic type deduction through 'auto'
// keyword.
void test_auto() {
    auto i = 42;     // i is of type 'int'.
    auto x = 1.234;  // x is of type 'double'
    auto y = i + x;  // y is of type 'double'

    UNUSED(i); UNUSED(x); UNUSED(y);

// NOTE:'auto' cannot be used with function parameters:
//    extern int some_fun(auto x); // Error: auto parameters not permitted.
//    Use template function instead:
//    template <typename T> int some_fun(T x);
}


//////////////////////////////////////////////////
// Range-based for-loops simplify iteration over
// sequences.
void test_range_based_for_loops() {
    vector<int> values {23, 42, 19};

    for (auto v : values) {         // 'v' is a local copy of item.
        cout << v << endl;
        v += 1;                     // Value change is lost.
    }
    for (auto& v : values) {        // 'v' is a reference to an item.
        cout << v << endl;
        v += 1;                     // Item value updated in vector.
    }
    for (const auto& v : values) {  // 'v' is a const reference to an item.
        cout << v << endl;
//      v += 1;                     // Error: 'v' is read-only.
    }
}


//////////////////////////////////////////////////
// Uniform initialization is a common way to
// initialize objects _and_ containers.
void test_uniform_initialization() {
    int a = 42;    // Traditional initialization.
    int b(42);     // dito.
    int c{42};     // Uniform initialization.
    int d{};       // Zero initialization.
    int e = int(); // Traditional zero intialization.
    UNUSED(a); UNUSED(b); UNUSED(c); UNUSED(d); UNUSED(e);
}


//////////////////////////////////////////////////
// Initializer lists provide a means to pass
// multiple values to constructors.
void test_initializer_lists() {
    // Initializer lists.
    vector<int> values1 {1, 2, 3};   // Would require 3 explicit push_back() calls in C++03.
    vector<int> values2 = {1, 2, 3}; // dito.
    vector<int> values3{};           // Empty vector.
    vector<int> values4 = {};        // dito.

    class MyClass {
    public:
        MyClass() { cout << "MyClass::MyClass()" << endl; }
        MyClass(const initializer_list<int>& i) { cout << "MyClass::MyClass{}" << endl; }
    };
    MyClass mc1 = {77,4,3,4};   // Calls MyClass{}.
    MyClass mc2;                // Calls MyClass().
    MyClass mc3{};              // dito.
    MyClass mc4 = {};           // dito.
    MyClass mc5();              // Just a function declaration.
    UNUSED(mc1); UNUSED(mc2); UNUSED(mc3); UNUSED(mc4);
}


//////////////////////////////////////////////////
// Scoped enumerations are safer than traditional
// enums and support different underlying types.
void test_scoped_enumerations() {
    enum class Colors { red, green, blue=42 };
    Colors my_color;
    // No unqualified access, no pollution of global namespace:
//  if (my_color == red) { ; }          // Error: unqualified access
    if (my_color == Colors::red) { ; }  // Fine.
//  cout << Colors::red << endl;        // Error: no implicit conversion to 'int'
    assert(42 == static_cast<int>(Colors::blue)); // Fine.

    // Enums of non-int underlying types:
    enum class Colors2 : unsigned char { red, green, blue=42 };
    assert(sizeof(Colors2) == 1);

    // Underlying type must be integral:
//  enum class Colors3 : float { red, green, blue=42.3 }; // Error.
}


int main() {
    test_cpp_version();
    test_static_assert();
    test_nullptr();
    test_auto();
    test_range_based_for_loops();
    test_uniform_initialization();
    test_initializer_lists();
    test_scoped_enumerations();

    return 0;
}
