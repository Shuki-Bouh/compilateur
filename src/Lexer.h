#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "lexem.h"

using namespace std;

#ifndef COMPILATEUR_LEXER_H
#define COMPILATEUR_LEXER_H


class Lexer {
public:
    vector<Lexem> lexems;

    void run(char * file);
    int parse_file(ifstream * stream);
    string find_type(string * value);
    int create_lexem(string * value, int (&position)[2]);


private:

    const unordered_map<string, string> regex = {
            {"main", "kw_main"},
            {"int", "kw_int"},
            {"float", "kw_float"},
            {"char", "kw_char"},
            {"bool", "kw_bool"},
            {"if", "kw_if"},
            {"else", "kw_else"},
            {"while", "kw_while"},
            {"(", "kw_lparenthese"},
            {")", "kw_rparenthese"},
            {"{", "kw_lcurbrac"},
            {"}", "kw_rcurbrac"},
            {"[", "kw_lcrochet"},
            {"]", "kw_rcrochet"},
            {"||", "kw_or"},
            {"&&", "kw_and"},
            {"=", "kw_assign"},
            {"==", "kw_equal"},
            {"!=", "kw_diff"},
            {"<", "kw_inf"},
            {"<=", "kw_inf_or_equal"},
            {">", "kw_sup"},
            {">=", "kw_sup"},
            {"+", "kw_add"},
            {"-", "kw_withdraw"},
            {"*", "kw_mul"},
            {"/", "kw_div"},
            {"%", "kw_mod"},
            {"!", "kw_non"},
            {":", "kw_semicol"}

    };
};





#endif //COMPILATEUR_LEXER_H
