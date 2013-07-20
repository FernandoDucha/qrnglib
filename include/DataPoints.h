/* 
 * File:   DataPoints.h
 * Author: fernando
 *
 * Created on 24 de Abril de 2013, 14:52
 */

#ifndef DATAPOINTS_H
#define	DATAPOINTS_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "GeneralUsage.h"
#include "RandomWalkVector.h"
#include <limits.h>

using namespace std;
template <class type> class RandomWalkVector;
using namespace std;
template <class type> class DataPoints {
private:
    type * pointsArray;
    unsigned long int Npoints;
    unsigned long int actualPoint;
    type max,min;
public:
    DataPoints();
    void receiveData(type * data, long unsigned  int n);
    bool getNext(type &);
    type getElement(unsigned int pos);
    unsigned long int getNpoints() const;
    void resetIterator();
    virtual ~DataPoints();
    type getMin() const;
    type getMax() const;    
    void setNpoints(unsigned long int Npoints);
    DataPoints<type> & operator+=(  DataPoints<type> &);
    DataPoints<type> & operator=(  DataPoints<type> &);
    DataPoints<type> & operator+=(  RandomWalkVector<type> &);
    DataPoints<type> & operator=(  RandomWalkVector<type> &);
    
    type sum(){
        type ret=0;
        for(unsigned int i=0;i<Npoints;i++){
            ret+=pointsArray[i];
        }
        return ret;
    }
    unsigned long int getActualPoint();
    void print(){
        for(unsigned int i=0;i<Npoints;i++){
            cout<<pointsArray[i]<<":";
        }
        cout<<endl;
    }
};

