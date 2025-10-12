#include <stdio.h>
#include <assert.h>
#include <string.h>

// coordinate
typedef struct Coordinate {
    int x;
    int y;
    int z;
} coordinate_t;

coordinate_t coord_new(int x, int y, int z) {
    coordinate_t coord = {.x = x, .y = y, .z = z};
    return coord;
}

coordinate_t coord_scale(coordinate_t coord, int scale) {
    coordinate_t c = {.x = coord.x * scale, .y = coord.y * scale, .z = coord.z * scale};
    return c;
}

void coord_update(coordinate_t coord, int new_x) {
    coord.x = new_x;
}

coordinate_t coord_update_and_return_x(coordinate_t coord, int new_x) {
    coord.x = new_x;
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


// ch3
typedef struct CodeFile {
    int lines;
    int filetype;
} codefile_t;

codefile_t codefile_change_filetype(codefile_t *cf, int new_filetype) {
    cf->filetype = new_filetype;
    return *cf;
}

void update_file(int filedata[200], int new_filetype, int new_num_lines) {
    filedata[0] = new_num_lines;
    filedata[1] = new_filetype;
    filedata[199] = 0;
}

typedef struct Graphics {
    int fps;
    int height;
    int width;
} graphics_t;

void dump_graphics(graphics_t gsettings[10]) {
    int *ptr = (int *) gsettings;
    for (int i = 0; i < 30; i++) {
        printf("settings[%d] = %d\n", i, ptr[i]);
    }
}

// void core_utils_func(int core_utilization[]) {
//     // array decays to a pointer so sizeof return the size of a pointer not size of the array
//     printf("sizeof core_utilization in core_utils_func: %zu\n", sizeof(core_utilization));
// }

void concat_strings(char *str1, const char *str2) {
    int end = 0;
    for (end = 0; str1[end] != '\0'; end++) {}
    for (int i = 0; str2[i] != '\0'; i++) {
        str1[end] = str2[i];
        end++;
    }
    str1[end] = '\0';
}

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

    // ch3
    coordinate_t c1 = coord_new(60, 40, 5);
    coord_update(c1, 20);
    assert(c1.x == 60);

    c1 = coord_new(60, 40, 5);
    coordinate_t c2 = coord_update_and_return_x(c1, 20);
    assert(c1.x == 60);
    assert(c2.x == 20);

    codefile_t cf = {.lines = 300, .filetype = 2};
    codefile_change_filetype(&cf, 3);
    assert(cf.lines == 300);
    assert(cf.filetype == 3);

    int filedata[200] = {0};
    update_file(filedata, 2, 2);
    assert(filedata[0] == 2);
    assert(filedata[1] == 2);
    assert(filedata[199] == 0);

    // graphics_t graphics_array[10] = {
    //     {60, 1080, 1920},
    //     {30, 720, 1280},
    //     {144, 1440, 2560},
    //     {75, 900, 1600},
    //     {120, 1080, 1920},
    //     {60, 2160, 3840},
    //     {240, 1080, 1920},
    //     {60, 768, 1366},
    //     {165, 1440, 2560},
    //     {90, 1200, 1920}
    // };
    // dump_graphics(graphics_array);

    // int core_utilization[] = {43, 67, 89, 92, 71, 43, 56, 12};
    // int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
    // printf("sizeof core_utilization in main: %zd\n", sizeof(core_utilization));
    // printf("len of core_utilization: %d\n", len);
    // core_utils_func(core_utilization);

    char str1[100] = "Hello ";
    const char *str2 = "World";
    concat_strings(str1, str2);
    assert(strcmp(str1, "Hello World") == 0);
    assert(str1[11] == '\0');

    return 0;
}
