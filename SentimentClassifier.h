#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"
#include <iostream>
#include <vector>
#include <map>

class SentimentClassifier
{
    private:
        std::map<DSString, int> data;           //tweet, tweet sentiment (# 4 or 0) 

    public:
        DSString id, date, q, user, tweet;      //DSStrings for the values in the csv
        size_t senti;                           //sentiment value

        void readingIn(const char* trainFile, const char* testFile);
        void train();
        void test(char* results);               //tests using the file without the sentiment
        void getResults(char* answFile, char* accuracy);     //returns the results from all functions, create accuracy file with math
};
#endif
