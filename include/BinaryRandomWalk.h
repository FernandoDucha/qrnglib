/* 
 * File:   BinaryRandomWalk.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 14:50
 */

#ifndef BINARYRANDOMWALK_H
#define	BINARYRANDOMWALK_H
#include <stdlib.h>
#include "FileRawBuffer.h"
#include "DPBase.h"
#include "RWVBase.h"
#include <math.h>
#include <iostream>
class BinaryRandomWalk {
public:    
    static  unsigned char ** LookUpTable;
    static  unsigned char * Mask;
    BinaryRandomWalk(FileRawBuffer * fbuffer);
    BinaryRandomWalk(FileRawBuffer * fbuffer, unsigned long int WS);
    BinaryRandomWalk(FileRawBuffer * fbuffer, unsigned long int WS, uint64_t NwalksBits);
    
    virtual ~BinaryRandomWalk();
    void SetWalkSize(unsigned long int walkSize);
    void SetNumberOfWalks(uint64_t numWalkSize);
    DataPointsInt * performOneWalkByPoints();
    DataSetInt * performAllWalksByPoints();
    RWVInt * performOneWalkByBits();
    RWVSInt * performAllWalksByBits();
    DataPointsInt * performOneWalkByPointsOnLineRandom();
    DataSetInt * performAllWalksByPointsOnLineRandom();
    RWVInt * performOneWalkByBitsOnLineRandom();
    RWVSInt * performAllWalksByBitsOnLineRandom();
    DataPointsInt * performOneWalkByPointsOnLine();
    DataSetInt * performAllWalksByPointsOnLine();
    RWVInt * performOneWalkByBitsOnLine();
    RWVSInt * performAllWalksByBitsOnLine();
    RWVInt * performWalkNByBits(int N);
    DataPointsInt * performWalkNByPoints(int N);
    static void createLookUpTable();
    static void createMaskTable();
    u_int64_t  maximumPossibleWalks();
    unsigned long int GetWalkSize() const; 
    void setNextRwkPos(int i);
    bool canProduceSets();
    
    bool prepareData(){
        fbuffer->generateBuffer(WalkByteSize*numberRandomWalks);
        return (fbuffer->getSize()>0)?true:false;
    }
    uint64_t GetNumberRandomWalks() const;
private:
    
    FileRawBuffer * fbuffer;
    unsigned long int walkSize;
    unsigned char WalkMask;
    unsigned long int WalkByteSize;
    uint64_t numberRandomWalks;
};
inline void BinaryRandomWalk::SetWalkSize(unsigned long int walkSize) {
    this->walkSize = walkSize;
    if (this->walkSize % 8 != 0) {
        WalkMask = Mask[8 - (walkSize % 8)];
    }
    WalkByteSize = ceil((double) walkSize / 8);

}

inline void BinaryRandomWalk::SetNumberOfWalks(uint64_t numWalkSize) {
    numberRandomWalks = numWalkSize;
}
#endif	/* BINARYRANDOMWALK_H */

