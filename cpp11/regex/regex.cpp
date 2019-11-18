#include <cstring>
#include <cassert>
#include <iostream>

#include <regex>

using namespace std;


//////////////////////////////////////////////////
// Basic regex usage.
//
void test_regex_essential() {
    const string text("the quick brown fox jumps over the lazy dog");

    // Simple search, anywhere in text.
    const regex re("quick");
    assert(regex_search(text, re));

    // No match.
    assert(not regex_search(text, regex("bamboozled")));

    // Complete match, from beginning to end of text.
    assert(regex_match(text, regex("the quick brown.*dog")));

    // Replace.
    string replaced = regex_replace(text, regex("dog"), "cat");
    assert(replaced == "the quick brown fox jumps over the lazy cat");

    // Search case insensitive.
    assert(not regex_search(text, regex("QUICK")));
    assert(regex_search(text, regex("QUICK", regex_constants::icase)));
}


//////////////////////////////////////////////////
// Subexpressions are sequences within parenthesis.
//
void test_regex_subexpression() {
    const string text("mailto:ralf.holly@approxion.com");

    const regex re{R"(mailto:(\S+)@(\S+))"};    // Define regex using raw string.
    smatch match_results;   // std::smatch = std::match_results<std::string::const_iterator>
    if (regex_search(text, match_results, re)) {
        assert(match_results.size() == 1 + 2);
        assert(match_results[0] == text);               // Whole match.
        assert(match_results[1] == "ralf.holly");       // First subexpression.
        assert(match_results[2] == "approxion.com");    // Second subexpression.
    }
}


//////////////////////////////////////////////////
// Find all matching instances of a search by
// restarting the search after the last match.
//
void test_regex_search_all1() {
    const string text("aaa 1 bbb 22 dddae 333 foo 4444 bar55555 zap");

    const regex number_re{R"(\d+)"};
    smatch match_results;
    auto subject = text;
    while (regex_search(subject, match_results, number_re)) {
        cout << match_results[0] << endl;
        subject = match_results.suffix().str();
    }
}


//////////////////////////////////////////////////
// Find all matching instances of a search.
// Search using 'sregex_iterator'.
//
void test_regex_search_all2() {
    const string text("aaa 1 bbb 22 dddae 333 foo 4444 bar55555 zap");

    const regex number_re{R"(\d+)"};
    for (sregex_iterator it = sregex_iterator(text.begin(), text.end(), number_re);
        it != sregex_iterator(); ++it) {
        smatch match_result = *it;
        cout << match_result[0] << endl;
    }
}


int main() {
    test_regex_essential();
    test_regex_subexpression();
    test_regex_search_all1();
    test_regex_search_all2();

    return 0;
}
