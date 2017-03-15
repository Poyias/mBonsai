#ifndef HASH
#define HASH
#include "sdsl/uint128_t.hpp"
#include <cstdint>

class hashFunction {
public:
    uint64_t initAd;
    uint64_t quotient;
    uint64_t a;
    uint64_t aInv;
    uint64_t prime;
    uint64_t M;

    hashFunction(){}
    hashFunction(uint64_t M, uint64_t cmax);
    void getKey(uint64_t parentLoc, uint64_t itemID);

    inline uint64_t getInitAd() { return initAd; }
    inline uint64_t getQuotient() { return quotient; }

    uint64_t recoverID(uint64_t initAd, uint64_t DIVM);
    uint64_t recoverParentLoc(uint64_t initAd, uint64_t DIVM);
	uint64_t modInverse(sdsl::uint128_t m);

    sdsl::uint128_t gcdExtended(sdsl::uint128_t aTemp, sdsl::uint128_t m, sdsl::uint128_t* x, sdsl::uint128_t* y);
};
#endif
