#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"
#include <iostream>
#include <vector>
#include <map>

class SentimentClassifier
{
    private:
        std::map<DSString, int> data;                   //tweet, tweet sentiment (# 4 or 0) 

    public:
        DSString id, date, q, user, tweet;              //DSStrings for the values in the csv
        size_t senti;                                   //sentiment value
        //reads in the values for the training file and testing file
        void readingIn(const char* trainFile, const char* testFile);
        std::vector<DSString> tokenTweets;              //trainFile tweet vector
        std::vector<int> sentiVect;                     //trainFile sentiment vector
        std::unordered_map<DSString, int> sentiMap;     //map for tweet ID (key) and sentiment value
        std::vector<DSString> tweetVect;                //testFile tweet vector
        std::vector<DSString> tweetIDs;                 //testFile ID vector
        
        void train();

        void test(char* results);                       //tests using the file without the sentiment
        std::vector<int> finalSentiment;                //output sentiment vector
        
        void getResults(char* answFile, char* accuracy);//returns the results from all functions, create accuracy file with math
};
#endif
