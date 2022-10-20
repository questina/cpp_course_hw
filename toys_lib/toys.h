struct toy {
    char* name;
    double price;
    char* country;
    int amount;
};

struct toy_array {
    int size;
    struct toy *toys;
};

int add_toy(struct toy_array *store, char* toy_name, double toy_price, char* toy_country, int toy_amount);

struct toy_array find_toys_spec_by_country(struct toy_array store, const char* toy_country);

struct toy_array init_data(void);