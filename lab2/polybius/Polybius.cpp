//
// Created by Ania Wójcik on 15.03.2018.
//

#include <string>
#include "Polybius.h"

std::string CheckIfInKey(char tab[5][5], char letter){
    std::string crypted;
    for(int j = 0; j< 5; ++j) {
        for (int k = 0; k < 5; ++k) {
            if (letter == tab[j][k] || letter == tab[j][k] + 32) {
                crypted += std::to_string(j + 1);
                crypted += std::to_string(k + 1);
                return crypted;
            }
        }
    }
    return "";
}

std::string PolybiusCrypt(std::string message){
    char PolybiusSquare2[5][5] = {
            {'A', 'B', 'C', 'D', 'E'},
            {'F', 'G', 'H', 'I', 'K'},
            {'L', 'M', 'N', 'O', 'P'},
            {'Q', 'R', 'S', 'T', 'U'},
            {'V', 'W', 'X', 'Y', 'Z'},
    };

    std::string crypted;
    for (char i : message) {
        if (i=='J' || i== 'j') {
            crypted += "24";
        }
        else {
            crypted += CheckIfInKey(PolybiusSquare2, i);
        }
    }
    return crypted;
}

std::string PolybiusDecrypt(std::string crypted){
    char PolybiusSquare2[5][5] = {
            {'A', 'B', 'C', 'D', 'E'},
            {'F', 'G', 'H', 'I', 'K'},
            {'L', 'M', 'N', 'O', 'P'},
            {'Q', 'R', 'S', 'T', 'U'},
            {'V', 'W', 'X', 'Y', 'Z'},
    };
    std::string decrypted;
    int x,y;
    for(int i = 0; i < crypted.length(); i+=2){
        x =((int) crypted[i])-1-'0';
        y =((int) crypted[i+1]) -'0'-1;
          decrypted += (PolybiusSquare2[x][y]+32);
        }
    return decrypted;
}

