//
// Created by USER on 18/02/2024.
//

#ifndef GAS_TOI_DFA_H
#define GAS_TOI_DFA_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include "json.hpp"
using namespace std;


class DFA {
    struct State{
        string name;
        unordered_map<char, State*> transitions = {};

        bool starting;
        bool accepting;

        State(const string &name, bool starting, bool accepting);


    };
    State* cur_state;
    State* acept_state;
    vector<State*> states;
    vector<string> alfabet;
    string filename;
    string type;


public:
    explicit DFA(const string &filename);

    virtual ~DFA();

    bool accepts(string languge);

    void changeState(State current_state, char input);

    void print() const;
};


#endif //GAS_TOI_DFA_H
