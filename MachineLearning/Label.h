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
    LabelOfClassification const &operator = (std::vector<int> const &);
    int at(int) const;
private:
    std::vector<int> labels;
};

class floatArray{
public:
    floatArray(float const * const, int);
    float at(int) const;
private:
    float content[_LABEL_CNT];
};

class LabelOfRegression{
public:
    LabelOfRegression();
    LabelOfRegression(LabelOfRegression const &);
    LabelOfRegression const &operator = (LabelOfRegression const &);
    float at(int, int) const;
private:
    std::vector<floatArray> labels;
};
#endif /* Label_H */
