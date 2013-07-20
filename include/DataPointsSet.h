/* 
 * File:   DataPointsSet.h
 * Author: fernando
 *
 * Created on 27 de Abril de 2013, 14:52
 */

#ifndef DATAPOINTSSET_H
#define	DATAPOINTSSET_H
#include <vector>
#include "DataPoints.h"
#include <stdio.h>
#include "GeneralUsage.h"
using namespace std;

template <class type> class DataPointsSet {
public:
    DataPointsSet(unsigned long int size);
    virtual ~DataPointsSet();
    void put(DataPoints<type> * a);
    DataPoints<type> * getNext();
    DataPoints<type> * getElement(unsigned long int p);
    unsigned long int getSize() const;
    void resetIterator();
    int getMin() const;
    int getMax() const;
private:
    DataPoints<type> ** list;
    unsigned long int size;
    unsigned long int pos,pos_temp;
    int max;
    int min;
};
template <class type> void DataPointsSet<type>::put(DataPoints<type> * a) {
    if(pos<size){
        list[pos] = a;
        if (a->getMax() > max) {
            max = a->getMax();
        }
        if (a->getMin() < min) {
            min = a->getMin();
        }
        pos++;
    }else{
        fprintf(stderr,"ERRO: Esse conjunto não suporta mais que %lu elementos.",size);
    }
}

template <class type> DataPointsSet<type>::DataPointsSet(unsigned long int size) {
    list = new DataPoints<type>*[size];
    for(unsigned int i=0;i<size;i++){
        list[i]=NULL;
    }
    this->size = size;
    pos_temp=pos = 0;
    max = min = 0;
}

template <class type> DataPointsSet<type>::~DataPointsSet() {
    for (unsigned int i = 0; i < size; i++) {
        if (list[i] != NULL) {
            delete list[i];
        }
    }
    delete [] list;
}
template <class type>DataPoints<type> * DataPointsSet<type>::getNext(){
    if(pos_temp<=pos){
        int p=pos_temp;
        pos_temp++;
        return list[p];        
    }else{
        pos_temp=0;
        return NULL;                
    }
}
template <class type>DataPoints<type> * DataPointsSet<type>::getElement(unsigned long int p){
    if(p<size){
        return list[p];
    }else{
        return NULL;
    }
}
template <class type>unsigned long int DataPointsSet<type>::getSize() const{
    return size;
}
template <class type> void DataPointsSet<type>::resetIterator(){
    pos_temp=0;
}

template <class type> int DataPointsSet<type>::getMin() const {
    return min;
}

template <class type>int DataPointsSet<type>::getMax() const {
    return max;
}
#endif	/* DATAPOINTSSET_H */

