/* 
 * File:   BinaryRandomWalk.cpp
 * Author: fernando
 * 
 * Created on 27 de Abril de 2013, 14:50
 */

#include <assert.h>

#include "BinaryRandomWalk.h"
unsigned char ** BinaryRandomWalk::LookUpTable = 0;
unsigned char * BinaryRandomWalk::Mask = 0;

BinaryRandomWalk::BinaryRandomWalk(FileRawBuffer * fbuffer) {
    BinaryRandomWalk::createLookUpTable();
    BinaryRandomWalk::createMaskTable();
    this->fbuffer = fbuffer;
    maximumPossibleWalks();
    WalkMask = 255;
    fbuffer->resetInitialPos();
}

uint64_t BinaryRandomWalk::GetNumberRandomWalks() const {
    return numberRandomWalks;
}

BinaryRandomWalk::BinaryRandomWalk(FileRawBuffer * fbuffer, unsigned long int WS) : BinaryRandomWalk(fbuffer) {
    SetWalkSize(WS);
}

BinaryRandomWalk::~BinaryRandomWalk() {
}

DataSetInt * BinaryRandomWalk::performAllWalksByPoints() {
    fbuffer->resetInitialPos();
    DataSetInt * ret = new DataSetInt(numberRandomWalks);
    for (unsigned int i = 0; i < numberRandomWalks; i++) {
        ret->put(performOneWalkByPoints());
    }
    return ret;
}

RWVSInt * BinaryRandomWalk::performAllWalksByBits() {
    fbuffer->resetInitialPos();
    RWVSInt * ret = new RWVSInt(numberRandomWalks);
    for (unsigned int i = 0; i < numberRandomWalks; i++) {
        ret->put(performOneWalkByBits());
    }
    return ret;
}

void BinaryRandomWalk::setNextRwkPos(int i) {
    this->fbuffer->setFilePosition(i * numberRandomWalks * WalkByteSize);
}

DataPointsInt * BinaryRandomWalk::performOneWalkByPoints() {
    unsigned char * temp = fbuffer->getBytesFromBuffer(WalkByteSize);
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    DataPointsInt * ret = new DataPointsInt();
    short actualP = 0;
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            actualP += (tableresp[j]) ? 1 : -1;
            walk[walkLeft] = actualP;
            walkLeft++;
        }
    }
    delete [] temp;
    ret->receiveData(walk, walkSize);
    return ret;
}

BinaryRandomWalk::BinaryRandomWalk(FileRawBuffer * fbuffer, unsigned long int WS, uint64_t Nwalks) : BinaryRandomWalk(fbuffer, WS) {
    numberRandomWalks = Nwalks;
}

RWVInt * BinaryRandomWalk::performOneWalkByBits() {
    unsigned char * temp = fbuffer->getBytesFromBuffer(WalkByteSize);
    //cout << mpz_class(temp[WalkByteSize - 1]).get_str(2) << "---" << mpz_class(WalkMask).get_str(2) <<"---"<<mpz_class(temp[WalkByteSize - 1]&WalkMask).get_str(2)<< endl;
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    RWVInt * ret = new RWVInt();
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            walk[walkLeft] = (tableresp[j]) ? 1 : -1;
            walkLeft++;
        }
    }
    //cout<<walk[walkLeft-1]<<endl;
    delete [] temp;
    ret->receiveData(walk, walkSize);
    delete [] walk;
    return ret;
}

RWVInt * BinaryRandomWalk::performWalkNByBits(int N) {
    assert(N < maximumPossibleWalks());
    fbuffer->setBufferPosition(N*WalkByteSize);
    unsigned char * temp = fbuffer->getBytesFromBuffer(WalkByteSize);
    //cout << mpz_class(temp[WalkByteSize - 1]).get_str(2) << "---" << mpz_class(WalkMask).get_str(2) <<"---"<<mpz_class(temp[WalkByteSize - 1]&WalkMask).get_str(2)<< endl;
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    RWVInt * ret = new RWVInt();
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            walk[walkLeft] = (tableresp[j]) ? 1 : -1;
            walkLeft++;
        }
    }
    //cout<<walk[walkLeft-1]<<endl;
    delete [] temp;
    ret->receiveData(walk, walkSize);
    delete [] walk;
    return ret;
}

DataPointsInt * BinaryRandomWalk::performWalkNByPoints(int N) {
    assert(N < maximumPossibleWalks());
    fbuffer->setBufferPosition(N*WalkByteSize);
    unsigned char * temp = fbuffer->getBytesFromBuffer(WalkByteSize);
    //cout << mpz_class(temp[WalkByteSize - 1]).get_str(2) << "---" << mpz_class(WalkMask).get_str(2) <<"---"<<mpz_class(temp[WalkByteSize - 1]&WalkMask).get_str(2)<< endl;
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    DataPointsInt * ret = new DataPointsInt();
    short actualP = 0;
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            actualP += (tableresp[j]) ? 1 : -1;
            walk[walkLeft] = actualP;
            walkLeft++;
        }
    }
    delete [] temp;
    ret->receiveData(walk, walkSize);
    delete [] walk;
    return ret;
}

