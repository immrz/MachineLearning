//
//  MLA.cpp
//  MachineLearning
//
//  Created by 毛润泽 on 16/10/13.
//  Copyright © 2016年 毛润泽. All rights reserved.
//

#include "MLA.h"
#define SMALL_N 20
#define LAPLACE
//#define NO_LAPLACE
#define DEVIA 0.001

using std::string;
using std::map;
using std::pair;
using std::vector;

char const * const delim = " \t\r\n,";

MLA::MLA() : train(), test(), vali(), trainSize(0), testSize(0), valiSize(0), trainWordBagSize(0) {
    if(!wordBag.empty()){
        wordBag.clear();
    }
}

void MLA::printTrainTable() const {
    train.print();
}

int MLA::getTrainSize() const {
    return trainSize;
}

int MLA::getTestSize() const {
    return testSize;
}

CMLA::CMLA(ccc fTrain, ccc fTest) : MLA() {
    label = LOC();
    FILE *f1 = fopen(fTrain, "r");
    FILE *f2 = fopen(fTest, "r");
    readFromFile(HINT_TRAIN, f1);
    readFromFile(HINT_TEST, f2);
    fclose(f1);
    fclose(f2);
    trainSize = train.size();
    testSize = test.size();
}

/*variables that you may be confused with:
 wordOrder : the order of the word according to its appearance in the files
 wordCnt : the number of words that the sentence contain*/
void CMLA::readFromFile(int hint, FILE *fr){
    int stcOrder = 0, wordOrder = (int)wordBag.size();
    TripleTable *whichTable;
    map<string,int>::iterator findWordIter;
    vector<int> storeLabel;
    
    if(hint == HINT_TRAIN)
        whichTable = &train;
    else if(hint == HINT_TEST)
        whichTable = &test;
    else{
        error(SUCH_HINT_NOT_ALLOWED);
        
        /*return is needed or the compiler would think 'whichTable' is uninitialized,
         although calling 'error' function has stopped the program actually*/
        return;
    }
    
    if(fr == NULL){
        error(NO_SUCH_FILE);
    }
    
    char stc[MAXN];
    fgets(stc, MAXN, fr); //the first line of the given files is useless
    while(fgets(stc, MAXN, fr) != NULL){
        int j, len, label, wordCnt = 0, spaceCnt = 0;
        if((len = (int)strlen(stc)) < 1){
            break; //end reading
        }
        
        //read the label of this sentence
        for(j = 0; stc[j]; ++j){
            if(stc[j] == delim[0] || stc[j] == delim[1]){
                if(++spaceCnt == 1)
                    break;
            }
        }
        sscanf((char*)stc + j + 1, "%d", &label);
        if(!(label >= 1 && label <= _LABEL_CNT))
            error(WRONG_LABEL);
        storeLabel.push_back(label);
        
        //locate to the start of the real sentence
        for(j = j + 1; stc[j]; ++j){
            if(stc[j] == delim[0] || stc[j] == delim[1]){
                if(++spaceCnt == 3)
                    break;
            }
        }
        
        //read the words one by one in this sentence
        TripleTuple newTuple(stcOrder++);
        char *ptr, str[SMALL_N];
        for(ptr = strtok(stc + j + 1, delim); ptr != NULL; ++wordCnt){
            sscanf(ptr, "%s", str);
            ptr = strtok(NULL, delim);
            
            string word(str);
            findWordIter = wordBag.find(word);
            
            int tupleKey;

            if(findWordIter == wordBag.end()){          //the word needs a corresponding key
                wordBag.insert(pair<string,int>(word, wordOrder));
                tupleKey = wordOrder++;
            }
            else                                        //the word has got a corresponding key
                tupleKey = findWordIter->second;
            
            newTuple.addByOne(tupleKey);
        }
        
        newTuple.setWordCnt(wordCnt);
        whichTable->insert(newTuple);
    }
    
    if(hint == HINT_TRAIN)
        trainWordBagSize = wordOrder;
    label.append(storeLabel);
}

int CMLA::getLabelAt(int hint, int pos) const {
    if(hint == HINT_TRAIN)
        return label.at(pos);
    else
        return label.at(pos + trainSize);
}

