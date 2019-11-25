The Happy Path To Modern C++
============================

Modern C++ can be really hard to learn! This project aims at teaching just the *beauty* of modern C++ -- not through documentation but through simple code snippets; corner cases are intentionally omitted.

Prerequisites
-------------

In order to benefit from this project, it's assumed that readers are already familiar with the C++98 language. This project aims at showing the "beautiful delta" between C++98 and modern C++.

C++11
-----

[cpp11/core_features/](cpp11/core_features/)
Cross-cutting language aspects that are either considered to be part of the core language or are so small that they don't warrant their own chapter, e. g.:
- Static assertions
- `auto` types
- Range-based `for` loops
- `initializer_list`s
- `constexpr` expressions
- Scoped `enum`s
- User-defined literals

[cpp11/lambda_expressions/](cpp11/lambda_expressions/)
Demonstrates how to use lambda expressions.

[cpp11/class_features/](cpp11/class_features/)
Features that pertain mostly to classes, e. g:
- `final`, `override`, `default`, `delete` specifiers
- Constructor delegation
- Initialization of non-static members

[cpp11/rvalues_lvalues_ref/](cpp11/rvalues_lvalues_ref/)
A primer on lvalues, rvalues, lvalue references and rvalue references.

[cpp11/move_semantics/](cpp11/move_semantics/)
Shows the motivation behind move semantics and how to implement it in your class.

[cpp11/threads/](cpp11/threads/)
Demonstrates the various aspecs of multi-threading, including:
- Launching threads with `std::thread`
- `std::mutex` and `std::condition_variable`
- `std::promise` and `std::future`
- Launching and synchronizing threads with `std::async`

[cpp11/smart_pointers/](cpp11/smart_pointers/)
Introduces smart pointers, e. g.:
- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`

[cpp11/containers/](cpp11/smart_pointers/)
Gives an overview of the following containers:
- `std::array`
- `std::forward_list`
- `std::unordered_set` and `std::unordered_multiset`
- `std::unordered_map` and `std::unordered_multimap`

[cpp11/containers/](cpp11/smart_pointers/)
Introduces smart pointers, e. g.:
- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`

[cpp11/variadic_templates/](cpp11/variadic_templates/)
Shows how to use variadic (arbitrary-number-of-argument) templates and what "perfect forwarding" is about.

[cpp11/odds_and_ends/](cpp11/odds_and_ends/)
Miscellaneous topics, like:
- Algorithms
- `std::tuple`
- Alignment

C++14
-----

[cpp14/core_features/](cpp14/core_features/)
    Cross-cutting language aspects that are either considered to be part of the core language or are so small that they don't warrant their own chapter, e. g.:

Upcoming topics
---------------

Lot's of C++14 stuff :-)
