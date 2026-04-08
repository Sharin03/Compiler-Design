#include <iostream>
#include <fstream>

using namespace std;

string classifyToken(string token) {


    string keywords[] = {"int", "float", "double", "char", "return",

                         "if", "else", "while", "for", "main", "void",

                         "cout", "cin", "endl", "include", "using", "namespace"};

    int keySize = sizeof(keywords) / sizeof(keywords[0]);



    for (int i = 0; i < keySize; i++) {

        if (token == keywords[i]) {

            return "Keyword";

        }

    }


    string operators[] = {"=", "+", "-", "*", "/", "<", ">", "<<", ">>",

                          "==", "!=", "<=", ">="};

    int opSize = sizeof(operators) / sizeof(operators[0]);



    for (int i = 0; i < opSize; i++) {

        if (token == operators[i]) {

            return "Operator";

        }

    }


    string puncts[] = {";", ",", "{", "}", "(", ")", "[", "]"};

    int puncSize = sizeof(puncts) / sizeof(puncts[0]);



    for (int i = 0; i < puncSize; i++) {

        if (token == puncts[i]) {

            return "Punctuation";

        }

    }


    if (token[0] == '"' || token[token.size()-1] == '"') {

        return "String";

    }


    bool isNumber = true;

    for (int i = 0; i < token.size(); i++) {

        if (!isdigit(token[i])) {

            isNumber = false;

            break;

        }

    }

    if (isNumber && !token.empty()) {

        return "Constant";

    }

    return "Identifier";

}

void tokenizeLine(string line, int lineNum) {

    cout << "\nLine " << lineNum << ": \"" << line << "\"" << endl;

    string token = "";

    for (int i = 0; i < line.size(); i++) {

        char c = line[i];


        if (c == ' ') {

            if (!token.empty()) {

                cout << "  " << token << "  -->  " << classifyToken(token) << endl;

                token = "";

            }

        }

        else if (c == ';' || c == ',' || c == '{' || c == '}' ||

                 c == '(' || c == ')' || c == '[' || c == ']') {

            if (!token.empty()) {

                cout << "  " << token << "  -->  " << classifyToken(token) << endl;

                token = "";

            }

            string punc(1, c);

            cout << "  " << punc << "  -->  Punctuation" << endl;

        }

        else {

            token += c;

        }

    }



    if (!token.empty()) {

        cout << "  " << token << "  -->  " << classifyToken(token) << endl;

    }

}

int main() {

    ofstream outFile("input.txt");

    if (!outFile) {

        cout << "Error: Could not create file!" << endl;

        return 1;

    }

    outFile << "int main(){\n";

    outFile << "int x ;\n";

    outFile << "x = 10 ;\n";

    outFile << "cout << \"Hello World\" << endl ;\n";

    outFile << "return 0 ;\n";

    outFile << "}\n";

    outFile.close();


    ifstream inFile("input.txt");



    if (!inFile) {

        cout << "Error: Could not open file!" << endl;

        return 1;

    }



    string line;

    int lineNumber = 1;


    while (getline(inFile, line)) {

        tokenizeLine(line, lineNumber);

        lineNumber++;

    }



    inFile.close();

    return 0;

}
