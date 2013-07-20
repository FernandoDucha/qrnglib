/* 
 * File:   RandomNumberGenerator.cpp
 * Author: fernando
 * 
 * Created on June 1, 2013, 4:25 PM
 */

#include <gmp.h>

#include "RandomNumberGenerator.h"
#include "BinaryRandomWalk.h"

RandomNumberGenerator::RandomNumberGenerator() {
    generateLookUpTable();
    BinaryRandomWalk::createMaskTable();
}

RandomNumberGenerator::RandomNumberGenerator(FileRawBuffer* frwb) : RandomNumberGenerator() {
    rawbuffer = frwb;
}

RandomNumberGenerator::RandomNumberGenerator(char * DataFileName) : RandomNumberGenerator() {
    rawbuffer = new FileRawBuffer(DataFileName);
}

RandomNumberGenerator::~RandomNumberGenerator() {
    //delete rawbuffer;
}

mpz_class RandomNumberGenerator::getNumberExactBits(ulong nbits) {
    mpz_class ret = getNumberWithMaxBits(nbits);
    mpz_class temp;
    mpz_pow_ui(temp.get_mpz_t(), mpz_class(2).get_mpz_t(), nbits - 1);
    if (ret < temp) {
        ret += temp;
    }
    return ret;
}

mpz_class RandomNumberGenerator::getNumberWithMaxBits(ulong nbits) {
    //    ulong bytes = ((nbits % 8) == 0) ? (nbits / 8) : (nbits / 8 + 1);
    //    uint8_t WalkMask = BinaryRandomWalk::Mask[8 - (nbits % 8)];
    //    uint8_t * ret = rawbuffer->getBytesFromFileRandom(bytes);
    //    ret[bytes - 1] &= WalkMask;
    //    string temp = "";
    //    for (ulong i = 0; i < bytes; i++) {
    //        temp = lookUpTable[ret[i]] + temp;
    //    }
    //    return mpz_class(temp, 16);
    ulong limbs = ((nbits % 8) == 0) ? (nbits / 8) : (nbits / 8 + 1);
    uint8_t WalkMask = BinaryRandomWalk::Mask[8 - (nbits % 8)];
    uint8_t * ret = rawbuffer->getBytesFromFileRandom(8 * limbs);
    ret[limbs - 1] &= WalkMask;
    mpz_class resp = 0;
    numeric_limits<unsigned char> a;
    mpz_class base(a.max());
    for (int i = 0; i < limbs; i++) {
        mpz_class b1 = 0;
        uint8_t t = ret[i];
        mpz_pow_ui(b1.get_mpz_t(), base.get_mpz_t(), i);
        resp += t*b1;
    }
    return resp;
}

mpz_class RandomNumberGenerator::getNumberWithMaxBitsFromBuffer_v1(ulong nbits) {
    ulong limbs = ((nbits % 8) == 0) ? (nbits / 8) : (nbits / 8 + 1);
    uint8_t WalkMask = BinaryRandomWalk::Mask[8 - (nbits % 8)];
    uint8_t * ret = rawbuffer->getBytesFromBuffer(8 * limbs);
    ret[limbs - 1] &= WalkMask;
    mpz_class resp = 0;
    numeric_limits<unsigned char> a;
    mpz_class base(a.max());
    for (int i = 0; i < limbs; i++) {
        mpz_class b1 = 0;
        uint8_t t = ret[i];
        mpz_pow_ui(b1.get_mpz_t(), base.get_mpz_t(), i);
        resp += t*b1;
    }
    return resp;
}

mpz_class RandomNumberGenerator::getNumberWithMaxBitsFromBuffer_v2(ulong nbits) {
    ulong bytes = ((nbits % 8) == 0) ? (nbits / 8) : (nbits / 8 + 1);
    uint8_t WalkMask = BinaryRandomWalk::Mask[8 - (nbits % 8)];
    uint8_t * ret = rawbuffer->getBytesFromBufferRandom(bytes);
    ret[bytes - 1] &= WalkMask;
    string temp = "";
    for (ulong i = 0; i < bytes; i++) {
        temp = lookUpTable[ret[i]] + temp;
    }
    return mpz_class(temp, 16);
}

void RandomNumberGenerator::generateLookUpTable() {
    for (int i = 0; i < 256; i++) {
        char buffer[4];
        sprintf(buffer, "%02X", i);
        memcpy(lookUpTable[i], buffer, 3);
    }
}

mpz_class RandomNumberGenerator::getNumber(mpz_class UB) {
    int bitsize = ceil(log2_temp(UB));
    bitsize=((bitsize%8)==0)?(bitsize/8):(bitsize/8+1);
    return getNumberWithMaxBitsFromBuffer_v2(8*bitsize) % (UB);
}

mpz_class RandomNumberGenerator::getNumber(mpz_class LB, mpz_class UB) {
    mpz_class diff= UB-LB;
    int bitsize = ceil(log2_temp(diff));
    bitsize=((bitsize%8)==0)?(bitsize/8):(bitsize/8+1);
    mpz_class ret = LB + getNumberWithMaxBitsFromBuffer_v2(8*bitsize) % (diff+1);
    return ret;
}

mpf_class RandomNumberGenerator::get01(ulong prec) {
    mpf_class numerator = mpf_class(getNumberWithMaxBitsFromBuffer_v2(prec));
    mpf_class denominator =2;
    mpf_pow_ui(denominator.get_mpf_t(),denominator.get_mpf_t(),prec);
    denominator--;
    return numerator/denominator;
}
