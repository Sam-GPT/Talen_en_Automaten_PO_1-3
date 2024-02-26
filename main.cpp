//
// Created by USER on 26/02/2024.
//
#include <iostream>
#include "DFA.h"

using namespace std;

int main() {
    DFA dfa("DFA.json");
    cout << boolalpha << dfa.accepts("0010110100") << endl << dfa.accepts("0001") << endl;
    dfa.print();
    return 0;
}