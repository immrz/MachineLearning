//
//  TripleTuple.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/11.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef TripleTuple_H
#define TripleTuple_H

#include <map>
#include "Errors.h"
#define NOT_FOUND 0

class TripleTuple{

public:
    explicit TripleTuple(int = 0);
    TripleTuple(TripleTuple const &);
    TripleTuple const &operator = (TripleTuple const &);
    
    /*judged only by order*/
    bool operator == (TripleTuple const &) const;
    
    /*insert pair<the order of the word, the times this word appears in this sentence>
     into tuple, and would return false if there is already such a pair in it*/
    bool insert(int, int);
    
    /*get the value given the key, and would return 'NOT_FOUND' if no such value exists*/
    int at(int) const;
    
    void setWordCnt(int);
    int getWordCnt() const;
    int getOrder() const;
    int countOfKey(int) const;
    
    /*Increase the value by 1 at the given key. If not exist, insert 1 as the value.*/
    void addByOne(int);
    
    void addByValue(int, int);
    
    std::map<int,int> const &getContent() const;
    void print() const;
    int size() const;
private:
    int order; //an order to specify this tuple
    int wordCnt; //equals to the sum of all the values in the map
    std::map<int,int> tuple;
};

#endif /* TripleTuple_H */
