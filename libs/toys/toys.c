#include "toys.h"
#include "../error/error.h"
#include <stdlib.h>
#include <string.h>


struct status add_toy(struct toy_array *store, char *toy_name, double toy_price,
        char *toy_country, int toy_amount) {
    struct status mes;
    if (store == NULL) {
        init_message(&mes, "Incorrect store passed", -1);
        return mes;
    } else {
        struct toy new_toy;
        new_toy.name = malloc(strlen(toy_name) * sizeof(char));
        strcpy(new_toy.name, toy_name);
        new_toy.price = toy_price;
        new_toy.country = malloc(strlen(toy_country) * sizeof(char));
        strcpy(new_toy.country, toy_country);
        new_toy.amount = toy_amount;
        if (store->toys == NULL) {
            store->toys = malloc(sizeof(new_toy));
            if (!store->toys) {
                free(store->toys);
                init_message(&mes, "Cannot allocate memory for store", -1);
                return mes;
            }
            store->toys[0] = new_toy;
            store->size += 1;
        } else {
            struct toy *tmp_store = NULL;
            tmp_store =
                    realloc(store->toys, (store->size + 1) * sizeof(new_toy));
            if (!tmp_store) {
                free(tmp_store);
                init_message(&mes, "Cannot reallocate memory for store", -1);
                return mes;
            }
            store->toys = tmp_store;
            store->toys[store->size] = new_toy;
            store->size += 1;
        }
    }
    init_message(&mes, "Success", 0);
    return mes;
}

struct toys_with_status find_toys_spec_by_country(const struct toy_array store,
        const char *toy_country) {
    struct toys_with_status mes;
    mes.toys.toys = NULL;
    mes.toys.size = 0;
    if (toy_country == NULL) {
        init_message(&mes.st, "Incorrect toy country passed", -1);
        return mes;
    }
    for (int i = 0; i < store.size; i++) {
        if ((strcmp(store.toys[i].country, toy_country) == 0) &&
        (store.toys[i].amount > 0)) {
            add_toy(&mes.toys, store.toys[i].name, store.toys[i].price, store.toys[i].country, store.toys[i].amount);
        }
    }
    init_message(&mes.st, "Success", 0);
    return mes;
}

struct toy_array init_data(void) {
    struct toy_array store = {0, NULL};
    struct status add_res;
    add_res = add_toy(&store, "Teddybear", 89.99, "USA", 50);
    process_message(add_res);
    add_res = add_toy(&store, "Puzzle", 12.99, "Russia", 200);
    process_message(add_res);
    add_res = add_toy(&store, "HelloKitty", 35.5, "USA", 10000);
    process_message(add_res);
    add_res = add_toy(&store, "NinjaTurtle", 74.2, "China", 3);
    process_message(add_res);
    add_res = add_toy(&store, "Doggy", 58, "China", 45);
    process_message(add_res);
    return store;
}
