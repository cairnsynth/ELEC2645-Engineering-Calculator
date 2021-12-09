#include <iostream>
#include <string>
#include <list>

#include "inverting_amplifier.h"

//Main loop
int main() {
    while(1) {
        std::list<std::string> menuItems = {"1. Inverting Amplifier Calculator", "2. Filter Calculator", "3. Function 3", "4. Exit"};
        iamp::print_menu("ELEC2645 Engineering Calculator", "Select a function:", menuItems);
        int input = iamp::user_input(4);

        if(input == 1) {
            iamp::main_menu();
        }
        else if(input == 2) {
            //filter calculator entrypoint
        }
        else if(input == 3) {
            //Function 3 entrypoint
        }
        else {
            exit(1);
        }
    }
}
