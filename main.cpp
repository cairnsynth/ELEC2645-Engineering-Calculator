//Including classes that I will need to use
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <math.h>
#include <fstream>

//Defining global constants
#define PI 3.14159265359
#define LINELENGTH 50
#define SCREENHEIGHT 15

//Global variable declarations
enum Position{LEFT, CENTRE, RIGHT};             //lastchance, 25/06/2019, http://www.cplusplus.com/forum/general/256212/#msg1121565

float g_gain;
float g_r1;
float g_r1Npv;
float g_r2;
float g_r2Npv;
float g_c1;
float g_c1Npv;
bool g_isSingleSupply;
float g_supplyVoltage;
float g_minFreq;
float g_maxFreq;
std::vector<float> g_e12  = {1, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2, 10};
std::map<float, std::string> siPrefixes{{-8, "y"}, {-7, "z"}, {-6, "a"}, {-5, "f"}, {-4, "p"}, {-3, "n"}, {-2, "u"}, {-1, "m"}, {0, ""},{1, "k"},{2, "M"},{3, "G"},{4, "T"},{5, "P"},{6, "E"},{7, "Z"},{8, "Y"}};

//Function declarations
void print_menu(std::string title, std::string body, std::list<std::string> items);
void print_page(std::string title, std::list<std::string> body);
int user_input(int range);
void user_cont();
void print(Position pos, std::string s);
std::list<std::string> string_to_list(const std::string& str);

//Function declarations for each menu screen
void ia_main_menu();
void ia_supply_type_menu();
void ia_supply_voltage_menu();
void ia_gain_menu();
void ia_input_z_menu();
void ia_freq_menu();
void ia_calculations_main_menu();
void ia_more_data();
void ia_detailed_calculations();
void ia_save_to_text();
void ia_generate_circuit();
void ia_generate_wave();
void ia_compare_opamp();
void ia_move_on();

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

    int remainingLines = (SCREENHEIGHT - 7) - items.size();                     // Calculates how many lines are remaining on the screen
    if(remainingLines > 0) std::cout << std::string(remainingLines, '\n');      //Prints a new line for each remaining line                      
    std::cout << std::string(LINELENGTH, '-') << std::endl;  
}

void print_page(std::string title, std::list<std::string> body) {
    std::cout << std::string(5, '\n');
    std::cout << std::string(LINELENGTH, '=') << std::endl;
    print(CENTRE, title);
    std::cout << std::string(LINELENGTH, '-') << std::endl;

    for(std::string line : body) {
        std::cout << line << std::endl;
    }

    int remainingLines = (SCREENHEIGHT - 7) - body.size();                     // Calculates how many lines are remaining on the screen
    if(remainingLines > 0) std::cout << std::string(remainingLines, '\n');      //Prints a new line for each remaining line                      
    std::cout << std::string(LINELENGTH, '-') << std::endl; 
}

