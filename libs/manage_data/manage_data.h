#ifndef _LIBS_MANAGE_DATA_MANAGE_DATA_H_
#define _LIBS_MANAGE_DATA_MANAGE_DATA_H_

#include "../toys/toys.h"
#include "stdio.h"

struct status read_data(struct toy_array *store, FILE *input_stream);

void write_data(struct toy_array store, FILE *output_stream);

void free_data(struct toy_array* store);

#endif  // _LIBS_MANAGE_DATA_MANAGE_DATA_H_
