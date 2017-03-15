#include "hash.h"
#include <stdio.h>
#include <math.h> /* sqrt */
#define mulmod(a, b, m) (uint64_t)(((sdsl::uint128_t)(a) * (sdsl::uint128_t)(b)) % ((sdsl::uint128_t)(m)))


// Function to find modulo inverse of a
uint64_t hashFunction::modInverse(sdsl::uint128_t m)
{
    sdsl::uint128_t x, y;
    sdsl::uint128_t g = gcdExtended(a, m, &x, &y);
    aInv = (x % m + m) % m;
    if ((a * aInv) % m != 1) {
        /*Inverse doesn't exist*/
        ++a;
        return modInverse(m);
    } else {
        return aInv;
    }
}

// C function for extended Euclidean Algorithm
sdsl::uint128_t hashFunction::gcdExtended(sdsl::uint128_t aTemp, sdsl::uint128_t m, sdsl::uint128_t* x, sdsl::uint128_t* y)
{
    // Base Case
    if (!aTemp) {
        *x = 0, *y = 1;
        return m;
    }
    sdsl::uint128_t x1;
    sdsl::uint128_t y1; // To store results of recursive call
    sdsl::uint128_t gcd = gcdExtended(m % aTemp, aTemp, &x1, &y1);

    // Update x and y using results of recursive
    // call
    sdsl::uint128_t diff = ((m / aTemp) * x1);
    *x = y1 - diff;
    *y = x1;
    return gcd;
}

/* Function that checks whether or not a given number is
 * a prime number or not.
 */
bool isPrime(uint64_t input)
{
    uint64_t i;
    bool prime = true;
    if (input == 2) {
        return true;
    }
    if (input % 2 == 0 || input <= 1) {
        prime = false;
    } else {
        for (i = 3; i <= sqrt(input); i += 2) {
            if (input % i == 0) {
                prime = false;
            }
        }
    }
    return prime;
} // end isPrime

/*
 * Function for determining the next prime number
 */
uint64_t nextPrimeNumber(uint64_t inputNumber)
{
    uint64_t nextPrimeNumber;
    if (inputNumber <= 0) {
    } else {
        while (inputNumber != 0) {
            nextPrimeNumber = inputNumber + 1;
            if (nextPrimeNumber % 2 == 0 && nextPrimeNumber != 2) {
                nextPrimeNumber += 1;
            }
            while (!isPrime(nextPrimeNumber)) {
                nextPrimeNumber += 2;
            }
            if (isPrime(nextPrimeNumber))
                return nextPrimeNumber;
        }
    }
    return nextPrimeNumber;
} // end nextPrimeNumber
hashFunction::hashFunction(uint64_t M, uint64_t cmax):
	M(M)
{
    prime = nextPrimeNumber(cmax);
    a = 0.66 * prime;
    aInv = modInverse(prime);
}

/*
 * calculates and returns the key which includes
 * quotient value (stored in the hashtable)
 * mod value (is the initial address of the key)
*/
void hashFunction::getKey(uint64_t parentLoc,
    uint64_t itemID)
{
    uint64_t c = (itemID * M) + parentLoc;
    uint64_t cRand = mulmod(a, c, prime);
    initAd = cRand % M;
    quotient = cRand / M;
}

/*
 * reverses the hashfunction to get the itemID
*/
uint64_t hashFunction::recoverID(uint64_t initAd, uint64_t DIVM)
{
    sdsl::uint128_t cRandRec = ((sdsl::uint128_t)DIVM * (sdsl::uint128_t)M + (sdsl::uint128_t)initAd);
    uint64_t cRec = mulmod(aInv, cRandRec, prime); //(aInv*cRandRec)%prime;
    uint64_t IDRec = cRec / M;
    return IDRec;
}
/*
 * reverses the hashfunction to get the parent location
*/
uint64_t hashFunction::recoverParentLoc(uint64_t initAd, uint64_t DIVM)
{
    sdsl::uint128_t cRandRec = ((sdsl::uint128_t)DIVM * (sdsl::uint128_t)M + (sdsl::uint128_t)initAd);
    uint64_t cRec = mulmod(aInv, cRandRec, prime); //aInv % prime;
    uint64_t parentLoc = cRec % M;
    return parentLoc;
}
