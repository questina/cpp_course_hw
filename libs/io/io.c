#include "../toys/toys.h"
#include "../error/error.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int CHUNK_SIZE = 4;

unsigned int read_chunk(char* buffer) {
    char c = getchar();
    unsigned int i = 0;
    while ((i < CHUNK_SIZE - 1) && (c != '\n') && (c != EOF)) {
        buffer[i] = c;
        i += 1;
        c = getchar();
    }
    if ((c == '\n') || (c == EOF)) {
        buffer[i] = '\0';
        return i;
    }
    buffer[i] = c;
    return i + 1;
}

char* read_data_chunks(void) {
    fflush(stdin);
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
        str = realloc(str, (strlen(str) + bytes_read) * sizeof(char));
        if (!str) {
            free(str);
            return NULL;
        }
        strcat(str, buffer);
    }
    return str;
}

struct status read_data(struct toy_array *store) {
    struct status add_res;
    printf("How many toys to insert in store: ");
    int store_size = 0;
    scanf("%d", &store_size);
    for (int i = 0; i < store_size; i++) {
        printf("Insert toy name: ");
        char* name = read_data_chunks();
        if (name == NULL) {
            init_message(&add_res, "Could not allocate memory for toy name", -1);
            return add_res;
        }
        double price = 0;
        printf("Insert toy price: ");
        scanf("%lf", &price);
        printf("Insert toy country: ");
        char* country = read_data_chunks();
        if (country == NULL) {
            free(name);
            name = NULL;
            init_message(&add_res, "Could not allocate memory for toy country", -1);
            return add_res;
        }
        int amount = 0;
        printf("Insert toys amount: ");
        scanf("%d", &amount);
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


