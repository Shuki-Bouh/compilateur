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
        cout << "\" manquant" << endl;
        exit(2);
    }
}

int Lexer::create_lexem(string * value, int (&position)[2], string kind) {
    int statut = 0;

    if (*value != "") {

        if (kind == "") {
            string kind = this->find_type(value);
            Lexem lex(kind, *value, position);
            this->lexems.push_back(lex);
        }
        else {
            Lexem lex(kind, *value, position);
            this->lexems.push_back(lex);
        }
    }
    else {
        statut = 1;
    }
    return statut;
}

int Lexer::parse_file(ifstream * stream) {
    int out;

    // Indices du parcours du fichier

    int row_position = 0;
    string row;
    int col_position;

    bool is_str = false; // celui-ci sert à savoir si on est encore dans une chaîne de caractère

    istringstream row_stream;

    // Valeurs des lexems
    int position[2] = {0, 0};

    // Liste temporaire du lexem en cours

    string temp;

    while (getline(*stream, row)) {
        col_position = 0;
        auto col = row.begin();
        while (col < row.end()) {
            string col_str(1, *col);
            auto itt_expr = this->regex.find(temp);
            auto itt_col = this->regex.find(col_str);
            if (col_str == "\"" || is_str) {
                if (col_str == "\"") {
                    is_str = 1 - is_str;
                    if (is_str) {
                        this->create_lexem(&temp, position);
                    }
                    else {
                        this->create_lexem(&temp, position, "str");
                    }
                    temp.clear();
                    position[0] = row_position;
                    position[1] = col_position;
                }
                else {
                    temp.push_back(*col);
                }
            }
            else {
                if (itt_col != this->regex.end() && itt_expr != this->regex.end()) {
                   // TODO
                    this->create_lexem(&temp, position);
                    temp.clear();
                    position[0] = row_position;
                    position[1] = col_position;
                    temp.push_back(*col);
                }
                else {
                    // Todo : on vérifie que temp est un regex avec le nouveau caractère ... Sinon il est un regex uniquement avec le précédent
                    if (itt_expr != this->regex.end()) {
                        string value = itt_expr->first;
                        this->create_lexem(&value, position, itt_expr->second);
                        temp.clear();
                        position[0] = row_position;
                        position[1] = col_position + 1;
                    }
                    else {
                        if (col_str == " " || col_str == "\n") {

                            this->create_lexem(&temp, position);
                            temp.clear();
                            position[0] = row_position;
                            position[1] = col_position+1; // Car le lexem suivant commence après l'espace, s'il s'agit
                                                          // d'un \n, col_position sera remis à 0 après

                        } else {
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
    return is_str; // 1 si on est toujours dans un str, 0 sinon
}


string Lexer::find_type(string * value) {
    string out;
    string::size_type ez;
    int int_value = stoi(*value, &ez);
    string n_value = to_string(int_value);
    if (n_value == *value) {
        out = "int";
    }
    else {
        ez++;
        n_value.push_back('.');
        int c = stoi(value->substr(ez));
        n_value += to_string(c);
        if (n_value == *value) {
            out = "float";
        }
        else {
            out = "ident";
        }
    }
    return out;
}


int main(int argc, char ** argv) {

    Lexer lexer;
    string a = "1232.245";
    cout << lexer.find_type(&a) << endl;
}