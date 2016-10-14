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

/*#define error(s) \
    printf("%s\n",s);\
    exit(1)*/

#define error Errors::printError
#define INDEX_BEYOND_VECTOR_SIZE "vector index is beyond size!\n"
#define INDEX_BEYOND_ARRAY_SIZE "array index is beyond size!\n"
#define ARRAY_SIZE_NOT_MATCH "The number of float labels doesn't match!\n"
#define SUCH_HINT_NOT_ALLOWED "There doesn't exist such a hint!\n"
#define NO_SUCH_FILE "Sorry!No such file.\n"

class Errors{
public:
    static void printError(char const * const s){
        printf("%s", s);
        exit(0);
    }
};

#endif /* Errors_H */
