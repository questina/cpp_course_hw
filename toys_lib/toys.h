#ifndef TOYS_LIB_TOYS_H_
#define TOYS_LIB_TOYS_H_

struct toy {
  const char *name;
  double price;
  const char *country;
  int amount;
};

struct toy_array {
  int size;
  struct toy *toys;
};

int add_toy(struct toy_array *store, const char *toy_name, double toy_price,
            const char *toy_country, int toy_amount);

void find_toys_spec_by_country(struct toy_array store,
        const char *toy_country);

int check_add_res(int add_res, struct toy_array *store);

struct toy_array init_data(void);

#endif  // TOYS_LIB_TOYS_H_
