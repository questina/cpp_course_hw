#include <stdio.h>
#include "libs/toys/toys.h"
#include "libs/error/error.h"
#include "libs/io/io.h"

// Вариант #7
// Создать структуру для хранения позиций каталога магазина детских игрушек:
// названия и стоимости каждой игрушки,
// объема складских запасов,
// а также страны-производителя.
// Составить с ее использованием программу определения наличия игрушек,
// произведенных в интересующей пользователя стране.

int main(void) {
    struct status mes;
    struct toy_array store = {0, NULL};
    mes = read_data(&store);
    process_message(mes);
    if (store.toys == NULL) {
        fprintf(stderr, "Error in init_data");
        return 1;
    }
    write_data(store);
    struct toys_with_status toys_with_st;
    printf("What country do you want to search? ");
    char *country = read_data_chunks();
    toys_with_st = find_toys_spec_by_country(store, country);
    printf("%s\n", mes.message);
    write_data(toys_with_st.toys);
    free_data(&toys_with_st.toys);
    free_data(&store);
    return 0;
}
