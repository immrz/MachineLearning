//
//  Errors.h
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/14.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#ifndef Errors_h
#define Errors_h

#include <iostream>

void error(char const * const p){
    printf("%s\n", p);
    exit(1);
}

char INDEX_BEYOND_VECTOR_SIZE[] = "vector index is beyond size!\n";
char INDEX_BEYOND_ARRAY_SIZE[] = "array index is beyond size!\n";
char ARRAY_SIZE_NOT_MATCH[] = "The number of float labels doesn't match!\n";
char SUCH_HINT_NOT_ALLOWED[] = "There doesn't exist such a hint!\n";
char NO_SUCH_FILE[] = "Sorry!No such file.\n";

#endif /* Errors_h */