template <class type> DataPoints<type> & operator+( DataPoints<type> & a,  DataPoints<type> & b){
    DataPoints<type> *ret = new DataPoints<type>();
    *ret+=a;
    *ret+=b;
    return *ret;
}
template <class type> bool operator==( DataPoints<type> & a,  DataPoints<type> & b){
    if(a.getNpoints()!=b.getNpoints()){
        return false;
    }else if((a.getMax()!=b.getMax())||(a.getMin()!=b.getMin())){
        return false;
    }else{
        for(unsigned int i=0;i<a.getNpoints();i++){
            if(a.getElement(i)!=b.getElement(i)){
                return false;
            }
        }
    }
    return true;
}
template <class type> bool operator!=( DataPoints<type> & a,  DataPoints<type> & b){
    return !(a==b);
}
template <class type> DataPoints<type>& DataPoints<type>::operator+=( DataPoints<type>& rhs){
    if(this->getNpoints()==rhs.getNpoints()){
        for(unsigned int i=0;i<rhs.getNpoints();i++){
            pointsArray[i]+=rhs.getElement(i);
            if(pointsArray[i]>max){
                max=pointsArray[i];
            }else if(pointsArray[i]<min){
                min=pointsArray[i];
            } 
        }
    }else if(this->pointsArray==NULL){
        this->pointsArray= new type[rhs.getNpoints()];
        for(unsigned int i=0;i<rhs.getNpoints();i++){
            pointsArray[i]=0;
            pointsArray[i]+=rhs.getElement(i);
            if(pointsArray[i]>max){
                max=pointsArray[i];
            }else if(pointsArray[i]<min){
                min=pointsArray[i];
            }            
        }
        Npoints=rhs.getNpoints();
    }else{
        fprintf(stderr,"ERRO: DataPoints precisam de ter a mesma dimensão - Npoint.");
    }
    return *this;
}
template <class type> DataPoints<type>& DataPoints<type>::operator=(  DataPoints<type>& rhs){
    if(this!=&rhs){
        if(this->pointsArray!=NULL){
            delete [] this->pointsArray;
            this->pointsArray= new type[rhs.getNpoints()];
        }else{
            this->pointsArray= new type[rhs.getNpoints()];
        }
        
        for(int i=0;i<rhs.getNpoints();i++){
            this->pointsArray[i]=rhs.getElement(i);
        }
        this->Npoints=rhs.getNpoints();
        min=rhs.getMin();
        max=rhs.getMax();
    }
    return *this;
}
template <class type> DataPoints<type>& DataPoints<type>::operator+=( RandomWalkVector<type>& rhs){
    if(this->getNpoints()==rhs.getSize()){
        for(unsigned int i=0;i<rhs.getSize();i++){
            pointsArray[i]+=rhs.getElement(i);
            if(pointsArray[i]>max){
                max=pointsArray[i];
            }else if(pointsArray[i]<min){
                min=pointsArray[i];
            }
        }
        max=rhs.GetMax();
        min=rhs.GetMin();
    }else if(this->pointsArray==NULL){
        this->pointsArray= new type[rhs.getSize()];
        for(unsigned int i=0;i<rhs.getSize();i++){
            pointsArray[i]=0;
            pointsArray[i]+=rhs.getElement(i);
            if(pointsArray[i]>max){
                max=pointsArray[i];
            }else if(pointsArray[i]<min){
                min=pointsArray[i];
            }            
        }
        Npoints=rhs.getSize();
    }else{
        fprintf(stderr,"ERRO: DataPoints precisam de ter a mesma dimensão - Npoint.");
    }
    return *this;
}
template <class type> DataPoints<type>& DataPoints<type>::operator=(  RandomWalkVector<type>& rhs){
    if(this->pointsArray!=NULL){
        delete [] this->pointsArray;
        this->pointsArray= new type[rhs.getSize()];
    }else{
        this->pointsArray= new type[rhs.getSize()];
    }

    for(unsigned int i=0;i<rhs.getSize();i++){
        this->pointsArray[i]=rhs.getElement(i);
    }
    this->Npoints=rhs.getSize();
    min=rhs.GetMin();
    max=rhs.GetMax();
    return *this;
}
template<class type> type DataPoints<type>::getElement(unsigned int pos){
    if(pos<this->Npoints){
        return pointsArray[pos];
    }else{
        cout<<"Erro: Requisição de elemento fora dos limites do vetor."<<endl;
        exit(1);
    }
}
template<class type> unsigned long int DataPoints<type>::getActualPoint(){
        return actualPoint;
}
template<class type> DataPoints<type>::DataPoints() {
    Npoints=0;
    this->pointsArray=NULL;
    actualPoint=0;
    max=0;
    min=0;
}
template<class type> DataPoints<type>::~DataPoints() {
        delete [] pointsArray;
}

template<class type> type DataPoints<type>::getMin() const {
    return min;
}

template<class type> type DataPoints<type>::getMax() const {
    return max;
}

template<class type> unsigned long int DataPoints<type>::getNpoints() const {
    return Npoints;
}

template <class type> void DataPoints<type>::setNpoints(unsigned long int Npoints) {
    this->Npoints = Npoints;
    pointsArray=new type[Npoints];
}
template<class type> void DataPoints<type>::receiveData(type* data, long unsigned int n)  {
    if(this->pointsArray!=NULL){
        delete [] pointsArray;
        pointsArray= new type[n];
    }else{
        pointsArray= new type[n];        
    }
    actualPoint=0;
    Npoints=n;
    min=INT_MAX;
    max=INT_MIN;
    for(unsigned long int i=0;i<n;i++){
        pointsArray[i]=data[i];
        //cout<<i<<" Valores: "<<data[i]<<"#-#"<<pointsArray[i]<<endl;
        if(data[i]>max){
            max=data[i];
        }
        if(data[i]<min){
            min=data[i];
        }
    }
//    delete [] data;
}
template<class type> bool DataPoints<type>::getNext(type& n){
    if(actualPoint<Npoints){
        n= pointsArray[actualPoint];
        actualPoint++;
        return true;
    }else{
        actualPoint=0;
        return false;
    }
}
template <class type >void DataPoints<type>::resetIterator(){
    actualPoint=0;
}
#endif	/* DATAPOINTS_H */

