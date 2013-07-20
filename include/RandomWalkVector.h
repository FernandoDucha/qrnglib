/* 
 * File:   RandomWalkVector.h
 * Author: fernando
 *
 * Created on 29 de Abril de 2013, 17:36
 */

#ifndef RANDOMWALKVECTOR_H
#define	RANDOMWALKVECTOR_H
#include <stdlib.h>
#include <iostream>
#include "GeneralUsage.h"
using namespace std;
template <class type> class DataPoints;
template <class type> class RandomWalkVector {
public:
    RandomWalkVector();
    void TransformDataPoints(DataPoints<type>* input);
    void receiveData(type * input , unsigned long int s);
    bool getNext(type & a);
    void resetIterator();
    type getElement(unsigned int i);
    virtual ~RandomWalkVector();
    unsigned long int getSize();
    long unsigned int abs_sum(){
        unsigned int sum=0;
        for(unsigned int i=0;i<size;i++){
            sum+=abs(vec[i]);
        }
        return sum;
    }
    long int sum(){
        int sum=0;
        for(unsigned int i=0;i<size;i++){
            sum+=vec[i];
        }
        return sum;
    }
    RandomWalkVector<type> & operator=(RandomWalkVector<type>&);
    RandomWalkVector<type> &operator+=(RandomWalkVector<type>&);
    RandomWalkVector<type> & operator-=(RandomWalkVector<type>&);
    bool operator==(RandomWalkVector<type>&);
    bool operator!=(RandomWalkVector<type>&);
    type GetMax() const;
    type GetMin() const;
private:
    type * vec;
    unsigned long int size;
    unsigned long int acualPoint;
    type min,max;
};
template <class type> RandomWalkVector<type> & operator-(RandomWalkVector<type>& lop,RandomWalkVector<type>&rop){
     if(lop.getSize()==rop.getSize()){
        RandomWalkVector<type> * ret = new RandomWalkVector<type>();
        type * vec = new type[rop.getSize()];
        type a,b;
        rop.resetIterator();
        lop.resetIterator();
        unsigned long int it=0;
        while(rop.getNext(a)&&lop.getNext(b)){
            vec[it]=a-b;
            it++;
        }
        ret->receiveData(vec,rop.getSize());
        return *ret;
    }else{
        fprintf(stderr,"ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}
template <class type>bool RandomWalkVector<type>::operator==(RandomWalkVector<type>&rop){
    if(size!=rop.getSize()){
        return false;
    }else{
        rop.resetIterator();
        int count=0;
        type a;
        while(rop.getNext(a)){
            if(vec[count]!=a){
                return false;
            }
            count++;
        }
        return true;
    }
}
template <class type> bool RandomWalkVector<type>::operator!=(RandomWalkVector<type>&rop){
    return !(*this==rop);
}

template <class type> type RandomWalkVector<type>::GetMax() const {
    return max;
}

template <class type> type RandomWalkVector<type>::GetMin() const {
    return min;
}
template <class type> RandomWalkVector<type>&operator+(RandomWalkVector<type>& lop,RandomWalkVector<type>& rop){
    if(lop.getSize()==rop.getSize()){
        RandomWalkVector<type> * ret = new RandomWalkVector<type>();
        type * vec = new type[rop.getSize()];
        type a,b;
        rop.resetIterator();
        lop.resetIterator();
        unsigned long int it=0;
        while(rop.getNext(a)&&lop.getNext(b)){
            vec[it]=a+b;
            it++;
        }
        ret->receiveData(vec,rop.getSize());
        return *ret;
    }else{
        fprintf(stderr,"ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
}
template <class type >RandomWalkVector<type> &RandomWalkVector<type>::operator+=(RandomWalkVector<type>&rhs){
    if(this->getSize()==rhs.getSize()){
        int tmax=0,tmin=0;
        for(unsigned int i=0;i<rhs.getSize();i++){
            vec[i]+=rhs.getElement(i);
            if(vec[i]>tmax){
                tmax=vec[i];
            }else if(vec[i]<tmin){
                tmin=vec[i];
            } 
        }
        max=tmax;
        min=tmin;
    }else if(this->vec==NULL){
        this->vec= new type[rhs.getSize()];
        int tmax=0,tmin=0;
        for(unsigned int i=0;i<rhs.getSize();i++){
            vec[i]=0;
            vec[i]+=rhs.getElement(i);
            if(vec[i]>tmax){
                tmax=vec[i];
            }else if(vec[i]<tmin){
                tmin=vec[i];
            } 
        }
        max=tmax;
        min=tmin;
        size=rhs.getSize();
    }else{
        fprintf(stderr,"ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
    return *this;
}
template <class type >RandomWalkVector<type> &RandomWalkVector<type>::operator-=(RandomWalkVector<type>&rhs){
    if(this->getSize()==rhs.getSize()){
        int tmax=0,tmin=0;
        for(unsigned int i=0;i<rhs.getSize();i++){
            vec[i]-=rhs.getElement(i);
            if(vec[i]>tmax){
                tmax=vec[i];
            }else if(vec[i]<tmin){
                tmin=vec[i];
            } 
        }
        max=tmax;
        min=tmin;
    }else if(this->vec==NULL){
        this->vec= new type[rhs.getSize()];
        int tmax=0,tmin=0;
        for(unsigned int i=0;i<rhs.getSize();i++){
            vec[i]=0;
            vec[i]-=rhs.getElement(i);
            if(vec[i]>tmax){
                tmax=vec[i];
            }else if(vec[i]<tmin){
                tmin=vec[i];
            }           
        }
        max=tmax;
        min=tmin;
        size=rhs.getSize();
    }else{
        fprintf(stderr,"ERRO: Os dois vetores precisam ter o a mesma dimensão  - Size");
        exit(0);
    }
    return *this;
}
template <class type> RandomWalkVector<type> &  RandomWalkVector<type>::operator=(RandomWalkVector<type>& rhs){
    if(vec==NULL){
        vec = new type[rhs.getSize()];
    }else{
        delete [] vec;
        vec = new type[rhs.getSize()];
    }
    size=rhs.getSize();
    min=rhs.GetMin();
    max=rhs.GetMax();
    rhs.resetIterator();
    type a;
    while(rhs.getNext(a)){
        vec[acualPoint]=a;
        acualPoint++;
    }
    return *this;
}
template <class type> unsigned long int RandomWalkVector<type>::getSize(){
    return size;
}
template <class type> RandomWalkVector<type>::RandomWalkVector() {
    vec = NULL;
    size=0;
    acualPoint=0;
    max=0;min=0;
}
template <class type> RandomWalkVector<type>::~RandomWalkVector() {
    delete vec;
}
template <class type> void RandomWalkVector<type>::receiveData(type* input, unsigned long int s){
    if(vec==NULL){
        vec = new type[s];
    }else{
        delete [] vec;
        vec = new type[s];
    }
    size=s;
    for(unsigned int i=0;i<size;i++){
        vec[i]=input[i];
        if(vec[i]>max){
            max=vec[i];
        }else if(vec[i]<min){
            min=vec[i];
        }
    }
}
template <class type> void RandomWalkVector<type>::resetIterator(){
    this->acualPoint=0;
}
template <class type> bool RandomWalkVector<type>::getNext(type & a){
    if(acualPoint<size){
        a=vec[acualPoint];
        acualPoint++;
        return true;
    }else{
        return false;
    }
}
template <class type> void RandomWalkVector<type>::TransformDataPoints(DataPoints<type>* input){
    if(vec==NULL){
        delete [] vec;
    }
    size=input->getNpoints();
    vec = new unsigned long int[input->getNpoints()];
    vec[0]=input->getElement(0);
    for(unsigned int i=1;i<input->getNpoints();i++){
        if(input->getElement(i)>input->getElement(i-1)){
            vec[i]=1;
        }else{
            vec[i]=-1;
        }
        if(vec[i]>max){
            max=vec[i];
        }else if(vec[i]<min){
            min=vec[i];
        }
    }

//    cout<<input->getElement(input->getNpoints()-1)<<endl;
}
template <class type> type RandomWalkVector<type>::getElement(unsigned int i){
    if(i<this->size){
        return vec[i];
    }else{
        cout<<"Erro: Requisição de elemento fora dos limites do vetor."<<endl;
        exit(1);
    }
}
#endif	/* RANDOMWALKVECTOR_H */

