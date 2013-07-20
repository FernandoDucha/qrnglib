/* 
 * File:   ProbabilityBase.cpp
 * Author: fernando
 * 
 * Created on 8 de Maio de 2013, 10:08
 */

#include <assert.h>

#include "ProbabilityBase.h"

ProbabilityBase::ProbabilityBase(BinaryRandomWalk * brwk) {
    thisbrwk = brwk;
    datap = NULL;
    databinp = NULL;
    //    this->datap=brwk->performAllWalksByPoints();
    //    this->databinp=brwk->performAllWalksByBits();
}

ProbabilityBase::~ProbabilityBase() {
}

void ProbabilityBase::SetDatabinp(RWVSInt* databinp) {
    this->databinp = databinp;
}

RWVSInt* ProbabilityBase::GetDatabinp() const {
    return databinp;
}

void ProbabilityBase::SetDatap(DataSetInt* datap) {
    this->datap = datap;
}

DataSetInt* ProbabilityBase::GetDatap() const {
    return datap;
}

void ProbabilityBase::prepareAllBinWalksOnLine() {
    this->databinp = this->thisbrwk->performAllWalksByBitsOnLineRandom();
}

//void ProbabilityBase::CurveFitting(DataPointsLI * x, DataPointsLI * y,double & erro,double&chi) {

void ProbabilityBase::CurveFitting() {
    double * xaxis = new double[databinp->getSize()];
    double * yaxis = new double[databinp->getSize()];
    double * w = new double[ databinp->getSize()];
    RWVInt accumulated;
    double cov00, cov01, cov11, chi_sqr, error;
    double a, b;
    for (unsigned int i = 0; i < databinp->getSize(); i++) {
        xaxis[i] = log(i + 1);
        accumulated += *databinp->getElement(i);
        yaxis[i] = log((double) accumulated.abs_sum() / databinp->getSize());
        w[i] = 1;
    }

    gsl_fit_linear(xaxis, 1, yaxis, 1, databinp->getSize(), &a, &b, &cov00, &cov01, &cov11, &chi_sqr);
    error = 0;
    for (u_int64_t i = 0; i < databinp->getSize(); i++) {
        double curve = b * xaxis[i] + a;
        error += pow(yaxis[i] - curve, 2);
    }
    cout << a << "-" << b << "-" << chi_sqr << "-" << error << endl;

    delete [] xaxis;
    delete [] yaxis;
    delete [] w;
}

void ProbabilityBase::CurveFittingOnLine_1() {
    prepareAllBinWalksOnLine();
    CurveFitting();
}

void ProbabilityBase::CurveFittingOnLine() {
    ofstream out("data1.txt");
    double * xaxis = new double[thisbrwk->GetNumberRandomWalks()];
    double * yaxis = new double[thisbrwk->GetNumberRandomWalks()];
    double * w = new double[thisbrwk->GetNumberRandomWalks()];
    RWVInt accumulated;
    double cov00, cov01, cov11, chi_sqr, error = 0;
    double a, b;
    for (unsigned int i = 0; i < thisbrwk->GetNumberRandomWalks(); i++) {
        xaxis[i] = (i == 0) ? 0 : log(i);
        RWVInt * temp = thisbrwk->performOneWalkByBitsOnLine();
        accumulated += *temp;
        delete temp;
        yaxis[i] = log((double) accumulated.abs_sum() / thisbrwk->GetNumberRandomWalks());
        w[i] = 1;
    }
    error = 0;
    for (uint64_t i = 0; i < databinp->getSize(); i++) {
        double curve = b * xaxis[i] + a;
        error += pow(yaxis[i] - curve, 2);
    }
    gsl_fit_linear(xaxis, 1, yaxis, 1, thisbrwk->GetNumberRandomWalks(), &a, &b, &cov00, &cov01, &cov11, &chi_sqr);
    delete [] xaxis;
    delete [] yaxis;
    delete [] w;
}

void ProbabilityBase::CurveFittingOnLineBuffer() {
    ofstream out("data2.txt");
    double * xaxis = new double[thisbrwk->GetNumberRandomWalks()];
    double * yaxis = new double[thisbrwk->GetNumberRandomWalks()];
    RWVInt accumulated;
    double cov00, cov01, cov11, chi_sqr, error = 0;
    double a, b;
    for (unsigned int i = 0; i < thisbrwk->GetNumberRandomWalks(); i++) {
        xaxis[i] = log(i + 1);
        RWVInt * temp = thisbrwk->performOneWalkByBits();
        accumulated += *temp;
        delete temp;
        yaxis[i] = log((double) accumulated.abs_sum() / thisbrwk->GetNumberRandomWalks());
        //out << xaxis[i] << "--" << yaxis[i] << endl;
    }
    error = 0;

    gsl_fit_linear(xaxis, 1, yaxis, 1, thisbrwk->GetNumberRandomWalks(), &a, &b, &cov00, &cov01, &cov11, &chi_sqr);
    for (uint64_t i = 0; i < this->thisbrwk->GetNumberRandomWalks(); i++) {
        double curve = b * xaxis[i] + a;
        error += pow(yaxis[i] - curve, 2);
    }
    cout << a << "-" << b << "-" << cov00 << "-" << error << endl;
    delete [] xaxis;
    delete [] yaxis;
    out.close();
    //    delete [] w;
}

