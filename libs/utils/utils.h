#ifndef LIBS_UTILS_UTILS_H_
#define LIBS_UTILS_UTILS_H_

#include <stdio.h>

void free_mem(char* str);
unsigned int read_chunk(char* buffer, FILE *input);
char* read_data_chunks(FILE *input);


#endif  // LIBS_UTILS_UTILS_H_
