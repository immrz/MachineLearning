//
//  TripleTuple.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/11.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef TripleTuple_h
#define TripleTuple_h

#include <map>

class TripleTuple{

public:
    explicit TripleTuple(int = 0);
    TripleTuple(TripleTuple const &);
    TripleTuple const &operator = (TripleTuple const &);
    
    /*judged only by order*/
    bool operator == (TripleTuple const &) const;
    
    /*insert pair<the order of the word, the times this word appears in this sentence>
     into tuple, and would return false if there is already such a pair in it*/
    bool insert(int, float);
    
    /*get the value given the key, and would return -1 if no such value exists*/
    int at(int) const;
    
    void setWordCnt(int);
    int getWordCnt() const;
    int getOrder() const;
private:
    int order;
    int wordCnt;
    std::map<int,int> tuple;
};

#endif /* TripleTuple_h */
