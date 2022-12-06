#include <stdio.h>
#include "libs/toys/toys.h"
#include "libs/status/status.h"
#include "libs/manage_data/manage_data.h"
#include "libs/utils/utils.h"

// Вариант #7
// Создать структуру для хранения позиций каталога магазина детских игрушек:
// названия и стоимости каждой игрушки,
// объема складских запасов,
// а также страны-производителя.
// Составить с ее использованием программу определения наличия игрушек,
// произведенных в интересующей пользователя стране.

int main(int argc, char **argv) {
    FILE *instream, *outstream;
    if (argc == 1) {
        instream = stdin;
        outstream = stdout;
    } else if (argc == 2) {
        instream = fopen(argv[1], "r");
        outstream = stdout;
    } else if (argc == 3) {
        instream = fopen(argv[1], "r");
        outstream = fopen(argv[2], "w");
    } else {
        return -1;
    }
    struct status mes;
    struct toy_array store = {0, NULL};
    mes = read_data(&store, instream);
    process_message(mes, stderr);
    write_data(store, outstream);
    struct toys_with_status toys_with_st;
    printf("What country do you want to search? ");
    char *country = read_data_chunks(instream);
    toys_with_st = find_toys_spec_by_country(store, country);
    printf("%s\n", mes.message);
    free_mem(country);
    write_data(toys_with_st.toys, outstream);
    free_data(&toys_with_st.toys);
    free_data(&store);
    return 0;
}
