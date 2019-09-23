#include <iostream>
#include <cstring>
#include <cassert>
#include <thread>
#include <atomic>
#include <chrono>
#include <future>

using namespace std;

#define UNUSED(x) ((void)(x))



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
// Two threads communicate via promise/future.
// A promise object has a future object, the former
// is used by the producer (PROmise -> PROducer),
// the latter by the consumer.
void test_future_promise_simple() {
    // Allocate a promise.
    auto promise = std::promise<std::string>();
    // Get the promise's future.
    auto future = promise.get_future();

    // Producer sets the promise's value.
    auto producer = std::thread([&]
    {
        this_thread::sleep_for(chrono::seconds(1));
        promise.set_value("Hello World");
    });

    // Consumer gets the future's value.
    auto consumer = std::thread([&]
    {
        cout << "Waiting for future... " << endl;
        auto futval = future.get();
        cout << "... got it: " << futval << endl;
    });

    producer.join();
    consumer.join();
}


int main() {
    test_thread_simple_with_thread_function();
    test_thread_simple_with_lambda();
    test_future_promise_simple();

    return 0;
}
