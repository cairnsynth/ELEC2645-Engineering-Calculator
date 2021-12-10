#include "filter.h"
#include <iostream>
#include <regex>
#define _USE_MATH_DEFINES             //https://stackoverflow.com/questions/26065359/m-pi-flagged-as-undeclared-identifier
#include <cmath>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>

//https://stackoverflow.com/questions/4184468/sleep-for-milliseconds

#include <chrono>
#include <thread>

using namespace std;


namespace filter {

  void main_menu() {
  print_main_menu();
  int menu_items_pre = 4;
  int input = get_user_input(menu_items_pre);
  select_menu_item(input);
  }

  void rc_menu() {
    print_rc_menu();
    int menu_items_pre = 4;
    int input = get_user_input(menu_items_pre);
    select_rc_item(input);
    }

  void rl_menu() {
    print_rl_menu();
    int menu_items_pre = 4;
    int input = get_user_input(menu_items_pre);
    select_rl_item(input);
    }

  void rlc_menu() {
    print_rlc_menu();
    int menu_items_pre = 4;
    int input = get_user_input(menu_items_pre);
    select_rlc_item(input);
    }

    /*
    float e_changer(float value){
    cout << "\n" << value;
    string str_value(to_string(value));
    str_value.empty() ? cout << "empty\n" : cout << str_value << endl;
    cout << "Initial string: " << str_value << endl;
    replace(str_value.begin(), str_value.end(), '0', '~' );
    cout << "Final string: " << str_value;
    }
    */

  float select_unit(int input, float value) {
    if (input == 1) {
      value = value*pow(10,9);
      return value;
    }
    else if (input == 2) {
      value = value*pow(10,6);
      return value;
    }
    else if (input == 3) {
      value = value*pow(10,3);
      return value;
    }
    else if (input == 4) {
      return value;
    }
    else if (input == 5) {
      value = value*pow(10,-3);
      return value;
    }
    else if (input == 6) {
      value = value*pow(10,-6);
      return value;
    }
    else if (input == 7) {
      value = value*pow(10,-9);
      return value;
    }
  return 0;
  }

  char select_symbol(int input) {
    if (input == 1) {
      char symbol = 'G';
      return symbol;
    }
    else if (input == 2) {
      char symbol = 'M';
      return symbol;
    }
    else if (input == 3) {
      char symbol = 'k';
      return symbol;
    }
    else if (input == 4) {
      char symbol = 'm';
      return symbol;
    }
    else if (input == 5) {
      char symbol = 'u';
      return symbol;
    }
    else if (input == 6) {
      char symbol = 'n';
      return symbol;
    }
  return 0;
  }

  string final_value(float value){
    cout << "\n" << value;
    string str_value(to_string(value));
    cout << "Initial string: " << str_value << endl;
    str_value.erase(std::remove(str_value.begin(), str_value.end(), '0'), str_value.end());
    cout << "Final string: " << str_value;
    return 0;
  }

  float cap_data() {
    float cap;
    float pre_cap;
    int cap_unit;
    cout << "\nEnter a value for Capacitance: ";
    cin >> pre_cap;
    cout << "\nEnter the number correlating to the unit you would like to use for Capacitance\n";
    int menu_items_pre = 7;
    cap_unit = get_user_input(menu_items_pre);
    float new_cap = select_unit(cap_unit, pre_cap);
    char cap_symbol = select_symbol(cap_unit);
    cap = new_cap;
    return cap;
  }

  float res_data() {
    float res;
    float pre_res;
    int res_unit;
    cout << "\nEnter a value for Resistance: ";
    cin >> pre_res;
    cout << "\nEnter the number correlating to the unit you would like to use for Resistance\n";
    int menu_items_pre = 7;
    res_unit = get_user_input(menu_items_pre);
    float new_res = select_unit(res_unit, pre_res);
    char res_symbol = select_symbol(res_unit);
    res = new_res;
    return res;
  }

  float induc_data() {
    float induc;
    float pre_induc;
    int induc_unit;
    cout << "\nEnter a value for Inductance: ";
    cin >> pre_induc;
    cout << "\nEnter the number correlating to the unit you would like to use for Inductance\n";
    int menu_items_pre = 7;
    induc_unit = get_user_input(menu_items_pre);
    float new_induc = select_unit(induc_unit, pre_induc);
    char induc_symbol = select_symbol(induc_unit);
    induc = new_induc;
    return induc;
  }

