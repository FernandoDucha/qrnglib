/* 
 * File:   RWPset.h
 * Author: fernando
 *
 * Created on 30 de Abril de 2013, 18:46
 */

#ifndef DPSET_H
#define	DPSET_H
#include "DataPoints.h"
#include "DataPointsSet.h"
//DataPointsSet Pre-Def Types
typedef DataPointsSet<long double> DataSetLD;
typedef DataPointsSet<long int> DataSetLI;
typedef DataPointsSet<int> DataSetInt;
typedef DataPointsSet<unsigned long int> DataSetULI;
typedef DataPointsSet<unsigned int> DataSetUInt;
typedef DataPointsSet<float> DataSetFloat;
typedef DataPointsSet<short> DataSetShort;
typedef DataPointsSet<unsigned short> DataSetUShort;
typedef DataPointsSet<unsigned char> DataSetsUC;
//DataPoints Pre-Def Types
typedef DataPoints<long double> DataPointsLD;
typedef DataPoints<double> DataPointsDouble;
typedef DataPoints<long int> DataPointsLI;
typedef DataPoints<int> DataPointsInt;
typedef DataPoints<unsigned long int> DataPointsULI;
typedef DataPoints<unsigned int> DataPointsUInt;
typedef DataPoints<float> DataPointsFloat;
typedef DataPoints<short> DataPointsShort;
typedef DataPoints<unsigned short> DataPointsUShort;
typedef DataPoints<unsigned char> DataPointsUC;


#endif	/* RWPSET_H */

