/* 
 * File:   GeneralFunctions.h
 * Author: fernando
 *
 * Created on 30 de Abril de 2013, 11:59
 */

#ifndef GENERALFUNCTIONS_H
#define	GENERALFUNCTIONS_H
#define BN(NrW,WS)(ceil((double)(WS)/8)*(NrW))
#include <gmpxx.h>
//#include <QColor>
//#include <QTime>
//#include <QtGlobal>
//QColor randomColor(unsigned long int seed);
double log2_temp(mpz_class  l);
struct Axis{
    Axis(double Lx1,double Hx1, double Ly1, double Hy1){
        x=Hx1-Lx1;
        Hx=Hx1;
        Lx=Lx1;
        y=Hy1-Ly1;
        Hy=Hy1;
        Ly=Ly1;
    }
    Axis(){
        x=0;
        Hx=0;
        Lx=0;
        y=0;
        Hy=0;
        Ly=0;
    }
    double x;
    double y;
    double Hy;
    double Ly;
    double Hx;
    double Lx;
    Axis & operator=(Axis & rhs);
    Axis & operator+=(Axis & rhs);
    
};
#endif	/* GENERALFUNCTIONS_H */

