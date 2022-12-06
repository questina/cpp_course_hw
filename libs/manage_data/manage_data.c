#include "../toys/toys.h"
#include "../status/status.h"
#include "manage_data.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct status read_data(struct toy_array *store, FILE *input_stream) {
    struct status add_res;
    printf("How many toys to insert in store: ");
    char *tmp = read_data_chunks(input_stream);
    if (tmp == NULL) {
        init_message(&add_res, "Could not read store_size", -1);
        return add_res;
    }
    long int store_size = strtol(tmp, NULL, 10);
    free_mem(tmp);
    if (store_size == 0) {
        init_message(&add_res, "No toys to read", -1);
        return add_res;
    }
    for (int i = 0; i < store_size; i++) {
        printf("Insert toy name: ");
        char* name = read_data_chunks(input_stream);
        if (name == NULL) {
            init_message(&add_res, "Could not allocate memory for toy name", -1);
            return add_res;
        }
        double price;
        printf("Insert toy price: ");
        tmp = read_data_chunks(input_stream);
        if (tmp == NULL) {
            free_mem(name);
            init_message(&add_res, "Could not read toy price", -1);
            return add_res;
        }
        price = strtod(tmp, NULL);
        free_mem(tmp);
        if (price == 0.0) {
            free_mem(name);
            init_message(&add_res, "Incorrect price", -1);
            return add_res;
        }
        printf("Insert toy country: ");
        char* country = read_data_chunks(input_stream);
        if (country == NULL) {
            free_mem(name);
            free_mem(country);
            name = NULL;
            init_message(&add_res, "Could not allocate memory for toy country", -1);
            return add_res;
        }
        unsigned long long amount;
        printf("Insert toys amount: ");
        tmp = read_data_chunks(input_stream);
        if (tmp == NULL) {
            free_mem(name);
            free_mem(country);
            init_message(&add_res, "Could not read toys amount", -1);
            return add_res;
        }
        amount = strtoll(tmp, NULL, 10);
        free_mem(tmp);
        if (amount == 0) {
            free_mem(name);
            free_mem(country);
            init_message(&add_res, "Incorrect amount", -1);
            return add_res;
        }
        add_res = add_toy(store, name, price, country, amount);
        free_mem(name);
        free_mem(country);
        if (add_res.status_code == -1) {
            return add_res;
        }
    }
    init_message(&add_res, "Success", 0);
    return add_res;
}

void write_data(struct toy_array store, FILE* output_stream) {
    for (int i = 0; i < store.size; i++) {
        fprintf(output_stream,
                "name = %s, price = %.2f, country = %s, amount = %llu\n",
                store.toys[i].name, store.toys[i].price,
                store.toys[i].country, store.toys[i].amount);
    }
}

void free_data(struct toy_array *store) {
    for (int i = 0; i < store->size; i++) {
        free(store->toys[i].name);
        free(store->toys[i].country);
    }
    free(store->toys);
    store->toys = NULL;
}


