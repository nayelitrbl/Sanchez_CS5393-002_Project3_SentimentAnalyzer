#include <iostream>
#include <vector>
#include <algorithm>
 
#include "DSString.h"
#include "SentimentClassifier.h"
 
int main(int argc, char** argv)
{  
    //run with: ./sentiment ./data/train_dataset_20.csv ./data/test_dataset_20.csv ./data/test_dataset_sentiment_20.csv ./results.csv ./accuracy.txt
    std::cout << "I will be a sentiment analyzer!" << std::endl;
    SentimentClassifier classifier;
    classifier.readingIn(argv[1], argv[2]);
    classifier.train();
    classifier.test(argv[3]);
    classifier.getResults(argv[4], argv[5]);
 
   return 0;
}
