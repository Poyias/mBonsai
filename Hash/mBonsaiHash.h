#ifndef HASH_RECANDGAMMA
#define HASH_RECANDGAMMA
#include "sdsl/uint128_t.hpp"
#include <cstdint>

class hashFunction {
public:
    uint64_t initAd;
    uint64_t quotient;

    void getKey(uint64_t parentLoc, uint64_t itemID,
        uint64_t M, uint64_t prime,
        uint64_t a);

    inline uint64_t getInitAd() { return initAd; }
    inline uint64_t getQuotient() { return quotient; }

    uint64_t recoverID(uint64_t initAd, uint64_t DIVM, uint64_t M, uint64_t prime, uint64_t aInv);
    uint64_t recoverParentLoc(uint64_t initAd, uint64_t DIVM, uint64_t M, uint64_t prime, uint64_t aInv);
};
#endif
