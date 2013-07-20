/* 
 * File:   RandomNumberGenerator.h
 * Author: fernando
 *
 * Created on June 1, 2013, 4:25 PM
 */

#ifndef RANDOMNUMBERGENERATOR_H
#define	RANDOMNUMBERGENERATOR_H
#include "FileRawBuffer.h"
#include "GeneralUsage.h"
class RandomNumberGenerator {
    char lookUpTable[256][3];
public:
    RandomNumberGenerator(FileRawBuffer * frwb);
    RandomNumberGenerator(char * DataFileName);
    mpz_class getNumberExactBits(ulong nbits);
    mpz_class getNumberWithMaxBits(ulong nbits);
    mpz_class getNumberWithMaxBitsFromBuffer_v1(ulong nbits);
    mpz_class getNumberWithMaxBitsFromBuffer_v2(ulong nbits);    
    mpz_class getNumber(mpz_class UB);
    mpz_class getNumber(mpz_class LB, mpz_class UB);
    mpf_class get01(ulong prec);
    void generateLookUpTable();
    virtual ~RandomNumberGenerator();
private:
    RandomNumberGenerator();
    FileRawBuffer * rawbuffer;
};

#endif	/* RANDOMNUMBERGENERATOR_H */

