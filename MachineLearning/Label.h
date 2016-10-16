//
//  Label.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/12.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef Label_H
#define Label_H

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include "Errors.h"
#define _LABEL_CNT 6

class LabelOfClassification{
public:
    LabelOfClassification();
    LabelOfClassification(LabelOfClassification const &);
    LabelOfClassification const &operator = (LabelOfClassification const &);
    int at(int) const;
    int size() const;
    
    void append(std::vector<int> const &);
private:
    std::vector<int> labels;
};

class FloatArray{
public:
    FloatArray(float const * const, int);
    FloatArray(FloatArray const &);
    FloatArray const &operator = (FloatArray const &);
    float at(int) const;
    float const * const getContent() const;
private:
    float content[_LABEL_CNT];
};

class LabelOfRegression{
public:
    LabelOfRegression();
    LabelOfRegression(LabelOfRegression const &);
    LabelOfRegression const &operator = (LabelOfRegression const &);
    
    float at(int, int) const;
    FloatArray const &getLabelsAt(int);
    float const * const getContentAt(int) const;
    void append(std::vector<FloatArray> const &);
private:
    std::vector<FloatArray> labels;
};
#endif /* Label_H */
