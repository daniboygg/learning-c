#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string.c"

void test_simple() {
    String s = string_new("This is my string");
    assert(s.len == 17);
    assert(s.capacity == 17);
    assert(strcmp(s.data, "This is my string") == 0);
    assert_string_equal_cstring(s, "This is my string");
}

void test_equal() {
    String s1 = string_new("This is my string");
    String s2 = string_new("This is my string");
    assert_string_equal(s1, s2);
}

void test_concat(Allocator *a) {
    String s1 = string_new("This is ");
    String s2 = string_new("my string.");
    String s3 = string_concat(a, s1, s2);
    assert_string_equal_cstring(s3, "This is my string.");
}

int main(int argc, char *argv[]) {
    Allocator *a = allocator_new(1024);

    test_simple();
    test_equal();
    test_concat(a);

    allocator_free(a);
}
