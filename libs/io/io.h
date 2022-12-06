#ifndef _LIBS_IO_IO_H_
#define _LIBS_IO_IO_H_

#include "../toys/toys.h"

struct status read_data(struct toy_array *store);

void write_data(struct toy_array store);

char* read_data_chunks(void);

void free_data(struct toy_array* store);

#endif  // _LIBS_IO_IO_H_
