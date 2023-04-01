#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

char* get_file_content() {
    FILE *fp;
    char *buffer;
    long size;

    // Open file for reading
    fp = fopen("example.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Unable to open file.\n");
        exit(1);
    }

    // Get file size
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    // Allocate memory for file content
    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Unable to allocate memory.\n");
        fclose(fp);
        exit(1);
    }

    // Read file content into buffer
    if (fread(buffer, size, 1, fp) != 1) {
        fprintf(stderr, "Error reading file.\n");
        free(buffer);
        fclose(fp);
        exit(1);
    }

    // Close file
    fclose(fp);

    // Print file content
    // printf("%s", buffer);
    return buffer;
}
