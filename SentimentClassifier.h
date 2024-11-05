#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

class SentimentClassifier
{
    private:
        std::map<DSString, int> data;                   //tweet, tweet sentiment (# 4 or 0) 

    public:
        DSString id, tweet;              //DSStrings for the values in the csv
        int senti;                                   //sentiment value
        //reads in the values for the training file and testing file
        void readingIn(const char* trainFile, const char* testFile);
        std::vector<DSString> tokenTweets;              //trainFile tweet vector
        std::vector<int> sentiVect;                     //trainFile sentiment vector
        std::unordered_map<DSString, int, DSString::Hash> sentiMap;     //map for tweet ID (key) and sentiment value
        std::vector<DSString> tweetVect;                //testFile tweet vector
        std::vector<DSString> tweetIDs;                 //testFile ID vector
        
        void train();

        void test(const char* actualSenti, const char* results);                       //tests using the file without the sentiment
        std::vector<int> finalSentiment;                //output sentiment vector
        std::unordered_map<DSString, int, DSString::Hash> actualSentiments;

        void getResults(const char* resultsFile, const char* accuracyFile);//returns the results from all functions, create accuracy file with math
        
};
#endif
