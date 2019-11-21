#include <cstring>
#include <cassert>
#include <iostream>

#include <array>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

using namespace std;

//////////////////////////////////////////////////
// 'array' is a fixed-size array-like container.
//
void test_array() {
    array<int, 10> values{11, 22, 33};

    assert(values.size() == 10);
    assert(values.max_size() == 10);

    assert(values[2] == 33);

    assert(values.front() == 11);
    assert(values.back() == 0);
    values[values.size() - 1] = 42;
    assert(values.back() == 42);

//  values[values.size()] = 666;    // Run-time error: out-of-bounds access.
}


//////////////////////////////////////////////////
// 'forward_list' is singly-linked list and thus
// a bit more memory-efficient that a regular
// 'list'.
void test_forward_list() {
    forward_list<int> values{9, 8, 7};

    int first = values.front();
    assert(first == 9);
    values.pop_front();

    auto it = values.begin();
    assert(*it++ == 8);
    assert(*it == 7);
    values.insert_after(it, first);

    const forward_list<int> values_expected{8, 7, 9};
    assert(values == values_expected);
}


//////////////////////////////////////////////////
// 'unordered_set' is a hash-table based set
// implementation.
//
void test_unorderd_set() {
    unordered_set<int> values{22, 33, 44};

    assert(values.size() == 3);
    assert(values.find(22) != values.end());

    values.insert(11);
    assert(values.find(11) != values.end());
    values.insert(11);
    values.insert(11);
    values.insert(11);
    // This is not a multiset.
    assert(values.count(11) == 1);

    // Element doesn't exist.
    assert(values.find(77) == values.end());
}


//////////////////////////////////////////////////
// 'unordered_multiset' is a hash-table based set
// implementation that allows duplicate keys.
//
void test_unorderd_multiset() {
    unordered_multiset<int> values{22, 33, 44};

    assert(values.size() == 3);
    assert(values.find(22) != values.end());

    values.insert(11);
    assert(values.find(11) != values.end());
    values.insert(11);
    values.insert(11);
    values.insert(11);
    assert(values.count(11) == 4);

    // Element doesn't exist.
    assert(values.find(77) == values.end());
}


//////////////////////////////////////////////////
// 'unordered_map' is a hash-table based map
// implementation.
//
void test_unorderd_map() {
    unordered_map<string, int> person_ages{{"John", 42}, {"Jill", 28}};

    assert(person_ages.size() == 2);
    assert(person_ages["John"] == 42);

    person_ages["Mary"] = 66;
    assert(person_ages.size() == 3);

    // Non-existant element.
    assert(person_ages.find("Herbert") == person_ages.end());

    // Add another John.
    person_ages["John"] = 77;
    assert(person_ages["John"] == 77);
    // This is not a multimap.
    assert(person_ages.count("John") == 1);
}


//////////////////////////////////////////////////
// 'unordered_multimap' is a hash-table based map
// implementation that allows duplicate keys.
//
void test_unorderd_multimap() {
    unordered_multimap<string, int> person_ages{{"John", 42}, {"Jill", 28}};

    assert(person_ages.size() == 2);
//  assert(person_ages["John"] == 42);      // Error: no operator[] support.
    assert(person_ages.find("John")->second == 42);

//  person_ages["Mary"] = 66;               // Error: no operator[] support.
    person_ages.insert({"Mary", 66});
    assert(person_ages.size() == 3);

    // Non-existant element.
    assert(person_ages.find("Herbert") == person_ages.end());

    // Add another John.
    person_ages.insert({"John", 77});
    assert(person_ages.count("John") == 2);

    // Retrieve multiple values.
    auto equ = person_ages.equal_range("John");
    unsigned john_count = 0;
    for (auto it = equ.first; it != equ.second; ++it) {
        assert(it->first == "John");
        ++john_count;
    }
    assert(person_ages.count("John") == john_count);
}


int main() {
    test_array();
    test_forward_list();
    test_unorderd_set();
    test_unorderd_multiset();
    test_unorderd_map();
    test_unorderd_multimap();

    return 0;
}
