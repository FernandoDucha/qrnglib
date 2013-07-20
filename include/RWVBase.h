/* 
 * File:   RWVBase.h
 * Author: fernando
 *
 * Created on 30 de Abril de 2013, 18:44
 */

#ifndef RWVBASE_H
#define	RWVBASE_H
#include "RandomWalkVector.h"
#include "RandomWalkVecSet.h"
//RandomWalkVector Pre-Def Types
typedef RandomWalkVector<long double> RWVLD;
typedef RandomWalkVector<long int> RWVLI;
typedef RandomWalkVector<int> RWVInt;
typedef RandomWalkVector<unsigned long int> RWVULI;
typedef RandomWalkVector<unsigned int> RWVUInt;
typedef RandomWalkVector<float> RWVFloat;
typedef RandomWalkVector<short> RWVShort;
typedef RandomWalkVector<unsigned short> RWVUShort;
typedef RandomWalkVector<unsigned char> RWVUC;
//RandomWalkVecSet Pre-Def Types
typedef RandomWalkVecSet<long double> RWVSLD;
typedef RandomWalkVecSet<long int> RWVSLI;
typedef RandomWalkVecSet<int> RWVSInt;
typedef RandomWalkVecSet<unsigned long int> RWVSULI;
typedef RandomWalkVecSet<unsigned int> RWVSUInt;
typedef RandomWalkVecSet<float> RWVSFloat;
typedef RandomWalkVecSet<short> RWVSShort;
typedef RandomWalkVecSet<unsigned short> RWVSUShort;
typedef RandomWalkVecSet<unsigned char> RWVSUC;
#endif	/* RWVBASE_H */

