#include <iostream>
#include "binarynum.h"

using namespace std;

BinaryNum readBinaryNum() {
    string text;
    int len = 0;
    int cap = 0;
    BinaryNum ret{};
    bool done = false;
    while (!done) {
        char c;
        cin >> c;
        if (cin.eof()) break;
        switch(c) {
            case '0':
            case '1':
                text += c;
                break;
            default :
                if (!isspace(c)) {
                    done = true;
                }
                break;
        }
    }
    len = text.length();
    if (len == 0) {
        ret.capacity = len;
        ret.size = cap;
        return ret;
    } else {
        cap = 4;
    }
    while (cap < len) {
        cap *= 2;
    }
    ret.contents = new bool[cap];
    ret.capacity = cap;
    for (int i = 0; i < len; i++) {
        ret.contents[i] = text[i] != '0';
    }
    ret.size = len;
    return ret;
}

void binaryConcat(BinaryNum &binNum) {
    string text = "";
    int newSize = binNum.size;
    int cap = binNum.capacity;

    BinaryNum tempNum = readBinaryNum();

    if (binNum.contents == nullptr) {
        binNum.capacity = tempNum.capacity;
        binNum.size = tempNum.size;
        binNum.contents = tempNum.contents;
        return;
    }

    newSize += tempNum.size;
    while (cap < newSize) {
        cap *= 2;
    }
    bool *temp = new bool[cap];
    for (int i = 0; i < binNum.size; i++) {
        temp[i] = binNum.contents[i];
    }
    delete[] binNum.contents;
    binNum.contents = nullptr;
    int index = 0;
    for (int i = binNum.size; i < newSize; i++) {
        temp[i] = tempNum.contents[index];
        index++;
    }
    delete[] tempNum.contents;
    binNum.contents = temp;
    binNum.capacity = cap;
    binNum.size = newSize;
}

int binaryToDecimal(const BinaryNum &binNum) {
    int ret = 0;
    int size = binNum.size;
    int tmp = 1;
    int exp = 0;
    for (int i = 0; i < size; i++) {
        tmp = 1;
        exp = size - i - 1;
        for (int j = 0; j < exp; j++) {
            tmp *= 2;
        }
        if (binNum.contents[i]) ret += tmp;
    }
    return ret;
}

void printBinaryNum(std::ostream &out, const BinaryNum &binNum, char sep) {
    if (binNum.contents == nullptr) {
        return;
    }
    for (int i = 0; i < binNum.size; i++) {
        int temp = (binNum.contents[i] == 0) ? 0 : 1;
        cout << temp;
        if (i < (binNum.size - 1)) cout << sep;
    }
}

BinaryNum &operator<<(BinaryNum &binNum, int num) {
    string text = "";
    int newSize = binNum.size;
    int cap = binNum.capacity;

    if (binNum.size == 0) {
        return binNum;
    }

    cap = binNum.capacity;
    newSize += num;
    while (cap < newSize) {
        cap *= 2;
    }
    bool *temp = new bool[cap];
    for (int i = 0; i < binNum.size; i++) {
        temp[i] = binNum.contents[i];
    }
    delete[] binNum.contents;
    for (int i = binNum.size; i < newSize; i++) {
        temp[i] = false;
    }
    binNum.contents = temp;
    binNum.capacity = cap;
    binNum.size = newSize;
    return binNum;
}