  float freq_data() {
    float freq;
    float pre_freq;
    int freq_unit;
    cout << "\nEnter a value for Frequency: ";
    cin >> pre_freq;
    cout << "\nEnter the number correlating to the unit you would like to use for Frequency\n";
    int menu_items_pre = 7;
    freq_unit = get_user_input(menu_items_pre = 7);
    float new_freq = select_unit(freq_unit, pre_freq);
    char freq_symbol = select_symbol(freq_unit);
    freq = new_freq;
    return freq;
  }

  void rc_cap() {
    print_rc_cap();
    float res = res_data();
    float freq = freq_data();
    float cap = 1/(freq*2*M_PI*res);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Resistance: " << res << "Ω";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Capacitance: " << cap << "F";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RC Filter Capacitance Calculation, Press 2 to return to the RC Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rc_cap(input);
  }

  void rc_res() {
    print_rc_res();
    float cap = cap_data();
    float freq = freq_data();
    float res = 1/(freq*2*M_PI*cap);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Capacitance: " << cap << "F";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Resistance: " << res << "Ω";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RC Filter Resistance Calculation, Press 2 to return to the RC Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rc_res(input);
  }

  void rc_freq() {
    print_rc_freq();
    float cap = cap_data();
    float res = res_data();
    float freq = 1/(res*2*M_PI*cap);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Capacitance: " << cap << "F";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Resistance: " << res << "Ω";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RC Filter Frequency Calculation, Press 2 to return to the RC Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rc_freq(input);
  }

  void rl_induc() {
    print_rl_induc();
    float res = res_data();
    float freq = freq_data();
    float induc = res/(freq*2*M_PI);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Resistance: " << res << "Ω";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Inductance: " << induc << "H";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RL Filter Inductance Calculation, Press 2 to return to the RL Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rl_induc(input);
  }

  void rl_res() {
    print_rl_res();
    float induc = induc_data();
    float freq = freq_data();
    float res = (freq*2*M_PI*induc);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Inductance: " << induc << "H";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Resistance: " << res << "Ω";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RL Filter Resistance Calculation, Press 2 to return to the RL Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rl_res(input);
  }

  void rl_freq() {
    print_rl_freq();
    float induc = induc_data();
    float res = res_data();
    float freq = res/(2*M_PI*induc);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Inductance: " << induc << "H";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Resistance: " << res << "Ω";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RL Filter Frequency Calculation, Press 2 to return to the RL Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rl_freq(input);
  }

  void rlc_induc() {
    print_rlc_induc();
    float cap = cap_data();
    float freq = freq_data();
    float induc = pow((1/(freq*2*M_PI)), 2)/cap;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Capacitance: " << cap << "F";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Inductance: " << induc << "H";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RLC Filter Inductance Calculation, Press 2 to return to the RLC Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rlc_induc(input);
  }

  void rlc_cap() {
    print_rlc_cap();
    float induc = induc_data();
    float freq = freq_data();
    float cap = pow((1/(freq*2*M_PI)), 2)/induc;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Inductance: " << induc << "H";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Capacitance: " << cap << "F";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RLC Filter Capacitance Calculation, Press 2 to return to the RLC Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rlc_cap(input);
  }

  void rlc_freq() {
    print_rlc_freq();
    float induc = induc_data();
    float cap = cap_data();
    float freq = 1/(2*M_PI*pow(induc*cap, 0.5));
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Capacitance: " << cap << "F";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n" << "Inductance: " << induc << "H";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n" << "Frequency: " << freq << "Hz";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nCalculated!";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\nPress 1 do carry out another RLC Filter Frequency Calculation, Press 2 to return to the RLC Filter menu and Press 3 to go back to the main menu!";
    this_thread::sleep_for(chrono::milliseconds(500));
    int menu_items_pre = 3;
    int input = get_user_input(menu_items_pre);
    select_return_rlc_freq(input);
  }

  int get_user_input(int menu_items) {
    int input;
    string input_string;
    bool valid_input = false;

    do {
      cout << "\nSelect item: ";
      cin >> input_string;
      valid_input = is_integer(input_string);
      // if input is not an integer, print an error message
      if (valid_input == false) {
        cout << "Enter an integer!\n";
      } else {  // if it is an int, check whether in range
        input = stoi(input_string);  // convert to int
        if (input >= 1 && input <= menu_items) {
          valid_input = true;
        } else {
          cout << "Invalid menu item!\n";
          valid_input = false;
        }
      }
    } while (valid_input == false);

    return input;
  }

  void select_menu_item(int input) {
    switch (input) {
      case 1:
        rc_menu();
        break;
      case 2:
        rl_menu();
        break;
      case 3:
        rlc_menu();
        break;
      case 4:
        break;
    }
  }

  void select_rc_item(int input) {
    switch (input) {
      case 1:
        rc_cap();
        break;
      case 2:
        rc_res();
        break;
      case 3:
        rc_freq();
        break;
      case 4:
        main_menu();
        break;
    }
  }

