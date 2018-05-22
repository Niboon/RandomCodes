#include <iostream>
#include <sstream>
using namespace std;

// Substitution cipher
int main(int argc, char *argv[]) {
    int shift = 3;
    string text = "";

    if ((argc-1) >= 1) {
        istringstream ss{argv[1]};
        int arg1;
        if (ss >> arg1){
            shift = arg1 % 26;
        }
    }

    if ((argc-1) >= 2) {
        string arg2 = argv[2];
        if (arg2 == "left") {
            shift = (26 - shift);
        }
    }

    int len = 0;
    bool done = false;
    while (!done) {
        char c;
        cin >> c; // reads a single e, d or q
        if (cin.eof()) break;
        switch(c) {
            case 'e':
                getline(cin, text);
                len = text.length();
                for (int i=0; i<len; i++) {
                    char clear = text[i];
                    if (( clear >= 'a' ) && ( clear <= 'z' )) {
                        char cipher = 'a' + ((clear - 'a' + shift) % 26);
                        text[i] = cipher;
                    } else if (( clear >= 'A' ) && ( clear <= 'Z' )) {
                        char cipher = 'A' + ((clear - 'A' + shift) % 26);
                        text[i] = cipher;
                    }
                }
                cout << text << endl;
                break;
            case 'd':
                getline(cin, text);
                len = text.length();
                for (int i=0; i<len; i++) {
                    char clear = text[i];
                    int deShift = 26 - shift;
                    if (( clear >= 'a' ) && ( clear <= 'z' )) {
                        char cipher = 'a' + ((clear - 'a' + deShift) % 26);
                        text[i] = cipher;
                    } else if (( clear >= 'A' ) && ( clear <= 'Z' )) {
                        char cipher = 'A' + ((clear - 'A' + deShift) % 26);
                        text[i] = cipher;
                    }
                }
                cout << text << endl;
                break;
            case 'q':
                done = true;
                break;
        }
    }
}
