
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;


//////////////////////////////////////////////////
// Various algorithms.
//
#include <algorithm>
#include <numeric>
void test_algorithms() {
    const vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19};

    // 'all_of' returns true if the predicate is true for all elements.
    // All numbers positive?
    assert(all_of(primes.begin(), primes.end(), [primes](int v) { return v > 0; }));

    // 'any_of' returns true if at least one element meets the predicate.
    // Any numbers even?
    assert(any_of(primes.begin(), primes.end(), [primes](int v) { return (v % 2) == 0 ; }));

    // 'none_of' returns true if no element meets the predicate.
    // No numbers above 1000?
    assert(none_of(primes.begin(), primes.end(), [primes](int v) { return v > 1000; }));

    // 'copy_if' copies elements for which a predicate is true.
    vector<int> even_primes;
    copy_if(primes.begin(), primes.end(), back_inserter(even_primes), [primes](int v) { return (v % 2) == 0; });
    assert(even_primes.size() == 1 && even_primes.front() == 2);

    // 'copy_n' copies n elements.
    vector<int> target;
    copy_n(primes.begin(), 2, back_inserter(target));
    assert(target.size() == 2);

    // 'is_sorted' checks if a sequence is sorted.
    assert(is_sorted(primes.begin(), primes.end()));

    // 'iota' assigns incremented numbers to a sequence
    vector<int> hundred_plus(5);
    iota(hundred_plus.begin(), hundred_plus.end(), 100);
    assert(hundred_plus[0] == 100);
    assert(hundred_plus[4] == 104);
}


//////////////////////////////////////////////////
// 'tuple' class and 'tie' utility.
//
#include <tuple>
void test_tuple() {
    auto my_tuple = make_tuple(1, "PI", 3.14f);

    // Access via 'std::get'.
    assert(get<0>(my_tuple) == 1);
    assert(get<1>(my_tuple) == string{"PI"});
    assert(get<2>(my_tuple) == 3.14f);

    // Access via 'std::tie'.
    int pos;
    string name;
    float value;
    tie(pos, name, value) = my_tuple;
    assert(pos == 1);
    assert(name == string{"PI"});
    assert(value == 3.14f);

    // Use 'tie' to extract from a 'pair'.
    pair<int, string> my_pair{42, "the answer"};
    int number;
    string description;
    tie(number, description) = my_pair;
}


//////////////////////////////////////////////////
// Memory alignment utilities.
//
#include <memory>
void test_alignment() {

    // 'alignof' returns the alignment in bytes of a given type.
    assert(alignof(char) == 1);
    assert(alignof(uint32_t) == 4);
    assert(alignof(double) == 8);

    // 'alignas' alignes an object on an n-byte boundary.
    struct Foo {
        double d;
        string s;
    };
    alignas(128) Foo foo;
    assert((reinterpret_cast<size_t>(&foo) % 128) == 0);

    // 'aligned_storage' builds a type that meets given alignment criteria.
    // .. 512 bytes, aligned on a 128-byte boundary.
    aligned_storage<512, 128>::type my_object;
    assert((reinterpret_cast<size_t>(&my_object) % 128) == 0);
    assert(sizeof(my_object) == 512);

    // 'align' aligns pointers to memory at run-time.
    uint8_t buffer[1024];
    void* memory = &buffer[0];
    size_t size = sizeof(buffer);
    cout << "Original address: " << reinterpret_cast<size_t>(memory) << ", original size: " << sizeof(buffer) << endl;
    // 'memory' will be aligned on a 128-byte boundary, for 3 'double' values
    // and 'size' will be set to the new size of the aligned memory.
    align(128, 3 * sizeof(double), memory, size);
    cout << "Aligned address: " << reinterpret_cast<size_t>(memory) << ", aligned size: " << size << endl;
    assert((sizeof(buffer) - size) <= 128);
    double* pd = static_cast<double*>(memory);
    *pd++ = 1.1;
    *pd++ = 2.2;
    *pd++ = 3.3;
}


//////////////////////////////////////////////////
// Type traits allow checking of certain properties
// on types at compile-time.
//
#include <type_traits>
void test_type_traits() {
    class Base { };
    class Derived : public Base { };

    static_assert(is_integral<int>::value, "");
    static_assert(not is_integral<string>::value, "");
    static_assert(is_class<string>::value, "");
    static_assert(not is_class<char>::value, "");
    static_assert(is_base_of<Base, Derived>::value, "");
    static_assert(not is_base_of<Derived, Base>::value, "");
    static_assert(not has_virtual_destructor<string>::value, "");
    static_assert(is_pod<Derived>::value, "");

    typedef int MY_INT;
    static_assert(is_same<int, MY_INT>::value, "");
    static_assert(is_signed<int>::value, "");
    static_assert(not is_signed<uint16_t>::value, "");

    int my_array[10][20];
    static_assert(is_array<decltype(my_array)>::value, "");
    static_assert(rank<decltype(my_array)>::value == 2, "");

    // Plus a lot more, see type_traits header file.
}


int main() {
    test_algorithms();
    test_tuple();
    test_alignment();
    test_type_traits();

    return 0;
}
