//
// Created by Ania Wójcik on 09.03.2018.
//

#include "DoubleBasePalindromes.h"
#include <iostream>


std::string to_binary(int decimal){
    int r=0, binary[1000000];
    std::string str_binary;
    while(decimal>0){
        binary[r]= decimal%2;
        decimal /=2;
        r++;
    }
    for(int j= r-1; j>=0; j--){
        str_binary+= std::to_string(binary[j]);
    }
    return str_binary;

    }


bool is_palindrome(std::string str){
    std::string reversed;
    for(int i = 1; i <= str.length() ; i++){
        reversed = reversed + str[str.length()- i] ;
    }
    if(str == reversed) return true;
    else return false;
}

uint64_t DoubleBasePalindromes(int max_vaule_exculsive){
    int binary, sum=0;
    std::string str_binary, str_decimal, reversed_str_binary, reversed_str_decimal;
    for(int decimal =0; decimal<= max_vaule_exculsive; decimal++) {
        str_binary = to_binary(decimal);
        str_decimal = std::to_string(decimal);
        if(is_palindrome(str_decimal) == true ){
            if(is_palindrome(str_binary) == true){
                sum += decimal;
            }
        }

    }
    return sum;

}