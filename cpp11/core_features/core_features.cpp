#include <initializer_list>
#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

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
// 'cstdint' library header provides fixed-width
// integer type definitions ala C99.
//
#include <cstdint>
void test_cstdint() {
    uint8_t byte1 = 20;
    uint_least8_t byte2 = 11;
    int_fast16_t f16 = 2000;
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

}


//////////////////////////////////////////////////
// Automatic type deduction through 'auto'
// keyword.
void test_auto() {
    auto i = 42;     // i is of type 'int'.
    auto x = 1.234;  // x is of type 'double'
    auto y = i + x;  // y is of type 'double'

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
    for (auto s : { "one", "two", "three" }) {    // Iterate over std::initializer_list.
        cout << s << endl;
    }
}


//////////////////////////////////////////////////
// Uniform initialization is a common way to
// initialize objects _and_ containers.
// Uniform initialization is now the preferred way
// to initialize.
void test_uniform_initialization() {
    int a = 42;    // Traditional initialization.
    int b(42);     // dito.
    int c{42};     // Uniform initialization.
    int d{};       // Zero initialization.
    int e = int(); // Traditional zero intialization.
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
        MyClass(const initializer_list<int>& list) {
            cout << "MyClass::MyClass(const initializer_list<int>&) {";
            for (const auto& e: list) {
                cout << e << ",";
            }
            cout << "} // list.size() is " << list.size() << endl;
        }
    };
    MyClass mc1 = {77,4,3,4};   // Calls MyClass{}.
    MyClass mc2 {77,4,3,4};     // dito.
    MyClass mc3;                // Calls MyClass().
    MyClass mc4{};              // dito.
    MyClass mc5 = {};           // dito.
    MyClass mc6();              // Just a function declaration.
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


//////////////////////////////////////////////////
// Raw string literals let you define string
// literals without the need to escape special
// characters like backslash and quotes.
void test_raw_string_literals() {
    // No delimiter.
    assert(strcmp(R"(actual\str"i"ng)", "actual\\str\"i\"ng") == 0);
    // Delimter is '#'.
    assert(strcmp(R"#(actual\str"i"ng)#", "actual\\str\"i\"ng") == 0);
    // Delimter is 'foo'.
    assert(strcmp(R"foo(actual\str"i"ng)foo", "actual\\str\"i\"ng") == 0);
    // Raw strings can span multiple lines.
    assert(strcmp(R"foo(actual
    str"i"ng
)foo", "actual\n    str\"i\"ng\n") == 0);
}


//////////////////////////////////////////////////
// Using 'constexpr' on a variable makes it
// implicitly constant.
//
void test_constexpr_on_variable() {
    constexpr int answer = 42;
    static_assert(answer == 42, "impossible!");
    int my_array[answer];

    const constexpr double PI = 3.14; // Redundant 'const' declaration.
}


//////////////////////////////////////////////////
// In C++11, 'constexpr' functions are quite restriced:
//  - no local variables
//  - only a single 'return' statement
//  - no loops (but recursion allowed)
// 'constexpr' functions must be able to return a 'constexpr' value if provided with only 'constexpr' arguments.
//
constexpr int add(int a, int b) {
    return a + b;
}

void test_constexpr_function() {
    constexpr int val1 = 1;
    constexpr int val2 = 2;
    static_assert(add(val1, val2) == 3, "impossible!");
    static_assert(add(100, 99) == 199, "impossible!");
    int array[add(1, 2)];

    int val3 = 42;
    int val4 = 10;
    // static_assert(add(val3, val4) == 52, "impossible!"); Error: 'add' doesn't yield a 'constexpr'.
    int val5 = add(val3, val4); // OK, 'add' may be called with non 'constexpr' arguments.
}


//////////////////////////////////////////////////
// 'decltype' determines the type of an expression
// at compile-time. It can be thought of as a
// standardized version of the proprietary 'typeof'
// operator provided by many compilers.
// 'auto' is often a better alternative.
// 'decltype' is sometimes useful in template contexts.
void test_decltype() {
    vector<double> my_vals { 1.1, 2.2, 3.3 };
    decltype(my_vals) your_vals;
    // auto a = decltype(my_vals);      // Error: can't store returned type.
    // static_assert(decltype(my_vals) == decltype(your_vals));
                                        // Error: can't compare returned types.
}


//////////////////////////////////////////////////
// New function syntax allows declaring the
// function return type after the parameter list.
//
auto calc_sum(int a, int b) -> int {
    return a + b;
}

void test_new_function_syntax() {
    assert(calc_sum(1, 2) == 3);
}


//////////////////////////////////////////////////
// New function syntax allows declaring the return
// value type based on argument types. This is
// might come in handy in template contexts.
//
template <class T, class U>
auto decltype_return_value(T const& t, U const& u) -> decltype(t + u) {
      return t + u;
}

void test_decltype_return_value() {
    assert(strcmp(decltype_return_value("abc", 1), "bc") == 0);
}


int main() {
    test_cpp_version();
    test_cstdint();
    test_static_assert();
    test_nullptr();
    test_auto();
    test_range_based_for_loops();
    test_uniform_initialization();
    test_initializer_lists();
    test_scoped_enumerations();
    test_raw_string_literals();
    test_constexpr_on_variable();
    test_constexpr_function();
    test_decltype();
    test_new_function_syntax();
    test_decltype_return_value();

    return 0;
}
