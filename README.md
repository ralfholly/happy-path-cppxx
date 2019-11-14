The Happy Path To Modern C++
============================

Modern C++ can be really hard to learn! This project aims at teaching just the *beauty* of modern C++ -- not through documentation but through simple code snippets; corner cases are intentionally omitted.

C++11
-----

[cpp11/core_features/](cpp11/core_features/)
Cross-cutting language aspects that are either considered to be part of the core language or are so small that they don't warrant their own chapter, e. g.:
- `static_assert`
- `auto` types
- range-based `for` loops
- `initializer_list`s
- `constexpr` expressions

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

[cpp11/variadic_templates/](cpp11/variadic_templates/)
Shows how to use variadic (arbitrary-number-of-argument) templates and what "perfect forwarding" is about.

C++14
-----

[cpp14/core_features/](cpp14/core_features/)
    Cross-cutting language aspects that are either considered to be part of the core language or are so small that they don't warrant their own chapter, e. g.:


Upcoming topics
---------------

- Core features
  - `decltype`
  - Foo<Bar<int>> syntax now legal
- User defined literals
- New containers
- Regexps
[cpp11/core_features/](cpp11/core_features/)
