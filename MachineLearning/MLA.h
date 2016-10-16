//
//  MLA.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/13.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef MLA_H
#define MLA_H

#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <cmath>
#include "TripleTable.h"

#define HINT_TRAIN 0
#define HINT_TEST 1
#define HINT_VALI 2
#define MAXN 200

typedef char const * const ccc;
typedef LabelOfClassification LOC;
typedef LabelOfRegression LOR;

/*short for Machine Learning Algorithm*/
class MLA{
public:
    MLA();
    virtual ~MLA() {};
    void printTrainTable() const;
    int getTrainSize() const;
    int getTestSize() const;
    
    virtual void solve() const = 0;
    virtual void readFromFile(int, FILE *) = 0;
    
protected:
    int trainSize;
    int testSize;
    int valiSize;
    int trainWordBagSize;
    TripleTable train;
    TripleTable test;
    TripleTable vali;
    std::map<std::string, int> wordBag;
};

/*short for Classfication-MLA*/
class CMLA : public MLA {
public:
    CMLA(ccc, ccc);
    virtual ~CMLA() {};
    virtual void readFromFile(int, FILE *); //the int parameter is to indicate which Table to initial
    virtual void solve() const = 0;

    int getLabelAt(int, int) const; //the first parameter is a hint
private:
    LOC label;
};

/*short for Regression-MLA*/
class RMLA : public MLA{
public:
    RMLA(ccc, ccc, ccc);
    virtual ~RMLA() {} ;
    virtual void readFromFile(int, FILE *); //the int parameter is to indicate which Table to initial
    virtual void solve() const = 0;
    
    int getLabelAt(int, int) const; //the two parameters are both positions
    float const * const getLabelContentAt(int) const;
private:
    LOR label;
};

class NaiveBayesCMLA : public CMLA {
public:
    NaiveBayesCMLA(ccc, ccc);
    virtual ~NaiveBayesCMLA() {};
    virtual void solve() const;
private:
    TripleTable reform;    //transform the 'train' table to simplify the calculation
    int prior[_LABEL_CNT]; //prior probilities
};

class NaiveBayesRMLA : public RMLA {
public:
    NaiveBayesRMLA(ccc, ccc, ccc);
    virtual ~NaiveBayesRMLA() {};
    virtual void solve() const;
};

#endif /* MLA_H */