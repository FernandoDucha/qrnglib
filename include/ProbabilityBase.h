/* 
 * File:   ProbabilityBase.h
 * Author: fernando
 *
 * Created on 8 de Maio de 2013, 10:08
 */

#ifndef PROBABILITYBASE_H
#define	PROBABILITYBASE_H
#include <gsl/gsl_fit.h>
#include <gsl/gsl_math.h>
#include "DPBase.h"
#include "RWVBase.h"
#include "BinaryRandomWalk.h"
#include <iostream>
using namespace std;

class ProbabilityBase {
public:
    ProbabilityBase(BinaryRandomWalk * brwk);
    virtual ~ProbabilityBase();
    void SetDatabinp(RWVSInt* databinp);
    RWVSInt* GetDatabinp() const;
    RWVSInt* GetDatabinp(u_int64_t ws, u_int64_t ns, char* msg);
    DataSetInt* GetDatap(u_int64_t ws, u_int64_t ns, char* msg);
    bool FetchDataOnly(u_int64_t ws, u_int64_t ns, char* msg);
    void SetDatap(DataSetInt* datap);
    DataSetInt* GetDatap() const;
    void CurveFitting();
    void CurveFittingOnLine();
    void CurveFittingOnLine_1();
    void prepareAllBinWalksOnLine();
    void CurveFittingOnLineBuffer();
    void CurveFittingOnLineBuffer(DataPointsDouble * x, DataPointsDouble * y, double & b, double & a, double & SSE);
    void clearDataBin();
    void clearDataPoints();
    RWVInt * getWalkNByBits(u_int64_t N);
    DataPointsInt * getWalkNByPoints(u_int64_t N);
    RWVSInt* getWalkNByBits(u_int64_t beg , u_int64_t end );
    DataSetInt* getWalkNByPoints(u_int64_t beg , u_int64_t end );

    BinaryRandomWalk* GetThisbrwk() const {
        return thisbrwk;
    }
    
private:
    DataPointsUInt * pointsFromFitting;
    DataPointsUInt * pointsCurve;
    BinaryRandomWalk * thisbrwk;
    DataSetInt * datap;
    RWVSInt * databinp;
};

#endif	/* PROBABILITYBASE_H */

