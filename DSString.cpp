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
