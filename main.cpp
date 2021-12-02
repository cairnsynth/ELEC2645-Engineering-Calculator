//Including classes that I will need to use
#include <iostream>
#include <string>
#include <list>

//Defining global constants
#define PI 3.14159265359

//Function declarations
int print_menu(std::string title, std::list<std::string> items);
int user_input(int range);
void ia_main_menu();
float calculate_r2(float gain, float rIn);
float calculate_c1(float r1, float fMin);

//Global variable declarations
float g_gain;
float g_rIn;
bool g_isSingleSupply;
float g_supplyVoltage;
float g_minFreq;
float g_maxFreq;

//Main loop
int main() {
    ia_main_menu();
}

//Function to handle printing of all menus
int print_menu(std::string title, std::list<std::string> items){
    std::cout << title << std::endl;                               //Prints menu title

    for(std::string item : items) {                                //Loop through all menu items
        std::cout << item << std::endl;                            //Prints menu item on new line
    }

    int input = user_input(items.size);                            //Gets a user input with a range equal to the number of menu items
    return input;                                                  //Returns users input
}

//Function to handle user input, takes in the range of options allows
int user_input(int range) {
    std::string input;          //String to contain the user input

    int int_input;              //Int to contain the converted input

    while (1) {                         //While loop to repeat until valid input is given
        std::cout << "USER INPUT:";
        std::cin >> input;              //Gets terminal input

        try {                               //Error handling to see if the input string can be converted to an integer
            int_input = stoi(input);
        } catch (std::invalid_argument) {               //If the above code fails, an error is output and input is requested again
            std::cout << "YOU MUST ENTER AN INTEGER!" << std::endl;
        }

        if (range == -1) {                  //if range == -1, there is no limit on the input, so it just returns the input integer
            if (int_input > 0) {            //the input must still be greater than 0
                return int_input;
            } else {                        //prints warning if input is <= 0
                std::cout << "INPUT MUST BE GREATER THAN 0" << std::endl;
            }
            
        } else {                            // if range != -1, the input must be between 0 and range
            if (int_input <= range && int_input >= 1) {             //checks input is between 0 and range
                return int_input;                                   //returns input
            }
            else {                          //If not, an error is printed
                std::cout << "INPUT IS OUT OF RANGE!" << std::endl;
            }
        }
    }  
}

//Function to print the main menu for the inverting amplifier calculator
void ia_main_menu(){
    std::cout << "Inverting Op-Amp Calculator\n\n"; 
    
                 
}

//Function to calculate the value of R2
float calculate_r2(float gain, float rIn) {
    float r2 = gain * rIn;                          //R1*Gain
    return r2;                                      //Returns R2
}

//Function to calculate C1
float calculate_c1(float r1, float fMin) {
    float c1 = 1 / (2 * PI * fMin * r1);            // C1 = 1 / 2PI * fMin * R1
    return c1;                                      //Returns C1
}

