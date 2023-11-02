//
// Created by talkysafe143 on 1/10/23.
//

#include "Utils.h"


static map<char, int> getFreq(string file) {
    map<char, int> freq;

    ifstream input(file);

    if (!input) {
        freq['a'] = -1;
        return freq;
    }

    string line;

    while (getline(input, line)) {
        for (char c: line) freq[c]++;
    }

    input.close();

    return freq;
}
