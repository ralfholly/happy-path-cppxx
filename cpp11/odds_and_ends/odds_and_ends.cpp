
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>

#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;


//////////////////////////////////////////////////
// Various algorithms.
//
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
// `tuple` class.
//
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

    int i1, i2, i3;
    tie(i1, i2, i3) = vector<int>{3, 4, 5};
}


int main() {
    test_algorithms();
    test_tuple();

    return 0;
}
