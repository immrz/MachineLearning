//
//  TripleTuple.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/11.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#include "TripleTuple.h"

using std::map;
using std::pair;

TripleTuple::TripleTuple(int a){
    order = a;
    wordCnt = 0;
    if(!tuple.empty())
        tuple.clear();
}

TripleTuple::TripleTuple(TripleTuple const &other){
    *this = other;
}

TripleTuple const &TripleTuple::operator = (TripleTuple const &other){
    order = other.order;
    wordCnt = other.wordCnt;
    tuple = other.tuple;
    return *this;
}

bool TripleTuple::operator == (TripleTuple const &other) const {
    if(order == other.order)
        return true;
    return false;
}

bool TripleTuple::insert(int key, int value){
    pair<map<int,int>::iterator,bool> p = tuple.insert(pair<int,int>(key,value));
    return p.second;
}

int TripleTuple::at(int key) const {
    map<int,int>::const_iterator it = tuple.find(key);
    if(it != tuple.end())
        return it->second;
    else
        return NOT_FOUND;
}

void TripleTuple::setWordCnt(int a){
    wordCnt = a;
}

int TripleTuple::getWordCnt() const {
    return wordCnt;
}

int TripleTuple::getOrder() const {
    return order;
}

int TripleTuple::countOfKey(int key) const {
    return (int)tuple.count(key);
}

void TripleTuple::addByOne(int key){
    map<int,int>::iterator it = tuple.find(key);
    if(it == tuple.end()){
        tuple.insert(pair<int,int>(key, 1));
    }
    else
        it->second ++;
}

void TripleTuple::addByValue(int key, int value){
    map<int,int>::iterator it = tuple.find(key);
    if(it == tuple.end()){
        tuple.insert(pair<int,int>(key, value));
    }
    else
        it->second += value;
}

map<int,int> const &TripleTuple::getContent() const {
    return tuple;
}

void TripleTuple::print() const {
    printf("%d : ",order);
    map<int,int>::const_iterator it;
    for(it = tuple.begin(); it != tuple.end(); ++it){
        printf("(%d, %d) ", it->first, it->second);
    }
    printf("\n\n");
}

int TripleTuple::size() const {
    return (int)tuple.size();
}