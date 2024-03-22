//
// Created by cyril on 28/02/2024.
//

#ifndef COMPILATEUR_LEXEM_H
#define COMPILATEUR_LEXEM_H


class Lexem {
public:
    char * kind;
    char * valeur;
    int position[2];

    Lexem(char * kind, char * valeur, int (&position)[2]) {
        this->kind = kind;
        this->valeur = valeur;
        for (int k = 0; k < 2; k++) {
            this->position[k] = position[k];
        }
    }
};


#endif //COMPILATEUR_LEXEM_H
