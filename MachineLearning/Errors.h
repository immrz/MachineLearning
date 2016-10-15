//
//  Errors.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/14.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef Errors_H
#define Errors_H

#include <iostream>

#define error Errors::printError

#define INDEX_BEYOND_VECTOR_SIZE "vector index is beyond size!\n"
#define INDEX_BEYOND_ARRAY_SIZE "array index is beyond size!\n"
#define ARRAY_SIZE_NOT_MATCH "The number of float labels doesn't match!\n"
#define SUCH_HINT_NOT_ALLOWED "There doesn't exist such a hint!\n"
#define NO_SUCH_FILE "Sorry!No such file.\n"
#define NO_SUCH_VALUE_IN_MAP "Sorry!This map doesn't contain the value given this key!\n"
#define WRONG_LABEL "Sorry!Such a label doesn't exist.\n"

class Errors{
public:
    static void printError(char const * const s){
        printf("Program crashes because of error:\n%s", s);
        exit(1);
    }
};

#endif /* Errors_H */