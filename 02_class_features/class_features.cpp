#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

#define UNUSED(x) ((void)(x))


//////////////////////////////////////////////////
// Special member function declarations 'default'
// and 'delete'.
// Before C++11, member functions where declared
// 'private' to make them inaccessible.
//
void test_special_mem_fun_declarations() {
    class Apple {
    public:
        Apple(int size) { ; }   // User-provided ctor.
        Apple() = default;      // Generate default ctor even though
                                // user-proved ctor exist.
        Apple(const Apple&) = delete; // Don't allow copy-construction.
    };
    Apple apple1(42);
    Apple apple2();
//  Apple apple3(apple1);       // Error: copy ctor deleted.
}


//////////////////////////////////////////////////
// 'override' specifier prevents from accidentally
// overriding wrong methods.
//
void test_override() {
    class Base {
        virtual void increase() { ; }   // Virtual member function.
        void apply() { ; }              // Non-virtual member function.
    };

    class Derived : public Base {
        virtual void increase() override { ; } // OK, overriding base class function.
//      virtual void apply() override { ; }    // Error: does not override.
    };
}


//////////////////////////////////////////////////
// 'final' specifier prevents further overriding.
//
void test_final() {
    class Base {
        virtual void increase() { ; }   // Virtual member function.
    };

    class Derived : public Base {
        virtual void increase() override final { ; } // Override base class function and
                                                     // prevent further overriding.
    };

    class MoreDerived : public Derived {
//      virtual void increase() override { ; } // Error: member function is 'final'.
    };

    class FinalBase final {     // Class is 'final'
    };

//  class DerivedFinalBase : public FinalBase {     // Error: cannot derive from
//                                                  // final class.
//  };
}


//////////////////////////////////////////////////
// Initialization of non-static class members
// allows for providing an initial value to a
// class member that can be overwritten in the
// constructor.
//
void test_non_static_member_init() {
    class Apple {
    public:
        int m_size = 42;        // Non-static initializer.
        int m_weight = 100;     // dito.
        Apple() : m_weight(99) { ; }    // Overwrite inital value.
    };

    Apple apple;
    assert(apple.m_size == 42);
    assert(apple.m_weight == 99);
}


//////////////////////////////////////////////////
// Constructor delegation allows for calling an
// existing constructor from another constructor.
//
void test_constructor_delegation() {
    class Apple {
    public:
        Apple(int i) { cout << "i: " << i << endl; }
        Apple(const char* name) : 
            Apple(strlen(name)){        // Invoke Apple(int) first,
                cout << name << endl;   // then execute body.
        }
    };
    Apple apple("Hello");
}


int main()
{
    test_special_mem_fun_declarations();
    test_override();
    test_final();
    test_non_static_member_init();
    test_constructor_delegation();

    return 0;
}
