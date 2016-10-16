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
//    NaiveBayesCMLA nb("train.txt", "test.txt");
//    cout << "succeed!\n";
//    nb.solve();
    NaiveBayesRMLA nb("Dataset_train.csv", "Dataset_validation.csv", "Dataset_test.csv");
    cout << "succeed!\n";
    nb.printTrainTable();
    return 0;
}