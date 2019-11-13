#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

#pragma GCC diagnostic ignored "-Wunused-variable"

//////////////////////////////////////////////////
// The basic idea behind 'move semantics' is
// optimization by reusing expensive-to-create
// member data that already exists in soon-to-
// be-deleted (temporary) objects.
//

void test_without_move_semantics() {
    // Holds an array of n integers.
    class Holder {
    public:
        Holder(size_t n) : n_(n), values_(new int[n]) { ; }
        Holder(const Holder& rhs) {
            cout << "Holder(const Holder&) called" << endl;
            n_ = rhs.n_;
            values_ = new int[n_];
            std::copy(rhs.values_, rhs.values_ + rhs.n_, values_);
        }
        Holder& operator=(const Holder& rhs) {
            cout << "operator=(const Holder&) called" << endl;
            if (this == &rhs) return *this;
            delete[] values_;
            n_ = rhs.n_;
            values_ = new int[n_];
            std::copy(rhs.values_, rhs.values_ + rhs.n_, values_);
            return *this;
        }
        ~Holder() { delete[] values_; }
    private:
        size_t n_;
        int* values_;
    };

    // Since true local functions are not supported by C++, use a lambda.
    auto create_big_holder = [] { return Holder(1000); };

    Holder holder(42);
    holder = create_big_holder(); // Values from returned temporary are copied to 'holder' object.
                                  // These values from the temporary are lost and can't be reused
                                  // without the use of move semantics.
}


void test_with_move_semantics() {
    // Holds an array of n integers.
    class Holder {
    public:
        Holder(size_t n) : n_(n), values_(new int[n]) { ; }
        Holder(const Holder& rhs) {
            cout << "Holder(const Holder&) called" << endl;
            n_ = rhs.n_;
            values_ = new int[n_];
            std::copy(rhs.values_, rhs.values_ + rhs.n_, values_);
        }
        // The 'move' constructor. (Not used in this example, but shown anyway).
        Holder(Holder&& rhs) {
            cout << "Holder(Holder&&) called" << endl;
            // Reuse ('steal') values from rhs without deeply copying them.
            n_ = rhs.n_;
            values_ = rhs.values_;
            // Leave rhs in a state that is valid and causes no harm
            // when its later destructed (like deleting the reused
            // values).
            // This is possible since rvalue references are not const
            // and thus allow modification of the bound rvalue.
            rhs.n_ = 0;
            rhs.values_ = nullptr;
        }
        Holder& operator=(const Holder& rhs) {
            cout << "operator=(const Holder&) called" << endl;
            if (this == &rhs) return *this;
            delete[] values_;
            n_ = rhs.n_;
            values_ = new int[n_];
            std::copy(rhs.values_, rhs.values_ + rhs.n_, values_);
            return *this;
        }
        // The 'move' assignment operator.
        Holder& operator=(Holder&& rhs) {
            cout << "operator=(Holder&&) called" << endl;
            if (this == &rhs) return *this;
            delete[] values_;
            // Reuse ('steal') values from rhs without deeply copying them.
            n_ = rhs.n_;
            values_ = rhs.values_;
            // Leave rhs in a state that is valid and causes no harm
            // when its later destructed (like deleting the reused
            // values).
            // This is possible since rvalue references are not const
            // and thus allow modification of the bound rvalue.
            rhs.n_ = 0;
            rhs.values_ = nullptr;
            return *this;
        }
        ~Holder() { delete[] values_; }
    private:
        size_t n_;
        int* values_;
    };

    // Since true local functions are not supported, use a lambda.
    auto create_big_holder = [] { return Holder(1000); };

    Holder holder(42);
    holder = create_big_holder(); // Thanks to move semantics, op=(Holder&&) is called instead of op=(const Holder&).
                                  // Thus, values from returned temporary are reused without expensive memory allocation/copying.
}


int main() {
    test_without_move_semantics();
    test_with_move_semantics();

    return 0;
}
