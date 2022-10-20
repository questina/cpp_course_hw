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
      store->toys[0] = new_toy;
      store->size += 1;
    } else {
      store->toys =
          realloc(store->toys, (store->size + 1) * sizeof(struct toy));
      store->toys[store->size] = new_toy;
      store->size += 1;
    }
  }
  return 0;
}

struct toy_array find_toys_spec_by_country(const struct toy_array store,
                                           const char *toy_country) {
  struct toy_array suitable_toys = {0, NULL};
  for (int i = 0; i < store.size; i++) {
    if ((strcmp(store.toys[i].country, toy_country)) &&
        (store.toys[i].amount > 0)) {
      printf("name = %s, price = %f, amount = %d\n", store.toys[i].name,
             store.toys[i].price, store.toys[i].amount);
    }
  }
  return suitable_toys;
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