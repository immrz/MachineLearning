//
//  MLA.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/13.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#include "MLA.h"
#define SMALL_N 20

using std::string;
using std::map;
using std::pair;

char const * const delim = " \t";

MLA::MLA() : train(), test(), vali() {
    if(!wordBag.empty()){
        wordBag.clear();
    }
}

CMLA::CMLA(ccc fTrain, ccc fTest) : MLA() {
    label = LOC();
    FILE *f1 = fopen(fTrain, "r");
    FILE *f2 = fopen(fTest, "r");
    readFromFile(INIT_TRAIN, f1);
    readFromFile(INIT_TEST, f2);
    fclose(f1);
    fclose(f2);
}

void CMLA::readFromFile(int hint, FILE *fr){
    int stcOrder = 0, wordOrder = 0;
    map<string,int>::iterator findWord;
    TripleTable *ptr;
    
    if(hint == INIT_TRAIN)
        ptr = &train;
    else if(hint == INIT_TEST)
        ptr = &test;
    else
        error(SUCH_HINT_NOT_ALLOWED);
    
    char stc[MAXN];
    while(fgets(stc, MAXN, fr) != NULL){
        if(fr == NULL)
            error(NO_SUCH_FILE);
        int j, len, label, wordCnt = 0, spaceCnt = 0;
        if((len = (int)strlen(stc)) >= 1){
            if(stc[len - 1] == '\n')
                stc[len - 1] = '\0';
        }
        else
            break;
        
        //read the label of this sentence
        for(j = 0; stc[j]; ++j){
            if(stc[j] == delim[0] || stc[j] == delim[1]){
                if(++spaceCnt == 1)
                    break;
            }
        }
        sscanf((char*)stc + j + 1, "%d", &label);
        
        //locate to the start of the real sentence
        for(j = j + 1; stc[j]; ++j){
            if(stc[j] == delim[0] || stc[j] == delim[1]){
                if(++spaceCnt == 3)
                    break;
            }
        }
        
        //read the words one by one in this sentence
        TripleTuple newTuple(stcOrder);
        char *ptr, str[SMALL_N];
        for(ptr = strtok(stc + j + 1, delim); ptr != NULL; ++wordCnt){
            sscanf(ptr, "%s", str);
            ptr = strtok(NULL, delim);
            
            string word(ptr);
            findWord = wordBag.find(ptr);
            if(findWord == wordBag.end()){
                wordBag.insert(pair<string,int>(word, wordOrder++));
            }
        }
        newTuple.setWordCnt(wordCnt);
    }
}