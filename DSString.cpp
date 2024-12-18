#include "DSString.h"
#include <cstring>
#include <stdexcept>
#include <functional>
 
/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings don't store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  
//data is a pointer to a character array that contains the string with a \0 terminator
 
DSString::DSString() : data{nullptr}{
    data = new char[1];//creates data as an array of characters with len of 1
    data[0] = '\0';    //since data is null the first element will be the terminator symbol
    len = 0;
}
 
DSString::DSString(const char *c){
    if(c == nullptr || *c == '\0'){     //if data is emptry 
        data = new char[1];             //creates data as an array of characters with len of 1
        data[0] = '\0';                 //assigns first element as terminator symbol since it is nullptr
        len = 0;
    }
    else{
        len = 0;
        while(c[len] != '\0'){
            len++;
        }
        data = new char[len + 1];
        for(size_t i = 0; i < len; i++){ //loops through c
            data[i] = c[i];             //takes element at i of c and copies it into data array 
        }
        data[len] = '\0';
    }
 
}
 
DSString::DSString(const DSString &rhs){
    len = rhs.len;
    data = new char[len + 1];
    for(size_t i = 0; i < len; i++){ //loops through c
        data[i] = rhs[i];             //takes element at i of c and copies it into data array 
    }
    data[len] = '\0';
}
 
DSString::~DSString(){
    delete[] data;     //deallocates memory pointed to by data pointer, whole length gets deleted
}
 
 
size_t DSString::length() const{
    return len;  //getter returns length
}
 
char &DSString::operator[](size_t ind){
    return data[ind]; //returns reference to a character at index
}
 

char &DSString::operator[](size_t ind) const{
    if(ind >= this->length()){
        throw out_of_range("Index out of bounds");
    }
    return data[ind];  //returns reference to a character at index (const)
}
 
 
/**
     * s1 = s2;
     * 1.check if s1 is s2, then do nothing if it is
     * 2.allocate memory again, big enough to store s2
     * 3.delete s1 from memory
     * 4.copy to new memory, assign pointer to s1 data
     * 5.fix len for s1
    */
DSString &DSString::operator=(const DSString &rhs) {
  if (this != &rhs) {              //check if data is equal to rhs, do nothing if it is
    delete[] data;
    len = rhs.len;
    data = new char[len + 1];
    for(size_t i = 0; i < len; i++){//loops through c
        data[i] = rhs[i];           //takes element at i of c and copies it into data array 
    }
    data[len] = '\0';
  }
  return *this;
}
 
/**
     * appends the string to this string
     * 1.create a new string with the length of both combined + 1 (for terminator)
     * 2.loop through both strings to append char at the indeces to the new string
     * 3.return the new string
    */
DSString DSString::operator+(const DSString &rhs) const{
    size_t newLen = len + rhs.len;
    char* together = new char[newLen+1];               //created with the length of both combined + 1 (terminator)
    for(size_t ind = 0; ind < len; ind++){             //loop through data 
        together[ind] = data[ind];                     //add data to the first part of together
    }
    for(size_t rhsInd = 0; rhsInd < rhs.len; rhsInd++){//loop through rhs
        together[rhsInd + len] = rhs[rhsInd];          //add rhs to the second part of together (index rhsInd(0) + length of rhs insert the string)
    }
    together[newLen] = '\0';                           //terminator at end
    DSString concStr(together);                        //create a DSString with the new concatenated string
    delete[] together;                                 //deallocate memory for together
    return concStr;                                    // return new DSString
}
 
/**
 * if original string is equal to new string return true else return false
 * 1.loop through the first string
 * 2.if theres a char that does not match with the right hand side, return false and end loop
 * 3.if all values match, return true
*/
bool DSString::operator==(const DSString &rhs) const{
    if(len != rhs.len){             //if the lens don't match up it is automatically false as a string cannot be equals to another if the lengths are not the same
        return false;
    }
    for(size_t i = 0; i < len; i++){//loop through the string
        if(data[i] != rhs[i]){      //if theres a char in any of the strings that don't match up, return false
            return false;
        }
    }
    return true;                    //else, all characters match in the string, so return true
 
}
 
 
/**
 * checks if string is less than new string 
 * 1.loops through strings using min in case one is longer than the other
 * 2.if original string is greater than, automatically return true
 * 3.if the original is less than the new, return true
*/
bool DSString::operator<(const DSString &rhs) const{
    for(size_t i = 0; i < std::min(len, rhs.len); i++){//loop through the strings
        if(data[i] > rhs[i]){                          //false if data is greater than the rhs at index i 
            return false;
        }
        if(data[i] < rhs[i]){                          //true if data is less than rhs at index i 
            return true;
        }
    }
    return len < rhs.len;
}

