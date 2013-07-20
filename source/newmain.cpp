/* 
 * File:   newmain.cpp
 * Author: fordem
 *
 * Created on July 18, 2013, 3:30 AM
 */

#include <cstdlib>
#include <iostream>
#include "FileRawBuffer.h"
#include "RandomNumberGenerator.h"
#include "GeneralUsage.h"
#include "Cronometro.h"
#include <limits>
#include <gmpxx.h>
using namespace std;
//#define invert(number)()

/*
 * 
 */
uint8_t mask[] = {0x81, 0x42, 0x24, 0x18};
unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}
int main(int argc, char** argv) {
    FileRawBuffer frb("/media/DATA0/qrngdata", pow(2, 30));
    RandomNumberGenerator rng(&frb);
    mpf_class sum=0;
    for (int i = 0; i < 10000; i++) {
        sum+=rng.getNumber(2000);
    }
    cout<<sum/10000<<"--"<<endl;
    return 0;
}

