#include <stdlib.h>
#include <stdio.h>
#include "toys_lib/toys.h"

// Вариант #7
// Создать структуру для хранения позиций каталога магазина детских игрушек:
// названия и стоимости каждой игрушки,
// объема складских запасов,
// а также страны-производителя.
// Составить с ее использованием программу определения наличия игрушек,
// произведенных в интересующей пользователя стране.

int main() {
  struct toy_array store = init_data();
  if (store.toys == NULL){
      fprintf(stderr, "Error in init_data");
      return 1;
  }
  find_toys_spec_by_country(store, "USA");
  free(store.toys);
  return 0;
}
