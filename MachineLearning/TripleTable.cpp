//
//  TripleTable.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/12.
//  Copyright © 2016年 毛润泽. All rights reserved.
//


#include "TripleTable.h"

using std::vector;
using std::map;

TripleTable::TripleTable(){
    if(!table.empty())
        table.clear();
}

TripleTable::TripleTable(TripleTable const &other){
    *this = other;
}

TripleTable const &TripleTable::operator = (TripleTable const &other){
    table = other.table;
    return *this;
}

void TripleTable::insert(TripleTuple const &item){
    table.push_back(item);
}

void TripleTable::addAt(int pos, int key, int value){
    table[pos].addByValue(key, value);
}

int TripleTable::at(int a, int b) const {
    if(a >= table.size()){
        error(INDEX_BEYOND_VECTOR_SIZE);
        return -1;
    }
    else
        return table[a].at(b);
}

map<int,int> const &TripleTable::getContentAt(int pos) const {
    return table[pos].getContent();
}

void TripleTable::setWordCntAt(int pos, int cnt){
    table[pos].setWordCnt(cnt);
}

int TripleTable::getWordCntAt(int pos) const {
    return table[pos].getWordCnt();
}

void TripleTable::print() const {
    for(int i = 0; i < table.size(); ++i)
        table[i].print();
}

int TripleTable::size() const {
    return (int)table.size();
}

int TripleTable::sizeAt(int pos) const {
    return table[pos].size();
}

int TripleTable::countOfKeyAt(int pos, int key) const {
    return table[pos].countOfKey(key);
}