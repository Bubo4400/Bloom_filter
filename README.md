# Bloom Filter

A small, homemade [Bloom filter](https://en.wikipedia.org/wiki/Bloom_filter) written in C99, with an interactive command-line interface.

A Bloom filter is a probabilistic data structure that can tell you whether an item is **definitely not** in a set, or **probably** in it. It trades a small chance of false positives for very low memory usage and fast lookups.

## How it works

- The filter is an array of `M` slots, all starting at 0.
- Each item is hashed with two hash functions, **MurmurHash3** and **FNV-1a**.
- Using double hashing, `K` positions are derived: `pos = (h1 + i * h2) % M` for `i` in `0..K-1`.
- **Adding** an item sets those `K` positions to 1.
- **Checking** an item looks at the same `K` positions: if any of them is 0, the item was never added; if all are 1, it was *probably* added.

The parameters are defined in `includes/bloom_filter.h`:

| Constant | Value | Meaning                          |
|----------|-------|----------------------------------|
| `N`      | 1000  | Expected number of items         |
| `M`      | 4096  | Size of the filter               |
| `K`      | 3     | Number of hash positions per item |

## Project structure

```
.
├── includes/
│   ├── bloom_filter.h   # Filter parameters and API
│   └── hashes.h         # Hash function declarations
├── src/
│   ├── bloom_filter.c   # Filter implementation
│   ├── hashes.c         # MurmurHash3 and FNV-1a
│   └── main.c           # Interactive CLI
└── Makefile
```

## Building

Requires `gcc` and `make`.

```sh
make        # builds ./bloom_filter
make clean  # removes object files and the binary
```

## Usage

```sh
./bloom_filter
```

At the prompt, type:

- `add`: then enter an item to insert into the filter
- `get`: then enter an item to check whether it is in the filter
- `quit` or `exit`: leave the program

Example:

```
Homemade Bloom_filter
Please enter if you would like to 'add' to the bloom, or 'get' if your item is already in it: add
Please enter the item: apple
Please enter if you would like to 'add' to the bloom, or 'get' if your item is already in it: get
Please enter the item: apple
Your item is probably in the list
Please enter if you would like to 'add' to the bloom, or 'get' if your item is already in it: get
Please enter the item: banana
Your item is definitely not in the list
```
