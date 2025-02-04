#include <bits/stdc++.h>
using namespace std;

// Predefined arrays for keywords, operators, and punctuations
const unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
    "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Bool",
    "_Complex", "_Imaginary"
};

const unordered_set<string> operators = {
    "+", "-", "", "/", "%", "++", "--", "=", "+=", "-=", "=", "/=", "%=", "==", "!=",
    ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>"
};

const unordered_set<string> punctuations = {
    "(", ")", "{", "}", "[", "]", ";", ":", ",", ".", "->", "..."
};

// Function to classify a token
string classifyToken(const string &token) {
    if (keywords.count(token)) {
        return "keyword";
    }
    if (operators.count(token)) {
        return "operator";
    }
    if (punctuations.count(token)) {
        return "punctuation";
    }
    if (isalpha(token[0]) || token[0] == '_') { // Starts with a letter or ''
        return "identifier";
    }
    if (isdigit(token[0])) { // Starts with a digit
        return "constant";
    }
    return "unknown";
}

int main() {
    ifstream file("Pr_3_input.txt");
    if (!file) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    string line;
    int wordCount = 0;
    vector<string> v;
    bool inMultilineComment = false;

    while (getline(file, line)) {
        istringstream stream(line);
        string word;

        while (stream >> word) {
            if (inMultilineComment) {
                if (word.find("*/") != string::npos) {
                    inMultilineComment = false;
                }
                continue;
            }

            if (word.find("//") != string::npos) {
                break;
            }
            if (word.find("/*") != string::npos) {
                inMultilineComment = true;
                continue;
            }

            string temp;
            for (char c : word) {
                if (isalnum(c) || c == '\'' || c == '_') {
                    temp += c;
                } else {
                    if (!temp.empty()) {
                        v.push_back(temp);
                        wordCount++;
                        temp.clear();
                    }
                    v.push_back(string(1, c));
                    wordCount++;
                }
            }
            if (!temp.empty()) {
                v.push_back(temp);
                wordCount++;
            }
        }
    }

    cout << "Total words: " << wordCount << endl;
    cout << "\nClassified Tokens:\n";

    // Classify and display tokens
    for (const auto &token : v) {
        cout << token << " = " << classifyToken(token) << endl;
    }

    file.close();
    return 0;
}