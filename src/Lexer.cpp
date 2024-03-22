#include "Lexer.h"
#include <sstream>

using namespace std;

void Lexer::run(char * file) {
    ifstream stream(file);
    int out = 0;
    if (stream) {
        cout << "Fichier ouvert" << endl;
        out = this->parse_file(&stream);
    } else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        exit(1);
    }

    if (out != 0) {
        exit(2);
    }
}

int Lexer::create_lexem(string * value, int (&position)[2]) {
    int statut = 0;
    if (*value != "") {
        string kind = "";//this->find_type(value);
        Lexem lex(kind, *value, position);
        this->lexems.push_back(lex);
    }
    else {
        statut = 1;
    }
    return statut;
}

int Lexer::parse_file(ifstream * stream) {
    // Indices du parcours du fichier

    int row_position = 0;
    string row;
    int col_position;

    bool is_str = false; // celui-ci sert à savoir si on est encore dans une chaîne de caractère

    istringstream row_stream;

    // Valeurs des lexems
    char * valeur;
    char * kind;
    int position[2];

    // Liste temporaire du lexem en cours

    string temp;

    while (getline(*stream, row)) {
        col_position = 0;
        auto col = row.begin();
        while (col < row.end()) {
            string col_str(1, *col);
            cout << temp << endl;
            auto itt_expr = this->regex.find(temp);
            auto itt_col = this->regex.find(col_str);
            if (col_str == "\"" || is_str) {
                // Todo : avancer jusqu'au prochiain "
                if (col_str == "\"") {
                    is_str = 1 - is_str;
                    this->create_lexem(&temp, position);
                    temp.clear();
                    position[0] = row_position;
                    position[1] = col_position;
                }
                else {
                    temp.push_back(*col);
                }
            }
            else {
                if (itt_expr != this->regex.end()) {
                    //Todo : nouveau lexem pour un mot régulier
                    //TODO : vider temp et ajouter un nouveau lexem
                    Lexem lex(itt_expr->second, itt_expr->first, position);
                    this->lexems.push_back(lex);
                    temp.clear();
                }
                else {
                    if (itt_col != this->regex.end()) {
                        //TODO : vider temp et ajouter un nouveau lexem
                        this->create_lexem(&temp, position);
                        temp.clear();
                        //TODO : nouveau lexem pour un caractère régulier
                        position[0] = row_position;
                        position[1] = col_position;
                        Lexem lex(itt_col->second, itt_col->first, position);
                        this->lexems.push_back(lex);
                    }
                    else {
                        if (col_str == " " || col_str == "\n") {
                            // Todo : créer un nouveau lexem pour la valeur nouvelle
                            // TODO : vider temp

                            this->create_lexem(&temp, position);
                            temp.clear();
                            position[0] = row_position;
                            position[1] = col_position+1; // Car le lexem suivant commence après l'espace, s'il s'agit
                                                          // d'un \n, col_position sera remis à 0 après

                        } else {
                            // Todo : ajouter à temp
                            temp.push_back(*col);
                        }
                    }
                }
            }
            col_position++;
            col++;
        }
    row_position++;
    }
    return 0;
}


string Lexer::find_type(string * value) {
    string out;
    return out;}


int main(int argc, char ** argv) {

    Lexer lexer;

    lexer.run("./prog");
    cout << lexer.lexems[2].kind;
}