/**
 * gets new string (substring) from string
 * 1.create a new string that will hold the substring with the len numChars+1 (terminator)
 * 2.loop through original string and get indeces until numChars
 * 3.at the start of substring add the characters at the index start and after until numChars is reached
 * 4.return the new string which is now a substring from the original string 
*/
DSString DSString::substring(size_t start, size_t numChars) const{   //change for loop to simple vers.
    if(start >= len || (start + numChars) > len){
        throw out_of_range("Index is out of bounds");
    }

    char* ss = new char[numChars+1]; 
    for(size_t i = 0; i < numChars; i++){//loops for the amount of chars in ss
        ss[i] = data[i+start];           //at index i, copy in data at index i + start 
    }
    ss[numChars] = '\0';                //at the end of ss (given by numChars) add the terminator
    DSString subString(ss);             //creates a DSString with the substring from the original string
    delete[] ss;                        //deallocates memory for ss
    return subString;                   //returns DSString subString
}
 
/**
     * to ascii -> take dec. and +32 to get lowercase from upper case if >=65 and <=90
     * A - Z : 65 - 90    (diff of 32 for lowercase letters)
     * 1.create new string for lower case string with len+1 (terminator)
     * 2.loop through original string, enter if loop
     * 3.if the ascii number is greater than or equal to 65 or less than or equal to 90 add 32 to get new ascii number  if(ascii >= 65 || ascii <= 90)
     * 4.else the same ascii number will be used (account for special characters - not letters)
     * 5.at index i of the new string, add the character based on result of if loop
     * 6. return the new string 
    */
DSString DSString::toLower() const{ // look at the ASCII table for this
   char* lower = new char[len+1];   //create new string which will be in lower case
   for(size_t i = 0; i < len; i++){ //loop through the original string
        char c = data[i];           //set c to the char at the index
        if(c >= 'A' && c <= 'Z'){   //if ascii value shows that it is A - Z (uppercase)
            lower[i] = c + 32;      //add 32 to ascii value to make it lower case
        }
        else{
            lower[i] = c;           //returns the same char if it is not uppercase
        }
   }
   lower[len] = '\0';               //set end to terminator
   DSString lowerCase(lower);       //create DSString with lowercase characters
   delete[] lower;                  //deallocates memory for lower
   return lowerCase;                //returns DSString lowerCase
} 
 
char* DSString::c_str() const{
    return data;        //returns pointer
}

bool DSString::empty() const {
    return this->length() == 0;
}
 
 
/**
     * overloading insertion operator, how the string will be printed with ostream
    */
std::ostream &operator<<(std::ostream &os, const DSString &str) {
    os << str.data; //str in ostream os, for loop ?
    return os;      //returns the ostream 
}
 
/**
 * Tokenize function:
 * add the DSString to a vector. Make sure the special chars are removed to 
 * make the words the only thing in the vector. Use toLower to make all the 
 * words the same and not get duplicate words.
*/
std::vector<DSString> DSString::tokenize(DSString str){
    std::vector<DSString> token;                //creates a vector of DSStrings
    char* cstr = new char[str.length() + 1];    //allocate c-style string
    strcpy(cstr, str.c_str());                  //copy DSString to c-string
    
    const char* delim = " ,.!?;:\"'()[]{}<>-";  //define delimiters
    char* word = strtok(cstr, delim);           //get first token

    while(word != nullptr){                     //loop through all tokens
        DSString dsWord = word;                 //convert c-string token to DSString
        dsWord = dsWord.toLower();              //convert to lowercase
        token.push_back(dsWord);                //add to vector
        word = strtok(nullptr, delim);          //get next token
    }
    
    delete[] cstr;
    return token;                               //returns the vector made up of the words
}
 
 
/**
 * getline function: 
 * takes in a line into istream in using DSStrings
 * reference: https://www.programiz.com/cpp-programming/buffer 
*/
std::istream& getline(std::istream &in, DSString &str){
    char *b = new char[10000];  //buffer with a size of 10000
    in.getline(b, 10000);       //gets the line 
    str = DSString(b);          //sets the DSString to the line read
    delete[] b;                 //deallocates memory
    return in;                  //returns istream in
}
 
 
/**
 * getline function (3 parameters): 
 * takes in a line into istream in using DSStrings and accounting for delimiter
 * reference: https://www.programiz.com/cpp-programming/buffer 
*/
std::istream& getline(std::istream &in, DSString &str, char delimiter){
    char *b = new char[10000];              //buffer with a size of 10000
    if(in.getline(b, 10000, delimiter)){    //gets the line if the until the delimiter is found
        str = DSString(b);                  //sets the DSString to the chars up to the delimiter
    }      
    delete[] b;                             //deallocates memory
    return in;                              //returns istream in
}

/**
 * Hash function for map with DSString
*/
std::size_t DSString::Hash::operator()(const DSString& s) const{
    std::size_t hashVal = 0; 
    for(size_t i = 0; i < s.length(); i++){
        hashVal = hashVal * 31 + s[i];
    }
    return hashVal;
}
