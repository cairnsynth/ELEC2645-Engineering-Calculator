//Including classes that I will need to use
#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>

//Defining global constants
#define PI 3.14159265359
#define LINELENGTH 50
#define SCREENHEIGHT 15

//Global variable declarations
enum Position{LEFT, CENTRE, RIGHT};             //lastchance, 25/06/2019, http://www.cplusplus.com/forum/general/256212/#msg1121565

float g_gain;
float g_r1;
float g_r2;
float g_c1;
bool g_isSingleSupply;
float g_supplyVoltage;
float g_minFreq;
float g_maxFreq;
std::vector<float> g_e12  = {1, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2, 10};
std::map<float, std::string> siPrefixes{{-8, "y"}, {-7, "z"}, {-6, "a"}, {-5, "f"}, {-4, "p"}, {-3, "n"}, {-2, "u"}, {-1, "m"}, {0, ""},{1, "k"},{2, "M"},{3, "G"},{4, "T"},{5, "P"},{6, "E"},{7, "Z"},{8, "Y"}};

//Function declarations
void print_menu(std::string title, std::string body, std::list<std::string> items);
int user_input(int range);
void user_cont();
void print(Position pos, std::string s);

//Function declarations for each menu screen
void ia_main_menu();
void ia_supply_type_menu();
void ia_supply_voltage_menu();
void ia_gain_menu();
void ia_input_z_menu();
void ia_freq_menu();
void ia_calculations_main_menu();
void ia_more_data();

float calculate_r2(float gain, float rIn);
float calculate_c1(float r1, float fMin);

std::pair<float, std::string> to_npv(float val);



//Main loop
int main() {
    ia_main_menu();
}
//Function to handle printing with centre justification, reference: lastchance, 25/06/2019, http://www.cplusplus.com/forum/general/256212/#msg1121565
void print(Position pos, std::string s) {           
    int spaces = 0;

    switch (pos) {
        case CENTRE: 
            spaces = (LINELENGTH - s.size()) / 2;
            break;
    }
    if(spaces > 0) {
        std::cout << std::string(spaces, ' ') << s << std::endl;
    }
}

//Function to handle printing of all menus
void print_menu(std::string title, std::string body, std::list<std::string> items) {
    std::cout << std::string(5, '\n');                                              //Prints blank space between screens
    std::cout << std::string(LINELENGTH, '=') << std::endl;                        //Prints menu header
    print(CENTRE, title);                                                            //Prints menu title
    std::cout << std::string(LINELENGTH, '-') << std::endl;                      //Prints sub header
    print(CENTRE, body);                                                          //Prints body


    for(std::string item : items) {                                              //Loop through all menu items
        print(CENTRE, item);                                                      //Prints menu item on new line
    }

    int remainingLines = (SCREENHEIGHT - 7) - items.size();                        // Calculates how many lines are remaining on the screen
    std::cout << std::string(remainingLines, '\n');                                //Prints a new line for each remaining line

    std::cout << std::string(LINELENGTH, '-') << std::endl;  
}

//Function to handle user input, takes in the range of options allows
int user_input(int range) {
    std::string input;          //String to contain the user input

    int int_input;              //Int to contain the converted input

    while (1) {                         //While loop to repeat until valid input is given
        std::cout << "ENTER VALUE:";
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

//Function to handle an input of any key
void user_cont() {
    std::cout << "Press enter to continue...";
    std::cin.ignore();
}

//Function to print the main menu for the inverting amplifier calculator
void ia_main_menu() {

    std::list<std::string> items = {"Luke Coles", " ", "201331120"};
    print_menu("Inverting Amplifier Calculator", " ", items);
    user_cont();

    ia_supply_type_menu();

}

void ia_supply_type_menu() {
    std::list<std::string> items = {"1. Single Supply", "2. Dual Supply"};
    print_menu("1. Supply Type", "Choose whether you want to use a:", items);
    int input = user_input(2);

    switch(input) {
        case 1: g_isSingleSupply = true; break;
        case 2: g_isSingleSupply = false; break;
    }

    ia_supply_voltage_menu();
}

void ia_supply_voltage_menu() {
    std::list<std::string> items = {"+Vs for single supply", "+Vs and -Vs for dual supply"};
    print_menu("2. Supply Voltage", "Enter your intended supply voltage, in V", items);
    g_supplyVoltage = user_input(-1);
    ia_gain_menu();
}

void ia_gain_menu() {
    std::list<std::string> items = {};
    print_menu("3. Gain", "Enter how much gain you would like", items);
    g_gain = user_input(-1);
    ia_input_z_menu();
}

void ia_input_z_menu() {
    std::list<std::string> items = {};
    print_menu("4. Input Impedance", "Enter the input impedance of your circuit", items);
    g_r1 = user_input(-1);
    ia_freq_menu();
}

void ia_freq_menu() {
    std::list<std::string> items = {"1. The MINMUM frequency", "2. The MAXIMUM frequency"};
    print_menu("5. Input Signal Frequency", "Signal frequency is important, enter in Hz:", items);
    g_minFreq = user_input(-1);
    g_maxFreq = user_input(-1);
    ia_calculations_main_menu();
}

//Function to calculate component values and display them
void ia_calculations_main_menu() {
    g_r2 = calculate_r2(g_gain, g_r1);
    g_c1 = calculate_c1(g_r1, g_minFreq);
    std::cout << g_c1;
    std::list<std::string> items;
    if(g_isSingleSupply) {
        items = {"R1 : " + to_npv(g_r1).second, "R2 : " + to_npv(g_r2).second, "C1 : " + to_npv(g_c1).second, "C2 : " + to_npv(g_c1).second};
    }
    else {
        items = {"R1 : " + to_npv(g_r1).second, "R2 : " + to_npv(g_r2).second, "C1 : " + to_npv(g_c1).second};
    }
    print_menu("Component Values", "These are the component values required:", items);
    user_cont();
    ia_more_data();
}

void ia_more_data() {

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

std::pair<float, std::string> to_npv(float val) {
    float npv = 0;
    std::string prefix;
    int divisions = 0;
    if(val > 999) {
        while(val >= 10) {
            val /= 10;
            divisions++;
        }
    }
    else if(val < 1) {
        while(val < 1) {
            val *= 10;
            divisions--;
        }
    }

    for(int i = 0; i < g_e12.size(); i++) {
        if(i == g_e12.size()) {
            return std::make_pair(val, "CONVERSION FAILED");
        }
        else {
            if(val >= g_e12[i] && val < g_e12[i + 1]) {
                float diff = g_e12[i + 1] - g_e12[i];
                float valDiff = val - g_e12[i];

                if(valDiff < (diff / 2)) {
                    npv = g_e12[i];
                }
                else {
                    npv = g_e12[i + 1];
                }
            }
        }
    }

    float rawVal;

    int subDiv = divisions / 3;
    int remainder = abs(divisions) % 3;

    if(divisions > 0) {
        npv *= pow(10, remainder);
        rawVal = npv * pow(10, divisions);
    }
    else {
        npv /= pow(10, remainder);
        rawVal = npv / pow(10, divisions);
    }

    prefix = siPrefixes[subDiv];

    std::string outString = std::to_string(npv) + prefix;
    std::cout << outString;
    
    return std::make_pair(rawVal, outString);
}