DataPointsInt * BinaryRandomWalk::performOneWalkByPointsOnLineRandom() {
    unsigned char * temp = fbuffer->getBytesFromFileRandom(WalkByteSize);
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    DataPointsInt * ret = new DataPointsInt();
    short actualP = 0;
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            actualP += (tableresp[j]) ? 1 : -1;
            walk[walkLeft] = actualP;
            walkLeft++;
        }
    }
    delete [] temp;
    ret->receiveData(walk, walkSize);
    return ret;
}

DataSetInt * BinaryRandomWalk::performAllWalksByPointsOnLineRandom() {
    DataSetInt * ret = new DataSetInt(numberRandomWalks);
    for (unsigned int i = 0; i < numberRandomWalks; i++) {
        ret->put(performOneWalkByPoints());
    }
    return ret;
}

RWVInt * BinaryRandomWalk::performOneWalkByBitsOnLineRandom() {
    unsigned char * temp = fbuffer->getBytesFromFileRandom(WalkByteSize);
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    RWVInt * ret = new RWVInt();
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            walk[walkLeft] = (tableresp[j]) ? 1 : -1;
            walkLeft++;
        }
    }
    delete [] temp;
    ret->receiveData(walk, walkSize);
    delete [] walk;
    return ret;
}

RWVSInt * BinaryRandomWalk::performAllWalksByBitsOnLineRandom() {
    RWVSInt * ret = new RWVSInt(numberRandomWalks);
    for (unsigned int i = 0; i < numberRandomWalks; i++) {
        ret->put(performOneWalkByBitsOnLineRandom());
    }
    return ret;
}

DataPointsInt * BinaryRandomWalk::performOneWalkByPointsOnLine() {
    unsigned char * temp = fbuffer->getBytesFromFile(WalkByteSize);
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    DataPointsInt * ret = new DataPointsInt();
    short actualP = 0;
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            actualP += (tableresp[j]) ? 1 : -1;
            walk[walkLeft] = actualP;
            walkLeft++;
        }
    }
    delete [] temp;
    ret->receiveData(walk, walkSize);
    delete walk;
    return ret;
}

DataSetInt * BinaryRandomWalk::performAllWalksByPointsOnLine() {
    DataSetInt * ret = new DataSetInt(numberRandomWalks);
    for (unsigned int i = 0; i < numberRandomWalks; i++) {
        ret->put(performOneWalkByPointsOnLine());
    }
    return ret;
}

RWVInt * BinaryRandomWalk::performOneWalkByBitsOnLine() {
    unsigned char * temp = fbuffer->getBytesFromFile(WalkByteSize);
    temp[WalkByteSize - 1] = temp[WalkByteSize - 1] & WalkMask;
    int * walk = new int[walkSize];
    RWVInt * ret = new RWVInt();
    unsigned int walkLeft = 0;
    for (unsigned int i = 0; i < WalkByteSize; i++) {
        unsigned char * tableresp = LookUpTable[(int) temp[i]];
        for (int j = 7; ((j >= 0)&&(walkLeft < walkSize)); j--) {
            walk[walkLeft] = (tableresp[j]) ? 1 : -1;
            walkLeft++;
        }
    }
    delete [] temp;
    ret->receiveData(walk, walkSize);
    delete [] walk;
    return ret;
}

RWVSInt * BinaryRandomWalk::performAllWalksByBitsOnLine() {
    RWVSInt * ret = new RWVSInt(numberRandomWalks);
    for (unsigned int i = 0; i < numberRandomWalks; i++) {
        ret->put(performOneWalkByBitsOnLine());
    }
    return ret;
}

u_int64_t BinaryRandomWalk::maximumPossibleWalks() {
    unsigned long int ret = floor((double) fbuffer->getSize() / WalkByteSize);
    return ret;
}

unsigned long int BinaryRandomWalk::GetWalkSize() const {
    return walkSize;
}

void BinaryRandomWalk::createLookUpTable() {
    if (LookUpTable == NULL) {
        LookUpTable = new unsigned char *[256];
        for (int i = 0; i < 256; i++) {
            LookUpTable[i] = new unsigned char[8];
            int t = i;
            for (int j = 7; j >= 0; j--) {
                LookUpTable[i][j] = t & 1;
                t = t >> 1;
            }
        }
    }
}

void BinaryRandomWalk::createMaskTable() {
    if (Mask == NULL) {
        Mask = new unsigned char[9];
        Mask[8] = 255;
        for (int i = 1; i < 8; i++) {
            Mask[i] = 255 >> i;
        }
    }
}

bool BinaryRandomWalk::canProduceSets() {
    if (fbuffer->getFileSize() >= numberRandomWalks * WalkByteSize) {
        return true;
    } else {
        return false;
    }
}
