#ifndef LIBS_IO_IO_H_
#define LIBS_IO_IO_H_

struct status read_data(struct toy_array *store);

void write_data(struct toy_array store);

char* read_data_chunks(void);

void free_data(struct toy_array* store);

#endif  // LIBS_IO_IO_H_
