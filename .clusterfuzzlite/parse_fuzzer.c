#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <csv.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  char **pstr = parse_csv(new_str);
  if (pstr != NULL) {
    free_csv_line(pstr);
  }

  free(new_str);
  return 0;
}