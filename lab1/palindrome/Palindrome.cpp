//
// Created by Ania Wójcik on 08.03.2018.
//

#include "Palindrome.h"



bool is_palindrome(std::string str){
    int length = str.size();
    std::string reversed;
    for(int i = 1; i <= length ; i++){
        reversed = reversed + str[length- i] ;
    }
    if(str == reversed) return true;
    else return false;

}