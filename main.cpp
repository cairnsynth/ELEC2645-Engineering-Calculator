//Including classes that I will need to use
#include <iostream>
#include <string>
#include <list>

//Defining global constants
#define PI 3.14159265359
#define LINELENGTH 40
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

//Function declarations
void print_menu(std::string title, std::string body, std::list<std::string> items);
int user_input(int range);
void start_page();
void end_page();

void ia_main_menu();
void ia_supply_type_menu();
void ia_supply_voltage_menu();
void ia_gain_menu();
void ia_input_z_menu();
void ia_freq_menu();
void ia_calculations_main_menu();

float calculate_r2(float gain, float rIn);
float calculate_c1(float r1, float fMin);

void print(Position pos, std::string s);

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
        case RIGHT:
            spaces = LINELENGTH - s.size();
            break;
    }
    if(spaces > 0) {
        std::cout << std::string(spaces, ' ') << s << std::endl;
    }
}

//Function to handle printing of all menus
void print_menu(std::string title, std::string body, std::list<std::string> items) {
    std::cout << std::string(5, '\n');                              //Prints blank space between screens
    std::cout << std::string(LINELENGTH, '=') << std::endl;         //Prints menu header
    print(CENTRE, title);                                         //Prints menu title
    std::cout << std::string(LINELENGTH, '-') << std::endl;                      //Prints sub header
    print(CENTRE, body);                                            //Prints body


    for(std::string item : items) {                                //Loop through all menu items
        print(CENTRE, item);                                      //Prints menu item on new line
    }

    int remainingLines = (SCREENHEIGHT - 7) - items.size();        // Calculates how many lines are remaining on the screen
    std::cout << std::string(remainingLines, '\n');                 //Prints a new line for each remaining line

    std::cout << std::string(LINELENGTH, '-') << std::endl;  
}

//Function to handle user input, takes in the range of options allows
int user_input(int range) {
    std::string input;          //String to contain the user input

    int int_input;              //Int to contain the converted input

    while (1) {                         //While loop to repeat until valid input is given
        print(LEFT, "ENTER VALUE:");
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

//Function that "clears" the screen and prints the upper page border
void start_page() {
    for(int i = 0; i < 5; i++) {
        std::cout << std::endl;
    }
    std::cout << "------------------------------------------------------------------------\n\n";
}

//Function that prints the lower page border
void end_page() {
    std::cout << "------------------------------------------------------------------------";
}

//Function to print the main menu for the inverting amplifier calculator
void ia_main_menu() {
 /*   
    start_page();

    std::cout << "Inverting Op-Amp Calculator\n\n"; 
    std::cout << "This section of the engineering calculator will produce component values and circuit diagrams for inverting amplifiers.\n\n";

    std::list<std::string> menu = {"1. Yes, I want to use a single supply voltage", "2. No, have a positive and negative voltage"};
    int input = print_menu("First, select whether you want to use a single supply voltage or not:", menu);

    switch(input) {
        case 1:
            g_isSingleSupply = true;
            break;
        default:
            g_isSingleSupply = false;
            break;
    }

    end_page();
    ia_supply_voltage_menu();
*/
    std::list<std::string> items = {"Luke Coles", "201331120", " ", "Press 1 to continue"};
    print_menu("Inverting Amplifier Calculator", " ", items);
    int input = user_input(1);

    switch(input) {
        case 1: ia_supply_type_menu(); break;
    }

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
    start_page();

    int input;
    if (g_isSingleSupply) {
        std::cout << "Enter your desired value for +VS int volts:\n";
        input = user_input(-1);
        std::cout << "\n+VS will be equal to " << input << "V\n";
    }
    else {
        std::cout << "Enter your desired value for +VS and -VS int volts, note these will be equal:\n";
        input = user_input(-1);
        std::cout << "\n+VS will be " << input << "V, -VS will be -" << input << "V\n";
    }

    end_page();
    ia_gain_menu();
}

void ia_gain_menu() {
    start_page();
    std::cout << "Enter how much gain you would like the amplifier to have:";
    g_gain = user_input(-1);

    end_page();
    ia_input_z_menu();
}

void ia_input_z_menu() {
    start_page();

    std::cout << "Now, enter your desired value for the input impedance of the circuit, in Ohms:\n";
    g_r1 = user_input(-1);
    std::cout << "\nThe input impedance of the amplifier will be " << g_r1 << std::endl;

    end_page();
    ia_freq_menu();
}

void ia_freq_menu() {
    start_page();

    std::cout << "The frequency range of the input signal is important to know when calculating the AC coupling capacitor value and any gain error that may occur.";
    std::cout << "Enter the MINIMUM frequency of the input signal in Hertz:\n";
    g_minFreq = user_input(-1);
    std::cout << "\nNow enter the MAXIMUM frequency in Hertz:\n";
    g_maxFreq = user_input(-1);
    std::cout << "\n\nSo the input signal frequency will range from " << g_minFreq << "Hz to " << g_maxFreq << "Hz.\n";

    end_page();
    ia_calculations_main_menu();
}

void ia_calculations_main_menu() {
    g_r2 = calculate_r2(g_gain, g_r1);
    g_c1 = calculate_c1(g_r1, g_minFreq);

    std::cout << g_gain << std::endl << g_r1 << std::endl << g_r2 << std::endl << g_c1 << std::endl;
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

