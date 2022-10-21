#include "toys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add_toy(struct toy_array *store, char *toy_name, double toy_price,
            char *toy_country, int toy_amount) {
  if (store == NULL) {
    fprintf(stderr, "Incorrect store passed");
    return -1;
  } else {
    struct toy new_toy;
    new_toy.name = toy_name;
    new_toy.price = toy_price;
    new_toy.country = toy_country;
    new_toy.amount = toy_amount;
    if (store->toys == NULL) {
      store->toys = malloc(sizeof(struct toy));
      if (!store->toys) {
          fprintf(stderr, "Cannot allocate memory for store");
          return -1;
      }
      store->toys[0] = new_toy;
      store->size += 1;
    } else {
      struct toy *tmp_store = NULL;
      tmp_store =
          realloc(store->toys, (store->size + 1) * sizeof(struct toy));
      if (!tmp_store) {
          free(store->toys);
          store->toys = NULL;
          fprintf(stderr, "Cannot reallocate memory for store");
          return -1;
      }
      store->toys = tmp_store;
      store->toys[store->size] = new_toy;
      store->size += 1;
    }
  }
  return 0;
}

void find_toys_spec_by_country(const struct toy_array store,
                                           const char *toy_country) {
  for (int i = 0; i < store.size; i++) {
    if ((strcmp(store.toys[i].country, toy_country) == 0) &&
        (store.toys[i].amount > 0)) {
      printf("name = %s, price = %.2f, amount = %d\n", store.toys[i].name,
             store.toys[i].price, store.toys[i].amount);
    }
  }
}

struct toy_array init_data() {
  struct toy_array store = {0, NULL};
  add_toy(&store, "Teddybear", 89.99, "USA", 50);
  add_toy(&store, "Puzzle", 12.99, "Russia", 200);
  add_toy(&store, "HelloKitty", 35.5, "USA", 10000);
  add_toy(&store, "NinjaTurtle", 74.2, "China", 3);
  add_toy(&store, "Doggy", 58, "China", 45);
  return store;
}
