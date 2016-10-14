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
    
    /*call table[a].at(b), and would return -1 either when there
     is no such value or 'a' goes beyond the size of the vector*/
    int at(int, int) const;
    
    /*Tuples must be inserted by ascending order like 0,1,2,..., 
     otherwise, the program would run into an unexpected state */
    void insert(TripleTuple const &);
private:
    int rowCnt;
    int colCnt;
    int noneZeroCnt;
    std::vector<TripleTuple> table;
};

#endif /* TripleTable_H */
