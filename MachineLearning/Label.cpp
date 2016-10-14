//
//  Label.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/12.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#include "Label.h"

/*Constructor of class LabelOfClassification*/
LabelOfClassification::LabelOfClassification(){
    if(!labels.empty())
        labels.clear();
}

LabelOfClassification::LabelOfClassification(LabelOfClassification const &a){
    *this = a;
}

LabelOfClassification const &LabelOfClassification::operator=(LabelOfClassification const &a){
    labels = a.labels;
    return *this;
}

int LabelOfClassification::at(int pos) const {
    if(pos >= labels.size()){
        error(INDEX_BEYOND_VECTOR_SIZE);
        return -1;
    }
    else
        return labels[pos];
}

/*Constructor of class floatArray*/
floatArray::floatArray(float const * const p, int n){
    if(p == NULL){
        memset(content, 0, sizeof(content));
        return;
    }
    else if(n != _LABEL_CNT)
        error(ARRAY_SIZE_NOT_MATCH);
    else
        memcpy(content, p, sizeof(content));
}

float floatArray::at(int pos) const {
    if(pos >= _LABEL_CNT){
        error(INDEX_BEYOND_ARRAY_SIZE);
        return -1;
    }
    else
        return content[pos];
}

/*Constructor of class LabelOfRegression*/
LabelOfRegression::LabelOfRegression(){
    if(!labels.empty()){
        labels.clear();
    }
}

LabelOfRegression::LabelOfRegression(LabelOfRegression const &a){
    *this = a;
}

LabelOfRegression const &LabelOfRegression::operator = (LabelOfRegression const &a){
    labels = a.labels;
    return *this;
}

float LabelOfRegression::at(int a, int b) const {
    if(a >= labels.size()){
        error(INDEX_BEYOND_VECTOR_SIZE);
        return -1;
    }
    else
        return labels[a].at(b);
}
