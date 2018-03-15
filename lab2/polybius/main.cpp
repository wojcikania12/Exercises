//
// Created by Ania Wójcik on 15.03.2018.
//
#include <iostream>
#include <fstream>
#include "Polybius.h"

using namespace std;

int main(int argc, char *argv[]) {

    fstream file, file2;
    file.open(argv[1], ios::in);
    file2.open(argv[2], ios::out);
    string word;
    if (argc > 4) {
        cout << "Za duzo argumentow." << endl;
    }

    if (!file.good()) {
        cout << "Plik nie istnieje." << endl;
    }
    if (*argv[4] == '1') {
        while (file >> word) {
            file2 << PolybiusCrypt(word) << " ";
        }
    } else if (*argv[4] == '0') {
        while (file >> word) {
            file2 << PolybiusDecrypt(word) << " ";
        }
    }
    file.close();
    file2.close();
    return 0;
}
