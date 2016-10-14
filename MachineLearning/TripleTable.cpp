//
//  TripleTable.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/12.
//  Copyright © 2016年 毛润泽. All rights reserved.
//


#include "TripleTable.h"

using std::vector;

TripleTable::TripleTable(){
    rowCnt = 0;
    colCnt = 0;
    noneZeroCnt = 0;
    if(!table.empty())
        table.clear();
}

TripleTable::TripleTable(TripleTable const &other){
    *this = other;
}

TripleTable const &TripleTable::operator = (TripleTable const &other){
    rowCnt = other.rowCnt;
    colCnt = other.colCnt;
    noneZeroCnt = other.noneZeroCnt;
    table = other.table;
    return *this;
}

void TripleTable::insert(TripleTuple const &item){
    table.push_back(item);
}

int TripleTable::at(int a, int b) const {
    if(a >= table.size()){
        error(INDEX_BEYOND_VECTOR_SIZE);
        return -1;
    }
    else
        return table[a].at(b);
}