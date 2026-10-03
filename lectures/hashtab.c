#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#define FNV_OFFSET_BASICS_64 14695981039346656037ULL
#define FNV_PRIME_64 1099511628211ULL

uint64_t fnvla_64(const void *data, size_t len) {
    const uint8_t *bytes = (const uint8_t *)data;
    uint64_t hash = FNV_OFFSET_BASICS_64;
    for (size_t i = 0; i < len; i++) {
        hash ^= bytes[i];
        hash *= FNV_PRIME_64;
    }
    return hash;
}

int main() {

}