#ifndef LIBS_MANAGE_DATA_MANAGE_DATA_H_
#define LIBS_MANAGE_DATA_MANAGE_DATA_H_

#include "../toys/toys.h"
#include "stdio.h"

struct status read_data(struct toy_array *store, FILE *input_stream);

void write_data(struct toy_array store, FILE *output_stream);

void free_data(struct toy_array* store);

#endif  // LIBS_MANAGE_DATA_MANAGE_DATA_H_
