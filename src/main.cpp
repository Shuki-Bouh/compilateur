#include <iostream>
#include <string>
#include <sstream>
#include "Lexer.h"
using namespace std;


int main(int argc, char ** argv) {
    string a = "156.2454";
    string::size_type ez;
    int b = stoi(a, &ez);
    cout << b << endl;
    ez++;
    b = stoi(a.substr(ez));
    cout << b << endl;


    return 0;
}






