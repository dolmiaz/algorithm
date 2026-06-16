#include "../library/string.hpp"

#include <cassert>

int main() {
    assert(is_palindrome(string("")));
    assert(is_palindrome(string("a")));
    assert(is_palindrome(string("racecar")));
    assert(is_palindrome(string("abba")));
    assert(!is_palindrome(string("abc")));
    assert(!is_palindrome(string("abca")));

    assert((is_palindrome(V<int>{1, 2, 3, 2, 1})));
    assert((is_palindrome(V<int>{1, 2, 2, 1})));
    assert((!is_palindrome(V<int>{1, 2, 3})));

    return 0;
}
