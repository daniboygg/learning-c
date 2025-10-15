#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ********************* ALLOCATOR *************************
typedef struct Allocator {
    size_t capacity;
    size_t len;
    char *data;
} Allocator;

Allocator *allocator_new(size_t capacity) {
    Allocator *a = malloc(sizeof(Allocator));
    assert(a != NULL);
    char *bytes = malloc(capacity * sizeof(char));
    assert(bytes != NULL);

    a->capacity = capacity;
    a->len = 0;
    a->data = bytes;
    return a;
}

char *allocator_alloc(Allocator *a, size_t size) {
    if (a->len + size > a->capacity) {
        return NULL;
    }
    char *current_length = a->data + a->len;
    a->len += size;
    return current_length;
}

void allocator_free(Allocator *a) {
    free(a->data);
    free(a);
}

// ********************* String *************************

typedef struct String {
    size_t capacity;
    size_t len;
    char *data; /* always contains '\0' but not counting towards capacity/length */
} String;

static size_t _char_size(const char *chars);

String string_new(char *chars) {
    size_t size = _char_size(chars);
    String s = {.capacity = size, .len = size, .data = chars};
    return s;
}

String string_concat(Allocator *alloc, String s1, String s2) {
    const int new_size = s1.len + s2.len;

    char *chars = allocator_alloc(alloc, new_size * sizeof(char) + 1); /* space for '\0' */
    assert(chars != NULL);
    // char *chars = malloc(new_size * sizeof(char) + 1); /* space for '\0' */

    String s = {.capacity = new_size, .len = 0, .data = chars};

    for (int i = 0; i < s1.len; ++i) {
        s.data[s.len++] = s1.data[i];
    }
    for (int i = 0; i < s2.len; ++i) {
        s.data[s.len++] = s2.data[i];
    }
    s.data[s.len] = '\0';
    return s;
}

void assert_string_equal(String s1, String s2) {
    assert(s1.len == s2.len);
    assert(s1.capacity == s2.capacity);
    assert(strcmp(s1.data, s2.data) == 0);
}

void assert_string_equal_cstring(String s1, const char *chars) {
    assert(s1.len == _char_size(chars));
    assert(s1.capacity == _char_size(chars));
    assert(strcmp(s1.data, chars) == 0);
}

static size_t _char_size(const char *chars) {
    size_t size = 0;
    while (chars[size] != '\0') {
        size++;
    }
    return size;
}

// **********************************************