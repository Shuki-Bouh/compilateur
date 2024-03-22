#include <iostream>
#include <string>
#include <sstream>
#include "Lexer.h"
using namespace std;


int main(int argc, char ** argv) {
    string a = "main";
    Lexer lexer;
    auto b = lexer.regex.find(a);
    cout << b->second << endl;

    return 0;
}






