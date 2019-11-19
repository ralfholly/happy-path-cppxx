
#include <cstring>
#include <cassert>
#include <iostream>

#include <memory>

using namespace std;


//////////////////////////////////////////////////
// 'unique_ptr' is a smart pointer that claims
// exclusive ownership over a pointer. It's meant
// to be a replacement for the (now deprecated)
// 'auto_ptr' class.
//
void test_unique_ptr_basic() {
    // Managed pointer.
    {
    unique_ptr<int> pi{new int(42)};
    assert(*pi == 42);
    } // pi dtor invokes delete on managed pointer.

    // Managed array.
    {
    unique_ptr<int[]> pia{new int[100]{11, 22, 33}};
    assert(pia[1] == 22);
    } // pia dtor invokes delete[] on managed pointer.
}


void test_unique_ptr_advanced() {
    unique_ptr<int> pi{new int(42)};
    assert(*pi == 42);

    // Get raw pointer, still managed by pi.
    int* p = pi.get();
    assert(*p == 42);

    // Take ownership of another pointer.
    pi.reset(new int(23));          // New ownership, previously owned pointer deleted.
    assert(*pi == 23);

    // Release pointer, end ownership.
    assert(pi);                     // There's a managed pointer.
    p = pi.release();               // Release ownership.
    assert(*p == 23);
    assert(pi.get() == nullptr);    // No ownership anymore.
    assert(!pi);                    // dito.

    // Unique pointers cannot be assigned, just moved.
    unique_ptr<float> pf1{new float{1.11f}};
//  unique_ptr<float> pf2{pf1};     // Error: no copy-construction allowed.
    unique_ptr<float> pf2{new float{2.22f}};
//  pf2 = pf1;                      // Error: no assignment allowed.
    pf2 = std::move(pf1);           // OK.
    assert(*pf2 == 1.11f);
    assert(!pf1);

    // A custom deleter function can be provided in
    // case a simple 'delete' is not enough.
    int counter = 0;
    auto deleter = [&counter](char* p) {
        delete p;
        ++counter;  // Observable (assertable) behavior.
    };
    {
    assert(counter == 0);
    unique_ptr<char, decltype(deleter)> pc{new char{'X'}, deleter};
    }
    // This proves that deleter was called.
    assert(counter == 1);
}


//////////////////////////////////////////////////
// 'shared_ptr' is a smart pointer that implements
// shared ownership over a wrapped pointer. Shared
// pointers maintain a "use count" variable that
// keeps track of the number of active users of
// the shared resource. When the use count reaches
// zero, the shared resource is automatically 
// destroyed.
//
void test_shared_ptr_basic() {
   // Managed pointer.
   shared_ptr<int> pi1{new int{42}};
   assert(*pi1 == 42);
   assert(pi1.use_count() == 1);
   {
       // Create another pointer to same shared resource.
       shared_ptr<int> pi2{pi1};
       assert(*pi2 == 42);
       assert(pi2.use_count() == 2);
       assert(pi1.use_count() == 2);
   } // pi2 dtor reduces use count.
   assert(pi1.use_count() == 1);

   // Managed array.
   shared_ptr<int[]> pia1{new int[100]{11, 22, 33}};
   assert(pia1[1] == 22);
   assert(pia1.use_count() == 1);
   {
       // Create another pointer to same shared resource.
       shared_ptr<int[]> pia2{pia1};
       assert(pia2[2] == 33);
       assert(pia2.use_count() == 2);
       assert(pia1.use_count() == 2);
   } // pia2 dtor reduces use count.
   assert(pia1.use_count() == 1);
}


void test_shared_ptr_advanced() {
    shared_ptr<int> pi{new int{42}};
    assert(*pi == 42);

    // Get raw pointer, still managed by pi.
    int* p = pi.get();
    assert(*p == 42);

    // Take ownership of another pointer.
    pi.reset(new int(23));          // New ownership, previously owned pointer deleted.
    assert(*pi == 23);

    // A custom deleter function can be provided in
    // case a simple 'delete' is not enough.
    int counter = 0;
    auto deleter = [&counter](char* p) {
        delete p;
        ++counter;  // Observable (assertable) behavior.
    };
    {
    assert(counter == 0);
    shared_ptr<char> pc{new char{'X'}, deleter};
    }
    // This proves that deleter was called.
    assert(counter == 1);
}


//////////////////////////////////////////////////
// 'weak_ptr' is a smart pointer that holds a
// non-owning ("weak") reference to an object that
// is managed by a 'shared_ptr'. It must be
// converted to a 'shared_ptr' in order to access
// the referenced object.
//
void test_weak_ptr() {
    shared_ptr<int> sp{new int{42}};
    assert(sp.use_count() == 1);

    // Create weak pointer that is bound to a shared pointer.
    weak_ptr<int> wp{sp};
    assert(sp.use_count() == 1);

    shared_ptr<int> my_sp = wp.lock();
    if (my_sp) {

    } else {
        cerr << "Shared " << endl;
    }
}


int main() {
    test_unique_ptr_basic();
    test_unique_ptr_advanced();
    test_shared_ptr_basic();
    test_shared_ptr_advanced();

    return 0;
}
