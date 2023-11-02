//
// Created by talkysafe143 on 1/10/23.
//

#include "Utils.h"

 bool Utils::compareFieldLists(list<Territorio> a, list<Territorio> b) {
    if (a.size() != b.size()) return false;

    a.sort(); b.sort();

    list<Territorio>::iterator itA = a.begin();
    list<Territorio>::iterator itB = b.begin();

    for (; itA != a.end() && itB != b.end(); itA++, itB++) {
        if (itA->getIdTerritorio() != itB->getIdTerritorio()) return false;
    }

    return true;
}

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
