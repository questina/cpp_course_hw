#include "status.h"
#include <stdio.h>

void init_message(struct status* mes, const char* str_mes, int status_code) {
    mes->message = str_mes;
    mes->status_code = status_code;
}

void process_message(struct status mes, FILE* input_stream) {
    if (mes.status_code == -1) {
        fprintf(input_stream, "%s", mes.message);
    }
}
