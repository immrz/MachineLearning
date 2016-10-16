//
//  main.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/11.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

//#include <iostream>
#include "MLA.h"

using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    MLA *ptr;
    
    ptr = new NaiveBayesCMLA("train.txt", "test.txt");
    ptr->solve();
    delete ptr;
    
    ptr = new NaiveBayesRMLA("Dataset_train.csv", "Dataset_validation.csv", "Dataset_test.csv");
    ptr->solve();
    delete ptr;
    
    return 0;
}