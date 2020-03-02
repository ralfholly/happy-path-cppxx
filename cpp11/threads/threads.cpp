
#include <cstring>
#include <cassert>
#include <thread>
#include <atomic>
#include <chrono>
#include <future>
#include <iostream>

using namespace std;


static void thread_func(int i) {
    for (auto i : { 1, 2, 3}) {
        cout << "Thread #" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}


//////////////////////////////////////////////////
// Create two simple threads that execute a thread
// function and wait for them to finish.
void test_thread_simple_with_thread_function() {
    thread thread1(&thread_func, 1);
    thread thread2(&thread_func, 2);

    thread1.join();
    thread2.join();
}


//////////////////////////////////////////////////
// Create two simple threads that execute a thread
// function as a lambda.
void test_thread_simple_with_lambda() {
    thread thread1([]() {
        cout << "Now with lambda 1!" << endl;
        thread_func(1);
    });
    thread thread2([]() {
        cout << "Now with lambda 2!" << endl;
        thread_func(2);
    });

    thread1.join();
    thread2.join();
}


//////////////////////////////////////////////////
// Mutexes are the basic thread synchronization
// primitives. 'lock_guard' and 'unique_lock' are
// convenience wrappers for 'mutex'.
//
void test_locks() {
    mutex m;

    // Explicit locking (rarely used).
    m.lock();
    // ... critical section ...
    m.unlock();

    // Try-locking.
    if (m.try_lock()) {
        // ... critical section ...
        m.unlock();
    } else {
        // Lock was not available.
    }

    // 'lock_guard' automatically calls 'mutex::lock' ('mutex::unlock') at the
    // beginning (end) of a block.
    {
        lock_guard<mutex> my_guard(m);      // m.lock()
        // ... critical section ...
    } // m.unlock()

    // 'unique_lock' is similar to 'lock_guard' but has a wider interface which,
    // for instance, allows explicit (and multiple) locking/unlocking of the
    // wrapped mutex.
    {
        unique_lock<mutex> my_unique_lock(m);
        // ... critical section ...
        my_unique_lock.unlock();        // Explicit unlocking.
        // ...
        my_unique_lock.lock();          // Explicit locking.
        // ... critical section ...
    } // m.unlock()
}


//////////////////////////////////////////////////
// Condition variables allow (multiple) threads to
// wait for an event.
void test_condition_variable() {
    // Use of condition variables requires a mutex.
    mutex mtx;
    condition_variable cond_var;
    // The following variable (combined with the while loop in the consumer)
    // guards against spurious wakeups. Spurious wakeups: It's possible that the
    // wait operation of a condition variable is aborted even though the
    // condition variable hasn't been explicitly signalled/notified.
    bool notified = false;

    // Producer notifies/signals condition variable.
    auto producer = std::thread([&]
    {
        this_thread::sleep_for(chrono::milliseconds(200));
        // ... wait a little ...
        unique_lock<mutex> lock(mtx);
        notified = true;
        cond_var.notify_all();
    });

    // Consumer waits on condition variable being signalled.
    auto consumer = std::thread([&]
    {
        // Lock *must* be acquired before calling wait on condition variable.
        unique_lock<mutex> lock(mtx);
        cout << "Waiting to be notified... " << flush;
        // While loop guards against spurious wakeups.
        while (!notified) {
            // Upon calling wait, lock is automatically released.
            cond_var.wait(lock);
            // Upon wakeup, lock is automatically re-acquired.
        }

        // Alternative implementation with implicit while loop:
        // cond_var.wait(lock, [&]() -> bool { return notified; });
        cout << "notified:" << boolalpha << notified << endl;
    });

    producer.join();
    consumer.join();
}


//////////////////////////////////////////////////
// Two threads communicate via promise/future.
// A promise object has a future object, the former
// is used by the producer (PROmise -> PROducer),
// the latter by the consumer.
void test_future_promise_simple() {
    // Allocate a promise.
    auto promise = std::promise<std::string>();

    // Producer sets the promise's value.
    auto producer = std::thread([&]()
    {
        this_thread::sleep_for(chrono::milliseconds(200));
        promise.set_value("Howdy!");
    });

    // Consumer gets the future's value.
    auto consumer = std::thread([&]()
    {
        // Get the promise's future.
        auto future = promise.get_future();
        cout << "Waiting for future... " << flush;
        auto futval = future.get();
        cout << "got it: " << futval << endl;
    });

    producer.join();
    consumer.join();
}


//////////////////////////////////////////////////
// Two threads communicate via promise/future.
// The consumer uses 'future::wait_for'
// instead of 'future::get' to avoid blocking.
void test_future_promise_extended() {
    // Allocate a promise.
    auto promise = std::promise<std::string>();

    // Producer sets the promise's value.
    auto producer = std::thread([&]()
    {
        this_thread::sleep_for(chrono::milliseconds(200));
        promise.set_value("Greetings!");
    });

    // Consumer gets the future's value.
    auto consumer = std::thread([&]()
    {
        // Get the promise's future.
        auto future = promise.get_future();
        for (;;) {
            cout << "Waiting for future... " << flush;
            auto status = future.wait_for(chrono::milliseconds(20));
            if (status == future_status::timeout) {
                cout << "no result yet!" << endl;
            } else if (status == future_status::ready) {
                // Value not consumed yet.
                assert(future.valid());
                cout << "got it: " << future.get() << endl;
                // Value consumed.
                assert(!future.valid());
                break;
            }
        }
    });

    producer.join();
    consumer.join();
}


//////////////////////////////////////////////////
// 'std::async' launches a function (asynchronously
// or synchronously, depending on the launch
// policy) and returns a future to that
// function's return value.
void test_async() {
    auto add_two = [](int a, int b) -> int {
        cout << "Computing " << a << " + " << b << "... " << flush;
        this_thread::sleep_for(chrono::milliseconds(300));
        // ... wait a little ...
        return a + b;   // Like an implicit promise.set_value(a + b).
    };
    auto future = async(std::launch::async, add_two, 1, 2);
    int futval = future.get();
    cout << futval << endl;
}


//////////////////////////////////////////////////
// 'std::atomic' is a wrapper that adds support
// for synchronized access to a type.
//
void test_atomics() {
    // Atomic primitive types are most likely implemented with lock-free
    // techniques for maximum performance.
    atomic<int> my_int {42};
    ++my_int;   // Thread-safe increment.
    --my_int;   // Thread-safe decrement.
    my_int.store(23);               // Explicit write access via wrapper interface.
    assert(my_int.load() == 23);    // Explicit read access via wrapper interface.
    my_int = 11;                    // Write access via overloaded operator.
    assert(my_int == 11);           // Read access via overloaded operator.

    // Atomic wrappers for arbitrary (complex) types will probably utilize mutexes.
    class Foo {
    // ...
    };
    atomic<Foo> my_foo;
    Foo your_foo;
    my_foo = your_foo;
}


int main() {
    test_thread_simple_with_thread_function();
    test_thread_simple_with_lambda();
    test_locks();
    test_condition_variable();
    test_future_promise_simple();
    test_future_promise_extended();
    test_async();
    test_atomics();

    return 0;
}
