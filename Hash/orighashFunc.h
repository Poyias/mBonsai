#ifndef CLEARY_HASH
#define CLEARY_HASH
#include <cstdint>
class origHash {
public:
    uint64_t initAd;
    uint64_t quotient;

    origHash getKey(uint64_t parentLoc, uint64_t itemID, uint64_t keyJ,
        uint64_t M, uint64_t prime, uint64_t a);
    uint64_t getInitAd() { return initAd; }
    uint32_t getQuotient() { return quotient; }
    /*
   *** The functions below work only if a is carefully selected such that its
   *mod inverse (aInv)
   *** will be able to reverse the hashfunction
  */
    /*  uint32_t recoverID(uint64_t initAd, uint32_t DIVM,
                           uint64_t M, uint64_t prime,
                           uint64_t aInv);
    uint64_t recoverParentLoc(uint64_t initAd,
                                        uint32_t DIVM, uint64_t M,
                                        uint64_t prime,
                                        uint64_t aInv);
    uint64_t recoverJ(uint64_t initAd, uint32_t DIVM,
                                uint64_t M, uint64_t prime,
                                uint64_t aInv);*/
};
#endif
