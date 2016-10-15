//
//  TripleTable.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/11.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef TripleTable_H
#define TripleTable_H

#include <vector>
#include <cstdio>
#include <iostream>
#include "TripleTuple.h"
#include "Label.h"

class TripleTable{
    
public:
    TripleTable();                                      //default constructor
    TripleTable(TripleTable const &);                   //copy constructor
    TripleTable const &operator = (TripleTable const &);//overload the asignment operator
    
    /*call table[a].at(b), and would return 'NOT_FOUND' when there is not
     such a value, and would kill program if 'a' exceeds vector size*/
    int at(int, int) const;
    
    /*Tuples must be inserted by ascending order like 0,1,2,..., 
     otherwise, the program would run into an unexpected state */
    void insert(TripleTuple const &);
    
    /*insert a <int,int> pair into the specified tuple*/
    void addAt(int, int, int);
    
    std::map<int,int> const &getContentAt(int) const;
    
    void setWordCntAt(int, int);
    int getWordCntAt(int) const;
    
    void print() const;
    int size() const;
    int sizeAt(int) const;
    int countOfKeyAt(int, int) const;
private:
    std::vector<TripleTuple> table;
};

#endif /* TripleTable_H */
