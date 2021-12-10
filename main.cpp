#include <iostream>
#include <string>
#include <list>

#include "inverting_amplifier.h"
#include "filter.h"

//Main loop
int main() {
    while(1) {
        std::list<std::string> menuItems = {"1. Inverting Amplifier Calculator", "2. Filter Calculator", "3. Resistor Colour Code Calculator", "4. Exit"};
        iamp::print_menu("ELEC2645 Engineering Calculator", "Select a function:", menuItems);
        int input = iamp::user_input(4);

        if(input == 1) {
            //Inverting amplifier calculator entrypoint
            iamp::main_menu();
        }
        else if(input == 2) {
            //filter calculator entrypoint
            filter::main_menu();
        }
        else if(input == 3) {
            //Function 3 entrypoint
            menuItems = {" ", "1. Continue", "2. Return to Main menu"};
            iamp::print_menu("Resistor Colour Code Calculator", "Faisal Sajwani", menuItems);
            input = iamp::user_input(2);
            if(input == 1) {
                std::cout << "\n\n\nThe tool I planned working on was a resistor color-code calculator that would benefit users of resistor's in the engineering and science space.\n";
                std::cout << "Users would input the number of and the colour of bands on the resistor and the appropriate values are calculated.\n" ;
                std::cout << "The tool would minimise time needed to build circuits by making it easier to identify the appropriate resistor for the appropriate application.\n";
                std::cout << "In turn, this will also help reduce the risk of accidents, the consequences of choosing a wrong resistor can be hazardous.\n";
                std::cout << "The resistor color-code table, that is widely used and what I had hoped to replace, is a complex system that consists of 3 tables\n";
                std::cout << "containing 10 colours each representing different meanings and values depending on which band they are.\n";
                std::cout << "This leaves users prone to mistakes, especially to beginners and/or visually impaired individuals that can't quite differentiate between colours.\n";
                std::cout << "I was motivated to pursue this project because I have noticed when working with resistors, as a beginner,\n";
                std::cout << "the difficulty of quickly identifying tiny circuit parts with the correct values while still being careful and professional.\n";
            }
        }
        else {
            exit(1);
        }
    }
}
