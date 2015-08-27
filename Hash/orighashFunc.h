class origHash
{
 public:

unsigned long long initAd;
unsigned long long quotient;

origHash getKey(unsigned long long parentLoc, unsigned long long itemID,
unsigned long long keyJ,unsigned long long M,unsigned long long prime, unsigned long long a);

unsigned int recoverID(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv);
unsigned long long recoverParentLoc(unsigned long long initAd, unsigned int DIVM, unsigned long long M,unsigned long long prime, unsigned long long aInv);
unsigned long long recoverJ(unsigned long long initAd, unsigned int DIVM, 
unsigned long long M,unsigned long long prime, unsigned long long aInv);

unsigned long long getInitAd(){return initAd;}
unsigned int getQuotient(){return quotient;}
};
