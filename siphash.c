#include "./siphash.h"

#define CROUNDS 2
#define DROUNDS 4

#define SIPROUND \
    do { \
        v0 += v1;\
        v1 = rotl(v1, 13);\
        v1 ^= v0;\
        v0 = rotl(v0, 32);\
        v2 += v3;\
        v3 = rotl(v3, 16);\
        v3 ^= v2;\
        v0 += v3;\
        v3 = rotl(v3, 21);\
        v3 ^= v0;\
        v2 += v1;\
        v1 = rotl(v1, 17);\
        v1 ^= v2;\
        v2 = rotl(v2, 32);\
    }while(0)

uint64_t rotl(uint64_t x, uint64_t n){
    return ((x<<n)|(x>>(64UL-n)));
}

int siphash(uint8_t *in, uint64_t inlen, uint8_t *key, uint64_t keylen, uint64_t *out){
    uint64_t v0, v1, v2, v3;
    uint64_t m = 0, i = 0, x = 0;
    uint64_t offset = 0;
    if(!in || !out || !key || keylen < 16) return -1;

    v0 = 0x736f6d6570736575UL^(*(uint64_t *)(key));
    v1 = 0x646f72616e646f6dUL^(*(uint64_t *)(key+8));
    v2 = 0x6c7967656e657261UL^(*(uint64_t *)(key));
    v3 = 0x7465646279746573UL^(*(uint64_t *)(key+8));

    if(inlen >= 8){
        for(i = 0; i < (inlen-(inlen&7)); i+=8){
            m = *(uint64_t *)(in+i);
            v3 ^= m;
            for(x = 0; x < CROUNDS; ++x){
                SIPROUND;
            }
            v0 ^= m;
        }
    }

    m = inlen<<56;
    offset = inlen-(inlen&7);
    for(x = 0; x < (inlen&7); x++){
        m |= ((uint64_t)(*(in+offset+x)))<<(8*x);
    }
    
    v3 ^= m;
    for(x = 0; x < CROUNDS; ++x){
        SIPROUND;
    }
    v0 ^= m;

    v2 ^= 0xffUL;
    for(x = 0; x < DROUNDS; ++x){
        SIPROUND;
    }

    *out = (v0^v1^v2^v3);
    return 0;
}