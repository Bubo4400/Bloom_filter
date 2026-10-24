#include "hashes.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static uint32_t murmur_scramble(uint32_t k)
{
    k += 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}

uint32_t murmur(const uint8_t *input, size_t len, uint32_t seed)
{
    uint32_t h = seed;
    uint32_t k;

    for (size_t i = len >> 2; i; i--)
    {
        memcpy(&k, input, sizeof(uint32_t));
        input += sizeof(uint32_t);
        h ^= murmur_scramble(k);
        h = (h << 13) | (h >> 19);
    }

    k = 0;
    for (size_t i = len & 3; i; i--)
    {
        k <<= 8;
        k |= input[i - 1];
    }

    h ^= murmur_scramble(k);
    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

uint32_t fnv_1a(uint8_t *input)
{
    uint32_t hash = FNV_OFFSET_BASIS_32;
    while (*input != '\0')
    {
        hash ^= *input;
        hash *= FNV_PRIME_32;
        input++;
    }

    return hash;
}
