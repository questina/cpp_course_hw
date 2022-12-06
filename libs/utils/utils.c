#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int CHUNK_SIZE = 4;

void free_mem(char* str) {
    free(str);
}

unsigned int read_chunk(char* buffer, FILE *input) {
    int c = getc(input);
    unsigned int i = 0;
    while ((i < CHUNK_SIZE - 1) && (c != '\n') && (c != -1)) {
        buffer[i] = (char) c;
        i += 1;
        c = getc(input);
    }
    if ((c == '\n') || (c == -1)) {
        buffer[i] = '\0';
        return i;
    }
    buffer[i] = (char) c;
    buffer[i + 1] = '\0';
    return i + 1;
}

char* read_data_chunks(FILE *input) {
    char buffer[CHUNK_SIZE];
    unsigned int bytes_read = read_chunk(buffer, input);
    if (bytes_read == 0) {
        return NULL;
    }
    char* str = malloc((bytes_read + 1) * sizeof(char));
    if (str == NULL) {
        free_mem(str);
        return NULL;
    }
    snprintf(str, (bytes_read + 1) * sizeof(char), "%s", buffer);
    char* tmp = NULL;
    while (bytes_read == CHUNK_SIZE) {
        bytes_read = read_chunk(buffer, input);
        tmp = realloc(str, (strlen(str) + bytes_read + 1) * sizeof(char));
        if (!tmp) {
            free_mem(tmp);
            free_mem(str);
            return NULL;
        }
        str = tmp;
        snprintf(str + strlen(str), (bytes_read + 1) * sizeof(char), "%s", buffer);
    }
    return str;
}


