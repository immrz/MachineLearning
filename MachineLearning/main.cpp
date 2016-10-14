//
//  main.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/11.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#include <iostream>
#include "TripleTuple.h"

int main(int argc, const char * argv[]) {
    TripleTuple t;
    t.insert(1, 0);
    t.insert(2, 10.1);
    float a = t.at(2);
    float b = t.at(3);
    std::cout << a << " " << b << std::endl;
    return 0;
}
