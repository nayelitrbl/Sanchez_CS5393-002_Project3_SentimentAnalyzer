#include "SentimentClassifier.h"
#include "DSString.h"
#include <iostream>
#include <iomanip> 

void SentimentClassifier::readingIn(const char* trainFile, const char* testFile) {
    std::ifstream in(trainFile);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open training file: " << trainFile << std::endl;
        return;
    }

    const char delimiter = ',';
    DSString line;
    getline(in, line); // Skip header

    while (getline(in, line)) {
        DSString temp;
        if (!getline(in, temp, delimiter)) continue;
        senti = atoi(temp.c_str());
        sentiVect.push_back(senti);

        if (!getline(in, temp, delimiter)) continue;
        id = temp;
        sentiMap[id] = senti;

        for (int i = 0; i < 3; i++) {
            if (!getline(in, temp, delimiter)) break; // Skip columns
        }

        if (getline(in, temp)) {
            DSString tweet = temp.toLower();
            if (!tweet.empty()) {
                tokenTweets.push_back(tweet);
            }
        } else {
            std::cerr << "Warning: Empty tweet detected and skipped." << std::endl;
        }
    }
    in.close();

    in.open(testFile);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open test file: " << testFile << std::endl;
        return;
    }

    getline(in, line); // Skip header
    while (getline(in, line)) {
        DSString temp;
        if (!getline(in, temp, delimiter)) continue;
        id = temp;
        tweetIDs.push_back(id);

        for (int i = 0; i < 3; i++) {
            if (!getline(in, temp, delimiter)) break;
        }

        if (getline(in, temp)) {
            tweet = temp.toLower();
            tweetVect.push_back(tweet);
        }
    }
    in.close();
}

void SentimentClassifier::train() {
    //map of the words is called data
    if (tokenTweets.empty() || sentiVect.empty()) {
        std::cerr << "Error: No tweets or sentiments to train on." << std::endl;
        return;
    }

    for (size_t strIndex = 0; strIndex < tokenTweets.size(); strIndex++) { // loop through the size of the training file tweet vector
        DSString tweet = tokenTweets.at(strIndex); // create a DSString that stores the DSString at the given index from the training file tweet vector
        auto tokenizedTweets = tweet.tokenize(tweet); // tokenizes the tweet 

        if(!tokenizedTweets.empty()){
            for (size_t mapIndex = 0; mapIndex < tokenizedTweets.size(); mapIndex++) { // introduces new index to insert into the data map
            DSString word = tokenizedTweets.at(mapIndex); // get tokenized word
            auto it = data.find(word); // create an iterator that checks the value at the selected index
            if (it != data.end()) { // checks if the word is currently in the map
                if (strIndex < sentiVect.size() && sentiVect.at(strIndex) == 4) { // Check the size before accessing
                    data.at(word)++;
                } else if (strIndex < sentiVect.size()) { // Check again for negative sentiment
                    data.at(word)--;
                }
            } else { // if the tweet isn't in the map then it will add it with the corresponding value for its sentiment
                if (strIndex < sentiVect.size()) {
                    data.insert(std::pair<DSString, int>(word, (sentiVect.at(strIndex) == 4) ? 1 : -1));
                }
            }
        }
        }else{
            std::cerr << "Warning: No tokens found for tweet at index " << strIndex << std::endl;
        }
    }
}

void SentimentClassifier::test(const char* actualSenti, const char* results) {
    // The file with the classifications for the testing tweet data
    std::ifstream actualFile(actualSenti);
    if (!actualFile.is_open()) {
        std::cerr << "Error: Could not open actual sentiment file: " << actualSenti << std::endl;
        return;
    }

    DSString line, temp;
    getline(actualFile, line); // Read and ignore header

    while (getline(actualFile, line)) {
        getline(actualFile, temp, ',');
        int sentimentInt = atoi(temp.c_str());
        getline(actualFile, temp, ',');
        DSString tweetID = temp;

        actualSentiments[tweetID] = sentimentInt;
    }
    actualFile.close();

    // Predict & store in output
    std::ofstream fout(results); // output file 
    if (!fout.is_open()) {
        std::cerr << "Error: Could not open results file: " << results << std::endl;
        return;
    }

    for (size_t strIndex = 0; strIndex < tweetVect.size(); strIndex++) { // loops through the testing file's tweet vector
        int totalPts = 0; // total sentiment value 

        DSString tweet = tweetVect.at(strIndex); // create a DSString that stores the DSString at the given index
        auto tweetV = tweet.tokenize(tweet); // tokenizes the tweet

        if(!tweetV.empty()){
            for (size_t mapIndex = 0; mapIndex < tweetV.size(); mapIndex++) { // loops through new vector
                auto it = data.find(tweetV.at(mapIndex)); // create an iterator that checks the value at the selected index
                if (it != data.end()) { // checks if the word is in the map
                    totalPts += it->second; // if it is, add the total sentiment value to the variable
                }
                }
                int prediction = totalPts > 0 ? 4 : 0;
                finalSentiment.push_back(prediction); // add the final value (0 or 4) for the sentiment to display on the output file  

                if (strIndex < tweetIDs.size()) {
                    fout << prediction << ',' << tweetIDs.at(strIndex) << '\n';
                } else {
                    std::cerr << "Warning: tweetIDs vector is shorter than tweetVect. Index: " << strIndex << std::endl;
                }
        }else{
            std::cerr << "Warning: No tokens found for testing tweet at index " << strIndex << std::endl;
        }
    }
    fout.close(); // closes the output file
}

// Evaluate function
void SentimentClassifier::getResults(const char* resultsFile, const char* accuracyFile) {
    std::ifstream results(resultsFile);
    if (!results.is_open()) {
        std::cerr << "Error: Could not open results file: " << resultsFile << std::endl;
        return;
    }

    size_t correct = 0;
    size_t total = 0;
    DSString line;

    std::ofstream out(accuracyFile);
    if (!out.is_open()) {
        std::cerr << "Error: Could not open accuracy file: " << accuracyFile << std::endl;
        return;
    }

    while (getline(results, line)) {
        DSString temp;
        getline(results, temp, ','); // get the tweet id 
        int prediction = atoi(temp.c_str()); // get the predicted sentiment

        getline(results, temp); // get the tweet ID
        DSString tweetID = temp;

        if (actualSentiments.find(tweetID) != actualSentiments.end()) {
            int actual = actualSentiments[tweetID];
            if (prediction == actual) {
                correct++;
            } else {
                out << prediction << ',' << actual << ',' << tweetID << '\n';
            }
            total++;
        }
    }

    if (total > 0) {
        double accResult = (static_cast<double>(correct) / total) * 100;
        out << "Accuracy: " << std::fixed << std::setprecision(3) << accResult << "%" << std::endl;
    } else {
        std::cerr << "Warning: No valid predictions to evaluate." << std::endl;
    }

    results.close();
    out.close();
}
