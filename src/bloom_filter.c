#include "bloom_filter.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hashes.h"

static int *array;

int create_array(void)
{
    array = calloc(M, sizeof(int));
    if (!array)
        return 0;

    return 1;
}

void free_array(void)
{
    free(array);
    array = NULL;
}

int add_item(uint8_t *input)
{
    if (!array)
    {
        if (!create_array())
            return 0;
    }
    uint32_t h1 = murmur(input, strlen((char *)input), 42);
    uint32_t h2 = fnv_1a(input);
    for (uint32_t i = 0; i < K; i++)
    {
        uint32_t pos = (h1 + h2 * i) % M;
        array[pos] = 1;
    }

    return 1;
}

int is_item_in(uint8_t *input)
{
    if (!array)
        return 0;

    uint32_t h1 = murmur(input, strlen((char *)input), 42);
    uint32_t h2 = fnv_1a(input);
    for (uint32_t i = 0; i < K; i++)
    {
        uint32_t pos = (h1 + h2 * i) % M;
        if (!array[pos])
            return 0;
    }

    return 1;
}
