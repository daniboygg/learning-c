#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int len;
    const char *data;
} String;

String string_new(const char *str) {
    String s = {.data = str, .len = strlen(str)};
    return s;
}

size_t string_write(FILE *file, String str) {
    size_t written = fwrite(str.data, sizeof(char), str.len, file);
    return written;
}


int main() {
    FILE *file = fopen("example.txt", "w");
    if(file == NULL) {
        printf("Error getting file %d\n", errno);
        return -1;
    }

    String str = string_new("content áaaamigo to show the proper handling of file\n");
    size_t written = string_write(file, str);
    printf("written: %zd items of char\n", written);

    if (fclose(file) != 0) {
        printf("Error closing file %d\n", errno);
        return -1;
    }

    
    FILE *file2 = fopen("example.txt", "r");
    if(file2 == NULL) {
        printf("Error getting file %d\n", errno);
        return -1;
    }
    
    #define buffer_size 9
    char buffer[buffer_size] = {0};
    while(1) {
        size_t read = fread(buffer, sizeof(char), buffer_size - 1, file2);
        if (read == 0) break;
        buffer[read] = '\0';
        printf("%s", buffer);
    }

    return 0;
}




















