#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

// Word Wrap
int main(int argc, char *argv[]) {
    int width = 25;
    char just = 'l';
    string arg1 = "";
    string arg2 = "";
    string arg3 = "";
    string text = "";

    switch (argc-1) {
        case 1:
            arg1 = argv[1];
            just = arg1[1];
            break;
        case 2:
            arg1 = argv[1];
            arg2 = argv[2];
            if (arg1 == "-w") {
                istringstream ss{arg2};
                ss >> width;
            }
            break;
        case 3:
            arg1 = argv[1];
            arg2 = argv[2];
            arg3 = argv[3];
            if (arg1 == "-w") {
                istringstream ss{arg2};
                ss >> width;
                just = arg3[1];
            } else if (arg2 == "-w") {
                just = arg1[1];
                istringstream ss{arg3};
                ss >> width;
            }
            break;
    }

    getline(cin, text);
    int len = text.length();
    string *words = new string[len];
    string *lines = new string[len];
    int wordCount = 0;
    int lineCount = 0;
    for (int i = 0; i < len; i++) {
        char c = text[i];
        if (c == ' ') {
            if ((i > 0) && (text[i-1] != ' ')) wordCount++;
        } else {
            words[wordCount] += c;
        }
    }
    switch(just) {
        case 'l':
            for (int j = 0; j < wordCount + 1; j++) {
                string word = words[j];
                string line = lines[lineCount];
                int wLen = word.length();
                int lLen = line.length();

                if (wLen + lLen + 1 <= width) {
                    if (lLen != 0) {
                        lines[lineCount] += " ";
                    }
                    lines[lineCount] += word;
                } else if (wLen + lLen + 1 > width) {
                    if (lLen != 0) {
                        lines[lineCount] += " ";
                    }
                    if (wLen >= width) {
                        lines[lineCount] += word.substr(0, width - lLen);
                        lineCount++;
                        int cur = width - lLen;
                        while (wLen - cur > width) {
                            lines[lineCount] += word.substr(cur, width);
                            lineCount++;
                            cur += width;
                        }
                        lines[lineCount] += word.substr(cur);
                    } else {
                        lineCount++;
                        lines[lineCount] += word;
                    }
                }
            }

            for (int k = 0; k < lineCount + 1; k++) {
                if (lines[k] != "") {
                    cout << lines[k] << endl;
                }
            }
            break;
        case 'r':
            for (int j = 0; j < wordCount + 1; j++) {
                string word = words[j];
                string line = lines[lineCount];
                int wLen = word.length();
                int lLen = line.length();
                if (wLen > width) {
                    if (lLen != 0) {
                        lines[lineCount] += " ";
                    }
                    if (wLen >= width) {
                        lines[lineCount] += word.substr(0, width - lLen);
                        lineCount++;
                        int cur = width - lLen;
                        while (wLen - cur > width) {
                            lines[lineCount] += word.substr(cur, width);
                            lineCount++;
                            cur += width;
                        }
                        lines[lineCount] += word.substr(cur);
                    } else {
                        lineCount++;
                        lines[lineCount] += word;
                    }
                } else {
                    int tempLen = wLen;
                    int t = j;
                    while (t < wordCount) {
                        string wordNext = words[t+1];
                        tempLen += wordNext.length() + 1;
                        if (tempLen < width) {
                            t++;
                        } else {
                            break;
                        }
                    }

                    for (int p = j; p <= t; p++) {
                        word = words[p];
                        line = lines[lineCount];
                        lLen = line.length();
                        wLen = word.length();
                        if (lLen != 0) {
                            lines[lineCount] += " ";
                        }
                        lines[lineCount] += word;
                    }
                    lineCount++;
                    j = t;
                }
            }

            for (int k = 0; k < lineCount + 1; k++) {
                if (lines[k] != "") {
                    cout << setw(width) << lines[k] << endl;
                }
            }
            break;
        case 'c':
            for (int j = 0; j < wordCount + 1; j++) {
                string word = words[j];
                string line = lines[lineCount];
                int wLen = word.length();
                int lLen = line.length();
                if (wLen > width) {
                    if (lLen != 0) {
                        lines[lineCount] += " ";
                    }
                    if (wLen >= width) {
                        lines[lineCount] += word.substr(0, width - lLen);
                        lineCount++;
                        int cur = width - lLen;
                        while (wLen - cur > width) {
                            lines[lineCount] += word.substr(cur, width);
                            lineCount++;
                            cur += width;
                        }
                        lines[lineCount] += word.substr(cur);
                    } else {
                        lineCount++;
                        lines[lineCount] += word;
                    }
                } else {
                    int tempLen = wLen;
                    int t = j;
                    while (t < wordCount) {
                        string wordNext = words[t+1];
                        tempLen += wordNext.length() + 1;
                        if (tempLen < width) {
                            t++;
                        } else {
                            break;
                        }
                    }

                    for (int p = j; p <= t; p++) {
                        word = words[p];
                        line = lines[lineCount];
                        lLen = line.length();
                        wLen = word.length();
                        if (lLen != 0) {
                            lines[lineCount] += " ";
                        }
                        lines[lineCount] += word;
                    }
                    lineCount++;
                    j = t;
                }
            }

            for (int k = 0; k < lineCount + 1; k++) {
                string thisLine = lines[k];
                int pad = (width - thisLine.length()) / 2;
                if (thisLine != "") {
                    cout << string(pad, ' ') << lines[k] << endl;
                }
            }
            break;
    }

    delete[] words;
    delete[] lines;
}