void ProbabilityBase::CurveFittingOnLineBuffer(DataPointsDouble * x, DataPointsDouble * y, double & b, double & a, double & SSE) {
    ofstream out("data2.txt");
    double * xaxis = new double[thisbrwk->GetNumberRandomWalks()];
    double * yaxis = new double[thisbrwk->GetNumberRandomWalks()];
    RWVInt accumulated;
    double cov00, cov01, cov11, chi_sqr, error = 0;
    double c0, c1;
    for (unsigned int i = 0; i < thisbrwk->GetNumberRandomWalks(); i++) {
        xaxis[i] = log(i + 1);
        RWVInt * temp = thisbrwk->performOneWalkByBits();
        accumulated += *temp;
        delete temp;
        yaxis[i] = log((double) accumulated.abs_sum() / thisbrwk->GetNumberRandomWalks());
        out << xaxis[i] << "--" << yaxis[i] << endl;
    }
    error = 0;

    gsl_fit_linear(xaxis, 1, yaxis, 1, thisbrwk->GetNumberRandomWalks(), &c0, &c1, &cov00, &cov01, &cov11, &chi_sqr);
    x->receiveData(xaxis, this->thisbrwk->GetNumberRandomWalks());
    y->receiveData(yaxis, this->thisbrwk->GetNumberRandomWalks());
    for (uint64_t i = 0; i < this->thisbrwk->GetNumberRandomWalks(); i++) {
        double curve = c1 * xaxis[i] + c0;
        error += pow(yaxis[i] - curve, 2);
    }
    b=c0;
    a=c1;
    SSE=error;
    // cout << a << "-" << b << "-" << cov00 << "-" << error << endl;
    //    delete [] xaxis;
    //    delete [] yaxis;
    out.close();
    //    delete [] w;
}

RWVSInt* ProbabilityBase::GetDatabinp(uint64_t nw, uint64_t ns, char* msg) {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    } else if (datap) {
        delete datap;
        datap = NULL;
    }
    this->thisbrwk->SetNumberOfWalks(nw);
    this->thisbrwk->SetWalkSize(ns);
    if (this->thisbrwk->canProduceSets()) {
        this->thisbrwk->prepareData();
        this->databinp = this->thisbrwk->performAllWalksByBits();
        return this->databinp;
    } else {
        msg = strdup("Arquivo selecionado não possui dados suficientes.");
    }

}

bool ProbabilityBase::FetchDataOnly(u_int64_t ws, u_int64_t ns, char* msg) {
    if (databinp) {
        delete databinp;
    } else if (datap) {
        delete datap;
    }
    this->thisbrwk->SetNumberOfWalks(ws);
    this->thisbrwk->SetWalkSize(ns);
    if (this->thisbrwk->canProduceSets()) {
        this->thisbrwk->prepareData();
        return true;
    } else {
        return false;
    }
}

DataSetInt* ProbabilityBase::GetDatap(uint64_t nw, uint64_t ns, char* msg) {
    if (datap) {
        delete datap;
        datap = NULL;
    } else if (databinp) {
        delete databinp;
        databinp = NULL;
    }
    this->thisbrwk->SetNumberOfWalks(nw);
    this->thisbrwk->SetWalkSize(ns);
    if (this->thisbrwk->canProduceSets()) {
        this->thisbrwk->prepareData();
        this->datap = this->thisbrwk->performAllWalksByPoints();
        return this->datap;
    } else {
        msg = strdup("Arquivo selecionado não possui dados suficientes.");
    }
}

void ProbabilityBase::clearDataBin() {
    if (databinp) {
        delete databinp;
        databinp = NULL;
    }
}

void ProbabilityBase::clearDataPoints() {
    if (datap) {
        delete datap;
        datap = NULL;
    }
}

RWVInt * ProbabilityBase::getWalkNByBits(u_int64_t N) {
    return thisbrwk->performWalkNByBits(N);
}

DataPointsInt * ProbabilityBase::getWalkNByPoints(u_int64_t N) {
    return thisbrwk->performWalkNByPoints(N);
}
RWVSInt* ProbabilityBase::getWalkNByBits(u_int64_t beg, u_int64_t end){
    RWVSInt * ret = new RWVSInt(end-beg+1);
    for(int i=beg;i<=end;i++){
        ret->put(getWalkNByBits(i));
    }
    return ret;
}
DataSetInt* ProbabilityBase::getWalkNByPoints(u_int64_t beg, u_int64_t end){
    assert(beg>end);
    DataSetInt * ret = new DataSetInt(end-beg+1);
    for(int i=beg;i<=end;i++){
        ret->put(getWalkNByPoints(i));
    }
    return ret;
}