  void select_rl_item(int input) {
    switch (input) {
      case 1:
        rl_induc();
        break;
      case 2:
        rl_res();
        break;
      case 3:
        rl_freq();
        break;
      case 4:
        main_menu();
        break;
    }
  }

  void select_rlc_item(int input) {
    switch (input) {
      case 1:
        rlc_induc();
        break;
      case 2:
        rlc_cap();
        break;
      case 3:
        rlc_freq();
        break;
      case 4:
        main_menu();
        break;
    }
  }

  void select_return_rc_cap(int input) {
    switch (input) {
      case 1:
        rc_cap();
        break;
      case 2:
        rc_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rc_res(int input) {
    switch (input) {
      case 1:
        rc_res();
        break;
      case 2:
        rc_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rc_freq(int input) {
    switch (input) {
      case 1:
        rc_freq();
        break;
      case 2:
        rc_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rl_induc(int input) {
    switch (input) {
      case 1:
        rl_induc();
        break;
      case 2:
        rl_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rl_res(int input) {
    switch (input) {
      case 1:
        rl_res();
        break;
      case 2:
        rl_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rl_freq(int input) {
    switch (input) {
      case 1:
        rl_freq();
        break;
      case 2:
        rl_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rlc_induc(int input) {
    switch (input) {
      case 1:
        rlc_induc();
        break;
      case 2:
        rlc_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rlc_cap(int input) {
    switch (input) {
      case 1:
        rlc_cap();
        break;
      case 2:
        rlc_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void select_return_rlc_freq(int input) {
    switch (input) {
      case 1:
        rlc_freq();
        break;
      case 2:
        rlc_menu();
        break;
      case 3:
        main_menu();
        break;
    }
  }

  void print_main_menu() {
    cout << "\n------- Main menu -------\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t1. RC Filter\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t2. RL Filter\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t3. RLC Filter\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t4. Exit\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "-------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(150));
  }

  void print_rc_menu() {
    cout << "\n----------------- RC Filter -----------------\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t1. Calculation for Capacitance\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t2. Calculation for Resistance\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t3. Calculation for Cut-Off Frequency\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t4. Back to main menu\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "---------------------------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(150));
  }

  void print_rl_menu() {
    cout << "\n----------------- RL Filter -----------------\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t1. Calculation for Inductance\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t2. Calculation for Resistance\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t3. Calculation for Cut-Off Frequency\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t4. Back to main menu\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "---------------------------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(150));
  }

  void print_rlc_menu() {
    cout << "\n---------------- RLC Filter -----------------\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t1. Calculation for Inductance\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t2. Calculation for Capacitance\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t3. Calculation for Cut-Off Frequency\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t4. Back to main menu\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "---------------------------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(150));
  }

  void print_unit_menu() {
    cout << "\n------ Unit Conversion ------\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t1. G = Giga = x10^9\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t2. M = Mega = x10^6\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t3. k = Kilo = x10^3\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t4. B = Base = x10^0\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t5. m = Milli = x10^-3\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t6. μ = Micro = x10^-6\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t7. n = Nano = x10^-9\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "|\t\t\t\t\t\t\t|\n";
    this_thread::sleep_for(chrono::milliseconds(50));
    cout << "-----------------------------\n";
    this_thread::sleep_for(chrono::milliseconds(50));
  }


  void go_back_to_main() {
    string input;
    do {
      cout << "\nEnter 'b' or 'B' to go back to main menu: ";
      cin >> input;
    } while (input != "b" && input != "B");
    main_menu();
  }

  // https://codereview.stackexchange.com/questions/162569/checking-if-each-char-in-a-string-is-a-decimal-digit

  bool is_integer(string num) {
    return regex_match(num, regex("[+-]?[0-9]+"));
  }

  void print_rc_cap() {
    cout << "\n>> RC Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Capacitance <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rc_res() {
    cout << "\n>> RC Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Resistance <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rc_freq() {
    cout << "\n>> RC Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Cut-Off Frequency <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rl_induc() {
    cout << "\n>> RL Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Inductance <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rl_res() {
    cout << "\n>> RL Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Resistance <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rl_freq() {
    cout << "\n>> RL Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Cut-Off Frequency <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rlc_induc() {
    cout << "\n>> RLC Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Inductance <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rlc_cap() {
    cout << "\n>> RLC Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Capacitance <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }

  void print_rlc_freq() {
    cout << "\n>> RLC Filter <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "\n>> Working out for Cut-Off Frequency <<\n";
    this_thread::sleep_for(chrono::milliseconds(400));
    print_unit_menu();
  }
      
}
