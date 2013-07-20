/* 
 * File:   RandomWalkMatrix.h
 * Author: fernando
 *
 * Created on 30 de Abril de 2013, 09:35
 */

#ifndef RANDOMWALKMATRIX_H
#define	RANDOMWALKMATRIX_H
#include "RandomWalkVector.h"
#include <stdio.h>
#include <stdlib.h>
template <class type>class RandomWalkVecSet {
public:
    RandomWalkVecSet(unsigned long int s);
    virtual ~RandomWalkVecSet();
    void put(RandomWalkVector<type> * a);
    RandomWalkVector<type> * getNext();
    RandomWalkVector<type> * getElement(unsigned long int p);
    unsigned long int getSize() const;
    void resetIterator();
private:
    RandomWalkVector<type>** list;
    unsigned long int size;
    unsigned long int pos,pos_temp;
};

template <class type>RandomWalkVecSet<type>::RandomWalkVecSet(unsigned long int s) {
    size=s;
    list = new RandomWalkVector<type> *[s];
    
    pos_temp=pos=0;
}
template <class type> void RandomWalkVecSet<type>::put(RandomWalkVector<type> * a){
    if(pos<size){
        list[pos]=a;
        pos++;
    }else{
        fprintf(stderr,"ERRO: Esse conjunto não pode possuir mais que %lu elementos.",size);
    }
    
}
template <class type>RandomWalkVecSet<type>::~RandomWalkVecSet() {
    for(unsigned int i=0;i<size;i++){
        RandomWalkVector<type> * a= list[i];        
        delete a;
    }
    delete list;
}
template <class type> RandomWalkVector<type> * RandomWalkVecSet<type>::getNext(){
    if(pos_temp<=pos){
        int p=pos_temp;
        pos_temp++;
        return list[p];        
    }else{
        pos_temp=0;
        return NULL;                
    }
}
template <class type> RandomWalkVector<type> * RandomWalkVecSet<type>::getElement(unsigned long int p){
    if(p<=size){
        return list[p];
    }else{
        return NULL;
    }
}
template <class type> unsigned long int RandomWalkVecSet<type>::getSize() const{
    return size;
}
template <class type> void RandomWalkVecSet<type>::resetIterator(){
    pos_temp=0;
}
#endif	/* RANDOMWALKMATRIX_H */

