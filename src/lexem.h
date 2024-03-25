#include <string>

#ifndef COMPILATEUR_LEXEM_H
#define COMPILATEUR_LEXEM_H

using namespace std;

class Lexem {
public:
    string kind;
    string value;
    int position[2];

    Lexem(string kind, string value, int (&position)[2]) {
        this->kind = kind;
        this->value = value;
        for (int k = 0; k < 2; k++) {
            this->position[k] = position[k];
        }
    }
};


#endif //COMPILATEUR_LEXEM_H
