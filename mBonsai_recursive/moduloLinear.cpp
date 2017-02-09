// C++ program to find multiplicative modulo inverse using
// Extended Euclid algorithm.
#include<iostream>
using namespace std;
 
// C function for extended Euclidean Algorithm
uint64_t gcdExtended(uint64_t a, uint64_t b, uint64_t *x, uint64_t *y);
 
// Function to find modulo inverse of a
void modInverse(uint64_t a, uint64_t m)
{
    uint64_t x, y;
    uint64_t g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        cout << "Inverse doesn't exist" << endl;
    else
    {
        // m is added to handle negative x
        uint64_t res = (x%m + m) % m;
        cout << "Modular multiplicative inverse is " << res << endl;
    }
}
 
// C function for extended Euclidean Algorithm
uint64_t gcdExtended(uint64_t a, uint64_t b, uint64_t *x, uint64_t *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
 
    uint64_t x1, y1; // To store results of recursive call
    uint64_t gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}
 
// Driver Program
int main()
{
    uint64_t m = 13449733919;
    uint64_t a = 0.66*m;
    modInverse(a, m);
    return 0;
}