std::list<std::string> string_to_list(const std::string& str) {
    int numStrings = str.length() / LINELENGTH;
    std::list<std::string> out;

    for(auto i = 0; i < numStrings; i++) {
        out.push_back(str.substr(i * LINELENGTH, LINELENGTH));
    }

    if(str.length() % LINELENGTH != 0) {
        out.push_back(str.substr(LINELENGTH * numStrings));
    }

    return out;
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
//Function to handle getting supply type data
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
//Function to handle getting supply voltage data
void ia_supply_voltage_menu() {
    std::list<std::string> items = {"+Vs for single supply", "+Vs and -Vs for dual supply"};
    print_menu("2. Supply Voltage", "Enter your intended supply voltage, in V", items);
    g_supplyVoltage = user_input(-1);
    ia_gain_menu();
}
//Function to handle getting gain data
void ia_gain_menu() {
    std::list<std::string> items = {};
    print_menu("3. Gain", "Enter how much gain you would like", items);
    g_gain = user_input(-1);
    ia_input_z_menu();
}
//Function to handle getting input impedance data
void ia_input_z_menu() {
    std::list<std::string> items = {};
    print_menu("4. Input Impedance", "Enter the input impedance of your circuit", items);
    g_r1 = user_input(-1);
    ia_freq_menu();
}
//Function to handle getting minimum and maximum frequencies
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

    g_r1Npv = to_npv(g_r1).first;
    g_r2Npv = to_npv(g_r2).first;
    g_c1Npv = to_npv(g_c1).first;

    std::cout << std::fixed << std::setprecision(3);

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
//Function to give options for displaying more data
void ia_more_data() {
    std::list<std::string> items = {"1. View detailed calculations", "2. Save component values to .txt", "3. Generate Falstad circuit", "4. Generate example wave graph", "5. Compare Op-Amp suitability", "6. Move on"};
    print_menu("More Data", "Choose an option to display more data:", items);
    int input = user_input(6);

    switch(input) {
        case 1: ia_detailed_calculations();
            break;
        case 2: ia_save_to_text();
            break;
        case 3: ia_generate_circuit();
            break;
        case 4: ia_generate_wave();
            break;
        case 5: ia_compare_opamp();
            break;
        default: ia_move_on();
            break;
    }
}
//Function to view calculations in detail
void ia_detailed_calculations() {
    std::string bodyText1 = "The gain of the amplifier is calculated as G = R2/R1. As the gain and input impedance (R1) are fixed, we can use the product of these 2 variables to calculate R2:";
    std::string bodyText2 = "R2 = G * R1 = " + std::to_string(g_gain) + " * " + std::to_string(g_r1);
    std::string bodyText3 = std::to_string(g_r2) + " = " + std::to_string(g_gain) + " * " + std::to_string(g_r1);
    std::string bodyText4 = "These calculations are using the raw values, not those rounded to the Nearest Preferable Value.";
    std::list<std::string> bodyList = string_to_list(bodyText1);
    bodyList.push_back(bodyText2);
    bodyList.push_back(bodyText3);
    bodyList.splice(bodyList.end(), string_to_list(bodyText4));

    print_page("Detailed Calculations 1/2", bodyList);

    user_cont();

    bodyText1 = "The AC coupling capacitance is calculated as C1 = 1 / (2 * PI * fMIN * R1). This creates a high-pass network between the capacitor and the virtual ground.";
    bodyText2 = "C1 = 1 / (2 * PI * " + std::to_string(g_minFreq) + " * " + std::to_string(g_r1) + ")";
    bodyText3 = "C1 = " + std::to_string(g_c1);
    bodyList = string_to_list(bodyText1);
    bodyList.push_back(bodyText2);
    bodyList.push_back(bodyText3);

    print_page("Detailed Calculations 2/2", bodyList);
}
//Function to save component values to a text file
void ia_save_to_text() {
    std::ofstream file;

    std::list<std::string> items = {};
    print_menu("Save Calculations to Text File", "Enter the filepath to create the file:", items);
    while(1){
        std::cout<< "ENTER PATH:";
        std::string path;
        std::cin >> path;
        file.open(path + "/Inverting Amplifier Components.txt");

        if(file.is_open()) {
            break;
        }
        else {
            std::cout << "COULD NOT OPEN LOCATION\n";
        }
    }

    if(g_isSingleSupply) {
        file << "Single-Supply Inverting Amplifier Parameters:\n\n";
        file << "Gain = " << std::fixed << std::setprecision(3) << g_gain << std::endl;
        file << "Input Impedance = " << to_npv(g_r1).second << " Ohms\n";
        file << "Supply Voltage = " << g_supplyVoltage << " V\n";
        file << "Operating Frequency = " << g_minFreq << " Hz to " << g_maxFreq << " Hz\n\n";
        file << "Calculated Component Values:\n\n";
        file << "R1 = " << to_npv(g_r1).second << " Ohms\n";
        file << "R2 = " << to_npv(g_r2).second << " Ohms\n";
        file << "C1 = " << to_npv(g_c1).second << " F\n";
        file << "C2 = " << to_npv(g_c1).second << " F\n";
        file << "RA = 100k Ohms\n";
        file << "RB = 100k Ohms\n";
    }
    else {
        file << "Dual-Supply Inverting Amplifier Parameters:\n\n";
        file << "Gain = " << std::fixed << std::setprecision(3) << g_gain << std::endl;
        file << "Input Impedance = " << to_npv(g_r1).second << " Ohms\n";
        file << "Supply Voltages: \n";
        file << "\t+Vs = " << g_supplyVoltage << " V\n";
        file << "\t-Vs = " << g_supplyVoltage << " V\n";
        file << "Operating Frequency = " << g_minFreq << " Hz to " << g_maxFreq << " Hz\n\n";
        file << "Calculated Component Values:\n\n";
        file << "R1 = " << to_npv(g_r1).second << " Ohms\n";
        file << "R2 = " << to_npv(g_r2).second << " Ohms\n";
        file << "C1 = " << to_npv(g_c1).second << " F\n";
    }

    file.close();
    ia_more_data();
}
//Function to generate a text file containing Falstad circuit code
void ia_generate_circuit() {
    std::ofstream file;

    std::list<std::string> items = {};
    print_menu("Generate Falstad Circuit", "Enter the filepath to create the file:", items);
    while(1){
        std::cout<< "ENTER PATH:";
        std::string path;
        std::cin >> path;
        file.open(path + "/Falstad Circuit.txt");

        if(file.is_open()) {
            break;
        }
        else {
            std::cout << "COULD NOT OPEN LOCATION\n";
        }
    }

    if(g_isSingleSupply){
        file << "$ 1 0.000005 10.20027730826997 50 5 43 5e-11\n";
        file << "a 240 208 384 208 8 " << std::fixed << std::setprecision(24) << g_supplyVoltage << " " << 0 << " 1000000 0 0 100000\n";
        file << "r 240 128 384 128 0 " << g_r2Npv << "\n";          //R2
        file << "r 160 192 240 192 0 " << g_r1Npv << "\n";          //R1
        file << "w 240 128 240 192 0\n";
        file << "w 384 128 384 208 0\n";
        file << "c 96 192 160 192 0 " << g_c1Npv << " 0 0.001\n";   //C1
        file << "207 448 208 480 208 4 VOUT\n";
        file << "c 384 208 448 208 320 0 " << g_c1Npv << " 0 0.001\n";  //C2
        file << "r 208 240 208 320 0 100000\n";                     //RA
        file << "r 208 320 208 400 0 100000\n";                     //RB
        file << "w 240 320 208 320 0\n";
        file << "207 208 240 176 240 4 +VS\n";
        file << "g 208 400 208 416 0 0\n";
        file << "w 240 224 240 320 0";
    }
    else {
        file << "$ 1 0.000005 10.20027730826997 50 5 43 5e-11\n";
        file << "a 240 208 384 208 8 " << g_supplyVoltage << " " << -g_supplyVoltage << " 1000000 0 0 100000\n";
        file << "r 240 128 384 128 0 " << std::fixed << std::setprecision(24) << g_r2Npv << "\n";          //R2
        file << "r 160 192 240 192 0 " << g_r1Npv << "\n";          //R1
        file << "w 240 128 240 192 0\n";
        file << "w 384 128 384 208 0\n";
        file << "c 96 192 160 192 0 " << g_c1Npv << " 0 0.001\n";   //C1
        file << "w 384 208 448 208 0\n";
        file << "207 448 208 480 208 4 VOUT\n";
        file << "w 240 224 240 272 0\n";
        file << "g 240 272 240 304 0 0\n";
        file << "207 96 192 48 192 4 VIN";
    }
    file.close();
    ia_more_data();
}
//Function that takes an input .csv file and simulates the wave going through the amplifier
void ia_generate_wave() {

}

void ia_compare_opamp() {

}

void ia_move_on() {
    std::list<std::string> items = {"1. Yes", "2. No"};
    print_menu("Exit Screen", "Do you wish to calculate different values?", items);
    int input = user_input(2);

    switch (input) {
        case 1: ia_main_menu();
            break;
        case 2: //Go to calculator main menu
            break;
    }
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
        rawVal = npv * pow(10, abs(divisions));
        npv *= pow(10, remainder);
    }
    else {
        rawVal = npv / pow(10, abs(divisions));
        npv /= pow(10, remainder);
    }

    prefix = siPrefixes[subDiv];

    std::string outString = std::to_string(npv) + prefix;
    
    return std::make_pair(rawVal, outString);
}
