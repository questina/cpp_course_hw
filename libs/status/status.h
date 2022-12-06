#ifndef LIBS_STATUS_STATUS_H_
#define LIBS_STATUS_STATUS_H_

#include "../toys/toys.h"
#include <stdio.h>

struct status {
    const char* message;
    int status_code;
};

struct toys_with_status {
    struct status st;
    struct toy_array toys;
};

void init_message(struct status *mes, const char* str_mes, int status_code);

void process_message(struct status mes, FILE* input_stream);


#endif  // LIBS_STATUS_STATUS_H_
