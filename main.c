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

// L14
void concat_strings(char *str1, const char *str2) {
    int end = 0;
    for (end = 0; str1[end] != '\0'; end++) {
    }
    for (int i = 0; str2[i] != '\0'; i++) {
        str1[end] = str2[i];
        end++;
    }
    str1[end] = '\0';
}

// CH3 L15
typedef struct TextBuffer {
    size_t length;
    char buffer[64];
} text_buffer_t;

int smart_append(text_buffer_t *dest, const char *src) {
    if (dest == NULL || src == NULL) {
        return 1;
    }
    const size_t BUFFER_SIZE = sizeof(dest->buffer);
    const size_t SCR_LENGTH = strlen(src);
    const size_t REMAINING = BUFFER_SIZE - dest->length - 1;

    if (SCR_LENGTH > REMAINING) {
        strncat(dest->buffer, src, REMAINING);
        dest->length = BUFFER_SIZE - 1;
        return 1;
    } else {
        strncat(dest->buffer, src, REMAINING);
        dest->length += SCR_LENGTH;
        return 0;
    }
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

    do {
        char str1[100] = "Hello ";
        const char *str2 = "World";
        concat_strings(str1, str2);
        assert(strcmp(str1, "Hello World") == 0);
        assert(str1[11] == '\0');
    } while (0);

    // CH3 l15
    do {
        text_buffer_t dest;
        const char *src = NULL;
        assert(smart_append(&dest, src) == 1);
    } while (0);
    do {
        text_buffer_t dest;
        strcpy(dest.buffer, "");
        dest.length = 0;
        const char *src = "Hello";
        assert(smart_append(&dest, src) == 0);
        assert(strcmp(dest.buffer, "Hello") == 0);
        assert(dest.length == 5);
    } while (0);
    do {
        text_buffer_t dest;
        strcpy(dest.buffer, "This is a very long string that will fill up the entire buffer.");
        dest.length = 63;
        const char *src = " Extra";
        assert(smart_append(&dest, src) == 1);
        assert(strcmp(dest.buffer, "This is a very long string that will fill up the entire buffer.") == 0);
        assert(dest.length == 63);
    } while (0);
    do {
        text_buffer_t dest;
        strcpy(dest.buffer, "This is a long string");
        dest.length = 21;
        const char *src = " that will fill the whole buffer and leave no space for some of the chars.";
        assert(smart_append(&dest, src) == 1);
        assert(strcmp(dest.buffer, "This is a long string that will fill the whole buffer and leave") == 0);
        assert(dest.length == 63);
    } while (0);

    return 0;
}
