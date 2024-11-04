#include <iostream>
#include <vector>
#include <algorithm>
 
#include "DSString.h"
#include "SentimentClassifier.h"
 
int main(int argc, char** argv)
{  
    /**
     * Your program should take 5 command line arguments in this order:
        training data set filename - the file with the training tweets
        testing data set filename - tweets that your program will classify
        testing data set sentiment filename - the file with the classifications for the testing tweet data
        classifier results file name - see Output Files section below
        classifier accuracy and errors file name - see Output Files section below
    */
    //run with: ./sentiment ./data/train_dataset_20k.csv ./data/test_dataset_10k.csv ./data/test_dataset_sentiment_10k.csv ./results.csv ./accuracy.txt
    std::cout << "I will be a sentiment analyzer!" << std::endl;
    SentimentClassifier classifier;
    classifier.readingIn(argv[1], argv[2]);
    classifier.train();
    classifier.test(argv[3], argv[4]);
    classifier.getResults(argv[4], argv[5]);
 
   return 0;
}
