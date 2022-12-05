#include "../toys/toys.h"
#include "../error/error.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int CHUNK_SIZE = 4;

unsigned int read_chunk(char* buffer) {
    int c = getchar();
    unsigned int i = 0;
    while ((i < CHUNK_SIZE - 1) && (c != '\n') && (c != -1)) {
        buffer[i] = (char) c;
        i += 1;
        c = getchar();
    }
    if ((c == '\n') || (c == -1)) {
        buffer[i] = '\0';
        return i;
    }
    buffer[i] = (char) c;
    return i + 1;
}

char* read_data_chunks(void) {
    char buffer[CHUNK_SIZE];
    unsigned int bytes_read = read_chunk(buffer);
    char* str = malloc(bytes_read * sizeof(char));
    if (!str) {
        free(str);
        return NULL;
    }
    strcat(str, buffer);
    while (bytes_read == CHUNK_SIZE) {
        bytes_read = read_chunk(buffer);
        char* tmp = realloc(str, (strlen(str) + bytes_read) * sizeof(char));
        if (!tmp) {
            free(tmp);
            free(str);
            return NULL;
        }
        str = tmp;
        strcat(str, buffer);
    }
    return str;
}

struct status read_data(struct toy_array *store) {
    struct status add_res;
    printf("How many toys to insert in store: ");
    int store_size = strtol(read_data_chunks(), NULL, 10);
    for (int i = 0; i < store_size; i++) {
        printf("Insert toy name: ");
        char* name = read_data_chunks();
        if (name == NULL) {
            init_message(&add_res, "Could not allocate memory for toy name", -1);
            return add_res;
        }
        double price;
        printf("Insert toy price: ");
        price = strtol(read_data_chunks(), NULL, 10);
        printf("Insert toy country: ");
        char* country = read_data_chunks();
        if (country == NULL) {
            free(name);
            name = NULL;
            init_message(&add_res, "Could not allocate memory for toy country", -1);
            return add_res;
        }
        int amount;
        printf("Insert toys amount: ");
        amount = strtol(read_data_chunks(), NULL, 10);
        add_res = add_toy(store, name, price, country, amount);
        if (add_res.status_code == -1){
            return add_res;
        }
        free(name);
        free(country);
    }
    init_message(&add_res, "Success", 0);
    return add_res;
}

void write_data(struct toy_array store) {
    for (int i = 0; i < store.size; i++){
        printf("name = %s, price = %.2f, country = %s, amount = %d\n",
               store.toys[i].name, store.toys[i].price,
               store.toys[i].country, store.toys[i].amount);
    }
}

void free_data(struct toy_array *store) {
    for (int i = 0; i < store->size; i++){
        free(store->toys[i].name);
        free(store->toys[i].country);
    }
    free(store->toys);
    store->toys = NULL;
}


