#ifndef TOYS_CATALOG_IO_H
#define TOYS_CATALOG_IO_H

struct status read_data(struct toy_array *store);

void write_data(struct toy_array store);

char* read_data_chunks(void);

void free_data(struct toy_array* store);

#endif //TOYS_CATALOG_IO_H
