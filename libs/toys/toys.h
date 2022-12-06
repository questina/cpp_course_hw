#ifndef _LIBS_TOYS_TOYS_H_
#define _LIBS_TOYS_TOYS_H_

struct toy {
  char *name;
  double price;
  char *country;
  int amount;
};

struct toy_array {
  int size;
  struct toy *toys;
};

struct status add_toy(struct toy_array *store, char *toy_name, double toy_price,
            char *toy_country, int toy_amount);

struct toys_with_status find_toys_spec_by_country(struct toy_array store,
        const char *toy_country);

#endif  // _LIBS_TOYS_TOYS_H_
