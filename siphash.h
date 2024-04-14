#ifndef SIPHASH_H
#define SIPHASH_H
#include <stdint.h>

/* Custom implementation of SipHash-2-4 */
int siphash(uint8_t *in, uint64_t inlen, uint8_t *key, uint64_t keylen, uint64_t *out);

#endif