#include <cassert>
#include <iostream>

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
    cout << "?";
#endif
    cout << endl;
}


//////////////////////////////////////////////////
// Better readability for numeric constants
// through (digit) separators and a possibility
// to define binary constants.
// Since C++14.
//
void test_numeric_literals() {
    assert(42'000'000 == 42000000); // Since C++14.
    assert(0b100 == 4);             // Since C++14.
    assert(0b1'0000'0000 == 256);   // Since C++14.
}


int main()
{
    test_cpp_version();
    test_numeric_literals();

    return 0;
}
