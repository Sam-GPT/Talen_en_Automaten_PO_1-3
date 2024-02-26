//
// Created by USER on 18/02/2024.
//

#include "DFA.h"
using json = nlohmann::json;
bool DFA::accepts(string languge) {
    for(auto in : languge){
        changeState(*cur_state, in);
    }
    return cur_state == acept_state;
}

void DFA::changeState(DFA::State current_state, char input) {
    auto it = current_state.transitions.find(input);
    if (it != current_state.transitions.end()) {
        cur_state = it->second;
    }
    else{
        cout << "Wutt"<<endl;
    }
}

DFA::~DFA() {
    for(auto state : states){
        delete state;
    }
    states.clear();
}

DFA::DFA(const string &filename) : filename(filename) {

    ifstream input(filename);

    json data = json::parse(input);

    vector<string> alphabet = data["alphabet"];
    alfabet = alphabet;

    type = data["type"];


    for(auto state : data["states"]){
        State* newstate = new State(state["name"], state["starting"], state["accepting"]);
        newstate->starting = state["starting"];
        newstate->accepting = state["accepting"];

        if(newstate->starting){
            cur_state = newstate;
        }

        if(newstate->accepting){
            acept_state = newstate;
        }
        states.push_back(newstate);
    }

    for(auto trans : data["transitions"]){
        auto from = std::find_if(states.begin(), states.end(), [&trans](const State* state) {
            return state->name == trans["from"].get<std::string>();
        });

        auto to = std::find_if(states.begin(), states.end(), [&trans](const State* state) {
            return state->name == trans["to"].get<std::string>();
        });

        string input_s = trans["input"].get<std::string>();



        pair<char, State*> p = make_pair(input_s[0], *to);

        (*from)->transitions.insert(p);
    }



}

void DFA::print() const {
    json j;

    j["type"] = type;
    j["alphabet"] = alfabet;

    for(auto state : states){
        json stateJson;
        stateJson["name"] = state->name;
        stateJson["starting"] = state->starting;
        stateJson["accepting"] = state->accepting;
        j["states"].push_back(stateJson);
    }

    for(auto state : states){
        for(auto input : alfabet){
            char in = input[0];
            json stateJson;
            stateJson["from"] = state->name;
            stateJson["to"] = state->transitions[in]->name;
            stateJson["input"] = input;
            j["transitions"].push_back(stateJson);
        }

    }

    cout <<setw(4) << j << endl;


}

DFA::State::State(const string &name, bool starting, bool accepting) : name(name), starting(starting),
                                                                       accepting(accepting) {}
