#ifndef LIBS_IO_IO_H_
#define LIBS_IO_IO_H_

#include "../toys/toys.h"
#include "stdio.h"

struct status read_data(struct toy_array *store, FILE *input_stream);

void write_data(struct toy_array store);

char* read_data_chunks(FILE *input);

void free_data(struct toy_array* store);

#endif  // LIBS_IO_IO_H_
