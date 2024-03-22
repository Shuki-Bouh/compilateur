#include "Lexer.h"
#include <sstream>

using namespace std;

void Lexer::run(char * file) {
    ifstream stream(file);

    if (stream) {
        this->parse_file(&stream);
    } else {
        cout << "Impossible d'ouvrir le fichier" << endl;
        exit(1);
    }

}



void Lexer::parse_file(ifstream * stream) {
    // Indices du parcours du fichier

    int row_position = 0;
    string row;
    int col_position;

    istringstream row_stream;

    // Valeurs des lexems
    char * valeur;
    char * kind;
    int position[2];

    // Liste temporaire du lexem en cours

    vector<char> temp;



    while (getline(*stream, row)) {
        col_position = 0;

        auto col = row.begin();
        while (col < row.end()) {
            string col_str(1, *col);
            auto expr = this->regex.find(col_str);
            if (*col != ' ' && *col != '\n' && expr != this->regex.end()) {
                temp.push_back(*col);
            }
            else {
                for (auto c = temp.begin(); c < temp.end(); c++) {
                    string c_str(1, *c);
                    auto expr = this->regex.find(c_str);
                    if (expr != this->regex.end()) {

                    }
                }
                string temp_str(temp.begin(), temp.end());
                auto expr = this->regex.find(temp_str);
            }
        }
    }




    while (data[i] != '\0') {
        temp.clear();
        if (data[i] == '\n') {
            ligne++;
            col = 0;
        }
        auto el = this->regex.find(&data[i]);
        if (el != this->regex.end()) {
            temp.push_back(data[i]);
            if ( data[i+1] == '='){
                temp.push_back('=');
                i++;
                col++;
            }
            valeur = this->convertVect2Str(temp);
            kind = this->trouve_type(valeur);
            position[0] = ligne;
            position[1] = col;
            Lexem lex(kind, valeur, position);
            this->lexems.push_back(lex);
            i++;
            col++;
        }
        else{
            if (data[i] == '"') {
                position[0] = ligne;
                position[1] = col;
                col++;
                try {
                    temp.push_back('"');
                    while (data[i] != '"') {
                        temp.push_back(data[i]);
                        col++;
                        i++;
                    }
                    temp.push_back('"');
                    valeur = this->convertVect2Str(temp);
                    Lexem lex("string", valeur, position);
                    this->lexems.push_back(lex);
                }
                catch (...) {
                    cout << "Manque guillemets" << endl;
                }
                col++;
            }
            if (data[i] != ' ' && data[i] != '\t') {
                position[0] = ligne;
                position[1] = col;
                auto el = this->regex.find(&data[i]);
                while ( data[i] != '\n' &&
                        el == this->regex.end() &&
                        data[i] != ' ' &&
                        data[i] != '\t' &&
                        data[i] != '\0')
                {
                    temp.push_back(data[i]);
                    i++;
                    col++;
                    el = this->regex.find(&data[i]);
                }
                valeur = this->convertVect2Str(temp);
                kind = this->trouve_type(valeur);
                Lexem lex(kind, valeur, position);
                this->lexems.push_back(lex);
            }
            else{
                col++;
                i++;
            }

        }
    }
}

char * Lexer::trouve_type(char *word) {
    char * type;
    if (word == "true" || word == "false")
        type = "bool";
    else {
        try {
            atoi(word);
            type = "int";
        }
        catch (...) {
            try {
                float(word);
                type = "float";
            }
            catch (...) {type = "ident";}
        }
    }
    return type;
}


int main(int argc, char ** argv) {

    Lexer lexer;

    lexer.run("prog");
    cout << lexer.lexems[1].valeur;
}