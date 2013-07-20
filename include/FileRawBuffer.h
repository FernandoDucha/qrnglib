/* 
 * File:   RawBuffer.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 13:36
 */

#ifndef RAWBUFFER_H
#define	RAWBUFFER_H
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <gmpxx.h>
#include "Cronometro.h"
using namespace std;

class FileRawBuffer {
public:

    typedef enum FETCH_MODE {
        NOTHING = 0, EVERYTHING = 1, PARTIAL = 2
    } Fetch;
    FileRawBuffer(char * filename, ulong size);
    FileRawBuffer(char * filename, Fetch mode = Fetch::NOTHING);
    virtual ~FileRawBuffer();
    ulong getSize() const;
    ulong getFileSize() const;
    void generateBufferComplete();
    void generateBuffer(ulong n);
    uint8_t * getBytesFromBuffer(ulong n);
    uint8_t * getBytesFromFile(ulong n);
    uint8_t * getBytesFromFileRandom(ulong n);
    void setFilePosition(u_int64_t to);
    void setBufferPosition(u_int64_t to);
    void resetInitialPos();
    void writeBuffer(char * filename);
    uint8_t * getBytesFromBufferRandom(ulong n);

    ulong getPos() const {
        return pos;
    }
private:

    uint8_t reverse(uint8_t b) {
        b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
        b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
        b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
        return b;
    }
    void initializeReverseTable();
    void setupRNG();
    void reSeed();
    ulong getRandomPos();
    uint8_t * rawBuffer;
    ulong pos;
    ulong size;
    ulong fsize;
    char * file;
    Fetch state;
    Cronometro chrono;
    ifstream filestream;
    gmp_randstate_t rng;
    static uint8_t * reverseTable;

};

#endif	/* RAWBUFFER_H */

