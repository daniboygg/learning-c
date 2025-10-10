#include <stdio.h>
#include <assert.h>

// coordinate
typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

coordinate_t coord_new(int x, int y, int z) {
    coordinate_t coord = {x, y, z};
    return coord;
}

coordinate_t coord_scale(coordinate_t c, int scale) {
    coordinate_t coord = {.x = c.x * scale, .y = c.y * scale, .z = c.z * scale};
    return coord;
}

// alignment
typedef struct {
    char a;
    char b;
    char c;
    char d;
    int x;
    int y;
    int z;
} coordinate_t_aligned;

typedef struct {
    char a;
    int x;
    int y;
    int z;
} coordinate_t_not_aligned;


int main() {
    coordinate_t c = coord_new(20, 40, 5);
    assert(c.x == 20);
    assert(c.y == 40);
    assert(c.z == 5);

    coordinate_t scaled = coord_scale(c, 2);

    assert(scaled.x == 40);
    assert(scaled.y == 80);
    assert(scaled.z == 10);

    assert(sizeof(coordinate_t) == 12);
    assert(sizeof(coordinate_t_aligned) == 16);
    assert(sizeof(coordinate_t_not_aligned) == 16);

    return 0;
}