NaiveBayesCMLA::NaiveBayesCMLA(ccc fTrain, ccc fTest) : CMLA(fTrain, fTest) {
    reform = TripleTable();
    memset(prior, 0, sizeof(prior));
    
    for(int i = 1; i <= _LABEL_CNT; ++i){
        reform.insert(TripleTuple(i));
    }
    
    int wordCnt[_LABEL_CNT];
    memset(wordCnt, 0, sizeof(wordCnt));
    
    for(int i = 0; i < trainSize; ++i){
        map<int,int> content = train.getContentAt(i);
        map<int,int>::iterator it;
        int pos = getLabelAt(HINT_TRAIN, i) - 1;
        
        prior[pos]++;
        
        for(it = content.begin(); it != content.end(); it++){
            reform.addAt(pos, it->first, it->second);
            wordCnt[pos] += it->second;
        }
    }
    
    for(int i = 0; i < _LABEL_CNT; i++){
        reform.setWordCntAt(i, wordCnt[i]);
    }
}

void NaiveBayesCMLA::solve() const {
    FILE *fw = fopen("/Users/Mr.z/Desktop/result.txt", "w");
    if(fw == NULL)
        error(NO_SUCH_FILE);
    
    int correct = 0;
    int wordCnt[_LABEL_CNT], nonRepeat[_LABEL_CNT];
    
    for(int i = 0; i < _LABEL_CNT; ++i){
        wordCnt[i] = reform.getWordCntAt(i);
        nonRepeat[i] = reform.sizeAt(i);
        //printf("%d %d\n", wordCnt[i], nonRepeat[i]);
    }
    
    for(int i = 0; i < testSize; i++){
        map<int,int> content = test.getContentAt(i);
        map<int,int>::const_iterator it;
        float maxP = -1;
        int goalLabel = -1;
        for(int j = 0; j < _LABEL_CNT; ++j){
            float p = 1;
            for(it = content.begin(); it != content.end(); it++){
                
                /*if the word didn't appear in the train text, ignore it*/
                if(it->first >= trainWordBagSize)
                    continue;
                
                float frequency;
#ifdef LAPLACE
                frequency = (1.0 * reform.at(j, it->first) + 1) / (wordCnt[j] + nonRepeat[j]);
#endif
#ifdef NO_LAPLACE
                frequency = 1.0 * reform.at(j, it->first) / wordCnt[j];
#endif
                if(it->second >= 2)
                    frequency = pow(frequency, it->second);
                p = p * frequency;
            }
            
            p = p * (float)prior[j];
            if(maxP < p){
                maxP = p;
                goalLabel = j + 1; //'+1' is important
            }
        }
        
        fprintf(fw, "%d\n", goalLabel);
        
        if(goalLabel == getLabelAt(HINT_TEST, i))
            correct++;
    }
    
    fclose(fw);
    printf("The accuracy of Naive-Bayes for classification is %.3lf\n", 1.0 * correct / testSize);
}



RMLA::RMLA(ccc fTrain, ccc fVali, ccc fTest) : MLA() {
    label = LOR();
    FILE *f1 = fopen(fTrain, "r");
    FILE *f2 = fopen(fVali, "r");
    FILE *f3 = fopen(fTest, "r");
    readFromFile(HINT_TRAIN, f1);
    readFromFile(HINT_VALI, f2);
    readFromFile(HINT_TEST, f3);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    trainSize = train.size();
    valiSize = vali.size();
    testSize = test.size();
}

