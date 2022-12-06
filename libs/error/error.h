#ifndef LIBS_ERROR_ERROR_H_
#define LIBS_ERROR_ERROR_H_

#include "../toys/toys.h"

struct status {
    const char* message;
    int status_code;
};

struct toys_with_status {
    struct status st;
    struct toy_array toys;
};


void init_message(struct status *mes, const char* str_mes, int status_code);

void process_message(struct status mes);


#endif  // LIBS_ERROR_ERROR_H_
