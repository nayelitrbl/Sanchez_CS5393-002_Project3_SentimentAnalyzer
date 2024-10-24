#include "DSString.h"

/* 
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project. 
 *
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable. 
 * DDO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */  
//data is a pointer to a character array that contains the string with a \0 terminator
 
DSString::DSString() : data{nullptr}{
    data = new char[1];//creates data as an array of characters with len of 1
    data[0] = '\0';    //since data is null the first element will be the terminator symbol
    len = 0;
}

DSString::DSString(const char *c){
    if(c == nullptr){      //if data is emptry 
        data = new char[1];//creates data as an array of characters with len of 1
        data[0] = '\0';    //assigns first element as terminator symbol since it is nullptr
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
