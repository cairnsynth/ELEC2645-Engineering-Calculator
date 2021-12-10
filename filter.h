#ifndef FILTER_H
#define FILTER_H
//Required libraries for function declarations
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;


//Set the namespace so functions with the same name dont clash
namespace filter {
    //Function declarations

    //Function declarations for each menu screen
    void main_menu();
    void rc_menu();
    void rl_menu();
    void rlc_menu();

    int get_user_input(int menu_items);

    float select_unit(int input, float value);
    char select_symbol(int input);
    string final_value(float value);

    void select_menu_item(int input);
    void select_rc_item(int input);
    void select_rl_item(int input);
    void select_rlc_item(int input);

    void select_return_rc_cap(int input);
    void select_return_rc_res(int input);
    void select_return_rc_freq(int input);
    void select_return_rl_induc(int input);
    void select_return_rl_res(int input);
    void select_return_rl_freq(int input);
    void select_return_rlc_induc(int input);
    void select_return_rlc_cap(int input);
    void select_return_rlc_freq(int input);

    void print_main_menu();
    void print_rc_menu();
    void print_rl_menu();
    void print_rlc_menu();

    void go_back_to_main_menu();

    bool is_integer(string num);

    void print_rc_cap();
    void print_rc_res();
    void print_rc_freq();
    void print_rl_induc();
    void print_rl_res();
    void print_rl_freq();
    void print_rlc_induc();
    void print_rlc_cap();
    void print_rlc_freq();

    void print_unit_menu();

    //float e_changer(float value);

    void rc_high();
    void rl_high();
    void rlc_high();

    void rc_filter();
    void rl_filter();
    void rlc_filter();

    void rc_cap();
    void rc_res();
    void rc_freq();
    void rl_induc();
    void rl_res();
    void rl_freq();
    void rlc_induc();
    void rlc_cap();
    void rlc_freq();

    float cap_data();
    float res_data();
    float induc_data();
    float freq_data();
}

#endif //FILTER_H