void RMLA::readFromFile(int hint, FILE *fr){
    int stcOrder = 0, wordOrder = (int)wordBag.size();
    TripleTable *whichTable;
    map<string,int>::iterator findWordIter;
    vector<FloatArray> storeLabel;
    
    switch(hint){
        case HINT_TRAIN:
            whichTable = &train; break;
        case HINT_VALI:
            whichTable = &vali; break;
        case HINT_TEST:
            whichTable = &test; break;
        default:
            error(SUCH_HINT_NOT_ALLOWED); return; break;
    }
    
    if(fr == NULL){
        error(NO_SUCH_FILE);
    }
    
    char stc[MAXN];
    fgets(stc, MAXN, fr); //the first line of the given files is useless
    while(fgets(stc, MAXN, fr) != NULL){
        int i, j, len, wordCnt = 0, commaCnt = 0;
        float label[_LABEL_CNT];
        if((len = (int)strlen(stc)) < 1){
            break; //end reading
        }
        
        //locate the start of the sentence and labels, respectively
        for(i = 6, j = 0; stc[j]; ++j){
            if(stc[j] == ','){
                ++commaCnt;
                if(commaCnt == 1)
                    i = j;
                else if(commaCnt == 2)
                    break;
            }
        }
        stc[j] = '\0';
        char *ptr;
        
        //only train text gives the labels
        if(hint == HINT_TRAIN){
            for(ptr = strtok(stc + j + 1, delim), j = 0; ptr != NULL; j++){
                sscanf(ptr, "%f", &label[j]);
                ptr = strtok(NULL, delim);
                if(j >= _LABEL_CNT)
                    error(ARRAY_SIZE_NOT_MATCH);
            }
            if(j != _LABEL_CNT)
                error(ARRAY_SIZE_NOT_MATCH);
            storeLabel.push_back(FloatArray(label, _LABEL_CNT));
        }
        
        //read the words one by one in this sentence
        TripleTuple newTuple(stcOrder++);
        char str[SMALL_N];
        for(ptr = strtok(stc + i + 1, delim); ptr != NULL; ++wordCnt){
            sscanf(ptr, "%s", str);
            ptr = strtok(NULL, delim);
            
            string word(str);
            findWordIter = wordBag.find(word);
            
            int tupleKey;
            
            if(findWordIter == wordBag.end()){          //the word needs a corresponding key
                wordBag.insert(pair<string,int>(word, wordOrder));
                tupleKey = wordOrder++;
            }
            else                                        //the word has got a corresponding key
                tupleKey = findWordIter->second;
            
            newTuple.addByOne(tupleKey);
        }
        
        newTuple.setWordCnt(wordCnt);
        whichTable->insert(newTuple);
    }
    
    if(hint == HINT_TRAIN){
        trainWordBagSize = wordOrder;
        label.append(storeLabel);
    }
}

int RMLA::getLabelAt(int a, int b) const {
    return label.at(a, b);
}

float const * const RMLA::getLabelContentAt(int pos) const {
    return label.getContentAt(pos);
}

NaiveBayesRMLA::NaiveBayesRMLA(ccc fTrain, ccc fVali, ccc fTest) : RMLA(fTrain, fVali, fTest) {}

void NaiveBayesRMLA::solve() const {
    FILE *fw;
    int whichSize;
    TripleTable const *whichTable;
    
    for(int m = 0; m < 2; m++){
        if(m == 0){
            fw = fopen("/Users/Mr.z/Desktop/valiRegression.csv", "w");
            whichSize = valiSize;
            whichTable = &vali;
        }
        else{
            fw = fopen("/Users/Mr.z/Desktop/testRegression.csv", "w");
            whichSize = testSize;
            whichTable = &test;
        }
        if(fw == NULL)
            error(NO_SUCH_FILE);
        
        float trainLabel[trainSize][_LABEL_CNT];
        for(int i = 0; i < trainSize; ++i)
            memcpy(trainLabel[i], getLabelContentAt(i), sizeof(trainLabel[i]));
        
        int wordCnt[trainSize];
        for(int i = 0; i < trainSize; ++i)
            wordCnt[i] = train.getWordCntAt(i);
        
        for(int i = 0; i < whichSize; ++i){
            map<int,int> content = whichTable->getContentAt(i);
            map<int,int>::const_iterator it;
            float goalLabel[_LABEL_CNT];
            memset(goalLabel, 0, sizeof(goalLabel));
            
            for(int j = 0; j < trainSize; ++j){
                float res = 1;
                for(it = content.begin(); it != content.end(); ++it){
                    if(it->first >= trainWordBagSize)
                        continue;
                    
                    float frequency = (1.0 * train.at(j, it->first) + DEVIA) /
                                        (trainWordBagSize * DEVIA + (float)wordCnt[j]);
                    res = res * frequency;
                }
                for(int k = 0; k < _LABEL_CNT; ++k){
                    goalLabel[k] += res * trainLabel[j][k];
                }
            }
            float sumLabel = 0;
            for(int j = 0; j < _LABEL_CNT; ++j)
                sumLabel += goalLabel[j];
            for(int j = 0; j < _LABEL_CNT; ++j)
                goalLabel[j] /= sumLabel;
            for(int j = 0; j < _LABEL_CNT - 1; ++j)
                fprintf(fw, "%.6f,", goalLabel[j]);
            fprintf(fw, "%.6f\n", goalLabel[_LABEL_CNT - 1]);
        }
    }
}