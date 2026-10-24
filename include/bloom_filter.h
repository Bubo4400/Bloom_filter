#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdint.h>

#define N 1000
#define M 4096
#define K 3

void free_array(void);
int add_item(uint8_t *input);
int is_item_in(uint8_t *input);

#endif // !BLOOM_FILTER_H

