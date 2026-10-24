#ifndef HASHES_H
#define HASHES_H

#include <stddef.h>
#include <stdint.h>

#define FNV_OFFSET_BASIS_32 2166136261u
#define FNV_PRIME_32 16777619u

uint32_t murmur(const uint8_t *input, size_t len, uint32_t seed);
uint32_t fnv_1a(uint8_t *input);

#endif // !HASHES_H
