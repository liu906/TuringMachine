//
// Created by lau on 2019/12/8.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
#ifndef TURING_TM_H
#define TURING_TM_H

struct Transition{
    string old_state;
    string old_chas;
    string new_chas;
    vector<char> directions;
    string new_state;
};

class TM {
public:
    vector<string> states;
    string symbols;
    string tape_symbols;
    char start_state;
    char blank;
    vector<string> final_state;
    int num_tapes;
    vector<Transition> tran_funcs;
    void print_tran_funcs();
    void print_states();
    void print_symbols();
    void print_tape_symbols();
    void print_final_state();
    void print_blank();
    void print_start_state();
    void print_num_tapes();
};


#endif //TURING_TM_H
