//
// Created by Ania Wójcik on 08.03.2018.
//
#include <iostream>
#include "Palindrome.h"

using namespace std;

int main() {
    int option;
    string str;
    cout << "Wybierz opcje i wpisz numer" << endl;
    cout << "1. Sprawdz palindrom" << endl << "2. Wyjscie" << endl;
    cin >> option;
    if(option == 1){
        cout << "Podaj wyraz" << endl;
        cin >> str;
        bool palindrome = is_palindrome(str);
        if(palindrome == true){
            cout << "To jest palindrom" << endl;
        }
        else cout << "To nie jest palindrom" << endl;

    }
    else if(option == 2){
        return 0;
    }
    else cout << "Nie ma takiej opcji." << endl;


    return 0;
}
