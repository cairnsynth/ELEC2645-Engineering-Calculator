//Including classes that I will need to use
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <math.h>
#include <fstream>

//Include header file
#include "inverting_amplifier.h"

//Defining global constants
#define PI 3.14159265359
#define LINELENGTH 50
#define SCREENHEIGHT 15

//Global variable declarations
enum Position{LEFT, CENTRE, RIGHT};             //lastchance, 25/06/2019, http://www.cplusplus.com/forum/general/256212/#msg1121565

std::list<std::string> emptyList = {};

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

namespace iamp {
    //Function to handle printing with centre justification, reference: lastchance, 25/06/2019, http://www.cplusplus.com/forum/general/256212/#msg1121565
    void print(Position pos, std::string s) {           
        int spaces = 0;                                             //Initialise spaces variable to 0

        switch (pos) {                                              //Switch statement for pos variable
            case CENTRE:                                            //If pos == CENTRE
                spaces = (LINELENGTH - s.size()) / 2;               //Calculates number of spaces to put before printing the string
                break;
        }
        if(spaces > 0) {                                            
            std::cout << std::string(spaces, ' ') << s << std::endl;//Print the correct number of spaces, then the string, then a new line
        }
    }

    //Function to handle printing of all menus
    void print_menu(std::string title, std::string body, std::list<std::string> items) {
        std::cout << std::string(5, '\n');                                               //Prints blank space between screens
        std::cout << std::string(LINELENGTH, '=') << std::endl;                          //Prints menu header
        print(CENTRE, title);                                                            //Prints menu title
        std::cout << std::string(LINELENGTH, '-') << std::endl;                          //Prints sub header
        print(CENTRE, body);                                                             //Prints body


        for(std::string item : items) {                                                  //Loop through all menu items
            print(CENTRE, item);                                                         //Prints menu item on new line
        }

        int remainingLines = (SCREENHEIGHT - 7) - items.size();                          // Calculates how many lines are remaining on the screen
        if(remainingLines > 0) std::cout << std::string(remainingLines, '\n');           //Prints a new line for each remaining line                      
        std::cout << std::string(LINELENGTH, '-') << std::endl;                          //Prints bottom sub header
    }

    //Function to handle printing a full page of text
    void print_page(std::string title, std::list<std::string> body) {
        std::cout << std::string(5, '\n');                                          //Prints 5 blank lines above page
        std::cout << std::string(LINELENGTH, '=') << std::endl;                     //Prints page header
        print(CENTRE, title);                                                       //Prints page title
        std::cout << std::string(LINELENGTH, '-') << std::endl;                     //Prints sub header

        for(std::string line : body) {                                              //Loops through each string in body array
            std::cout << line << std::endl;                                         //Prints the string then a new line
        }

        int remainingLines = (SCREENHEIGHT - 7) - body.size();                      // Calculates how many lines are remaining on the screen
        if(remainingLines > 0) std::cout << std::string(remainingLines, '\n');      //Prints a new line for each remaining line                      
        std::cout << std::string(LINELENGTH, '-') << std::endl;                     //Prints bottom page sub header
    }

    //Function to convert a string into a list of strings with set width, lcs, 29/06/2014, https://stackoverflow.com/questions/25022880/c-split-string-every-x-characters
    std::list<std::string> string_to_list(const std::string& str) {
        int numStrings = str.length() / LINELENGTH;                                 //Calculate the number of strings needed
        std::list<std::string> out;                                                 //Create list of strings

        for(auto i = 0; i < numStrings; i++) {                                      //Loop for the number of strings
            out.push_back(str.substr(i * LINELENGTH, LINELENGTH));                  //Get the substring and add it to the end of the list
        }

        if(str.length() % LINELENGTH != 0) {                                        //If there is an incomplete line at the end of the string
            out.push_back(str.substr(LINELENGTH * numStrings));                     //Add the remaining characters as a final list item
        }

        return out;                                                                 //Return the list
    }

    //Function to handle user input, takes in the range of options allows
    int user_input(int range) {
        std::string input;                                                          //String to contain the user input

        int int_input;                                                              //Int to contain the converted input

        while (1) {                                                                 //While loop to repeat until valid input is given
            std::cout << "ENTER VALUE:";
            std::cin >> input;                                                      //Gets terminal input

            try {                                                                   //Error handling to see if the input string can be converted to an integer
                int_input = stoi(input);
            } catch (std::invalid_argument) {                                       //If the above code fails, an error is output and input is requested again
                std::cout << "YOU MUST ENTER AN INTEGER!" << std::endl;
            }

            if (range == -1) {                                                      //if range == -1, there is no limit on the input, so it just returns the input integer
                if (int_input > 0) {                                                //the input must still be greater than 0
                    return int_input;
                } else {                                                            //prints warning if input is <= 0
                    std::cout << "INPUT MUST BE GREATER THAN 0" << std::endl;
                }
                
            } else {                                                                // if range != -1, the input must be between 0 and range
                if (int_input <= range && int_input >= 1) {                         //checks input is between 0 and range
                    return int_input;                                               //returns input
                }
                else {                                                              //If not, an error is printed
                    std::cout << "INPUT IS OUT OF RANGE!" << std::endl;
                }
            }
        }  
    }

    //Function to handle an input of any key
    void user_cont() {
        std::cout << "Press enter to continue...";                                  //Prints prompt
        std::cin.ignore();                                                          //Waits for enter to be pressed, regardless of what else is pressed
    }

    //Function to print the main menu for the inverting amplifier calculator
    void main_menu() {

        std::list<std::string> items = {"Luke Coles", " ", "201331120"};            //Creating list to be displayed on page
        print_menu("Inverting Amplifier Calculator", " ", items);                   //Printing the menu
        user_cont();                                                                //Wait for enter to be pressed

        supply_type_menu();                                                      //Call the next menu function

    }
    //Function to handle getting supply type data
    void supply_type_menu() {
        std::list<std::string> items = {"1. Single Supply", "2. Dual Supply"};      //Creating the list of menu options
        print_menu("1. Supply Type", "Choose whether you want to use a:", items);   //Printing the menu
        int input = user_input(2);                                                  //Get user input with a range 1-2

        switch(input) {                                                         
            case 1: g_isSingleSupply = true; break;                                 //If input is 1, set g_isSingleSupply to true
            case 2: g_isSingleSupply = false; break;                                //If input is 2, set g_isSingleSupply to false
        }

        supply_voltage_menu();                                                   //Call the next menu function
    }
    //Function to handle getting supply voltage data
    void supply_voltage_menu() {
        std::list<std::string> items = {"+Vs for single supply", "+Vs and -Vs for dual supply"};    //Create list of menu items
        print_menu("2. Supply Voltage", "Enter your intended supply voltage, in V", items);         //Print menu
        g_supplyVoltage = user_input(-1);                                           //Get user input for supply voltage, no range limit
        gain_menu();                                                             //Call the next menu function
    }
    //Function to handle getting gain data
    void gain_menu() {
        print_menu("3. Gain", "Enter how much gain you would like", emptyList);     //Print the menu, no menu items so uses emptyList
        g_gain = user_input(-1);                                                    //Get input for gain, no range limit
        input_z_menu();                                                          //Call the next menu function
    }
    //Function to handle getting input impedance data
    void input_z_menu() {
        print_menu("4. Input Impedance", "Enter the input impedance of your circuit", emptyList);   //Print the menu
        g_r1 = user_input(-1);                                                      //Get input impedance value, no range limit
        freq_menu();                                                             //Call the next menu function
    }
    //Function to handle getting minimum and maximum frequencies
    void freq_menu() {
        std::list<std::string> items = {"1. The MINMUM frequency", "2. The MAXIMUM frequency"};         //Create list for menu items
        print_menu("5. Input Signal Frequency", "Signal frequency is important, enter in Hz:", items);  //Print menu
        g_minFreq = user_input(-1);                                                 //Get input for minimum frequency, in hz
        g_maxFreq = user_input(-1);                                                 //Get input for maximum frequency, in hz
        calculations_main_menu();                                                //Call the next menu function
    }
    //Function to calculate component values and display them
    void calculations_main_menu() {
        g_r2 = calculate_r2(g_gain, g_r1);                                          //Calls function to calculate R2
        g_c1 = calculate_c1(g_r1, g_minFreq);                                       //Calls function to calculate C1

        g_r1Npv = to_npv(g_r1).first;                                               //Get the NPV rounded value of r1
        g_r2Npv = to_npv(g_r2).first;                                               //Get the NPV rounded value of R2
        g_c1Npv = to_npv(g_c1).first;                                               //Get the NPV rounded value of C1

        std::cout << std::fixed << std::setprecision(3);                            //Set the precision of the output to 3 dp

        std::list<std::string> items;                                               //Create item list
        if(g_isSingleSupply) {
            items = {"R1 : " + to_npv(g_r1).second, "R2 : " + to_npv(g_r2).second, "C1 : " + to_npv(g_c1).second, "C2 : " + to_npv(g_c1).second};   //Items to display if is single supply
        }
        else {
            items = {"R1 : " + to_npv(g_r1).second, "R2 : " + to_npv(g_r2).second, "C1 : " + to_npv(g_c1).second};                                  //Items to display if is dual supply
        }
        print_menu("Component Values", "These are the component values required:", items);  //Prints the menu
        user_cont();                                                                //Wait for enter to be pressed
        more_data();                                                             //Calls next menu function
    }
    //Function to give options for displaying more data
    void more_data() {
        std::list<std::string> items = {"1. View detailed calculations", "2. Save component values to .txt", "3. Generate Falstad circuit", "4. Generate example wave graph", "5. Compare Op-Amp suitability", "6. Move on"};   //Menu items list
        print_menu("More Data", "Choose an option to display more data:", items);   //Prints the menu
        int input = user_input(6);                                                  //Gets user input, range 1-6

        switch(input) {                                                             //Switch statement for different input options
            case 1: detailed_calculations();                                     //Each case calls the respective menu function
                break;
            case 2: save_to_text();
                break;
            case 3: generate_circuit();
                break;
            case 4: generate_wave();
                break;
            case 5: compare_opamp();
                break;
            default: move_on();
                break;
        }
    }
    //Function to view calculations in detail
    void detailed_calculations() {  
        std::cout << std::scientific;
        std::string bodyText1 = "The gain of the amplifier is calculated as G = R2/R1. As the gain and input impedance (R1) are fixed, we can use the product of these 2 variables to calculate R2:";   //String 1 to display in body
        std::string bodyText2 = "R2 = G * R1 = " + std::to_string(g_gain) + " * " + std::to_string(g_r1);                           //String 2 to display in body
        std::string bodyText3 = std::to_string(g_r2) + " = " + std::to_string(g_gain) + " * " + std::to_string(g_r1);               //String 3 to display in body
        std::string bodyText4 = "These calculations are using the raw values, not those rounded to the Nearest Preferable Value.";  //String 4 to display in body
        std::list<std::string> bodyList = string_to_list(bodyText1);                //Convert string 1 into a list
        bodyList.push_back(bodyText2);                                              //Add string 2 to the end
        bodyList.push_back(bodyText3);                                              //Add string 3 to the end
        bodyList.splice(bodyList.end(), string_to_list(bodyText4));                 //convert string 4 to a list and add to the end of the body list

        print_page("Detailed Calculations 1/2", bodyList);                          //Print the page with the body list 

        user_cont();                                                                //Wait for enter

        bodyText1 = "The AC coupling capacitance is calculated as C1 = 1 / (2 * PI * fMIN * R1). This creates a high-pass network between the capacitor and the virtual ground.";   //Body text as above
        bodyText2 = "C1 = 1 / (2 * PI * " + std::to_string(g_minFreq) + " * " + std::to_string(g_r1) + ")";
        bodyText3 = "C1 = " + to_npv(g_c1).second;
        bodyList = string_to_list(bodyText1);
        bodyList.push_back(bodyText2);
        bodyList.push_back(bodyText3);

        print_page("Detailed Calculations 2/2", bodyList);                          //Print second page of calculations

        user_cont();                                                                //Wait for enter
        more_data();                                                             //Call next menu function, returning to the more data page
    }
    //Function to save component values to a text file
    void save_to_text() {
        std::ofstream file;                                                         //Create stream object
        std::list<std::string> items = {"Enter a random input to save to resources:"};
        print_menu("Save Calculations to Text File", "Enter the filepath to create the file,", items);  //Print menu
        std::cout<< "ENTER PATH:";                                              //Prompt user input
        std::string path;
        std::cin >> path;

 /*       
        if(path.empty()){
            path = ".\\Resources\\Output\\Inverting Amplifier Components.txt";
        }                                                   //Store input in path
*/
        
        file.open(path + "/Inverting Amplifier Components.txt"); 

        if(!file.is_open()) { 
            std::cerr << "COULD NOT OPEN LOCATION, saving to Resources folder\n";                           //If not open print error message
            file.open(".\\Resources\\Output\\Inverting Amplifier Components.txt");                          //Save to resources folder             
        }
            
        


        if(g_isSingleSupply) {                                                      //Write text for a single supply amplifier to the file
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
        else {                                                                      //Write the text for a dual supply amplifier to the file
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

        file.close();                                                               //Close the file stream
        more_data();                                                             //Call the next menu function
    }
    //Function to generate a text file containing Falstad circuit code
    void generate_circuit() {
        std::ofstream file;                                                         //Create stream object
        std::list<std::string> items = {"Enter a random input to save to resources:"};
        print_menu("Generate Falstad Circuit", "Enter the filepath to create the file:", items);    //Prints menu

        std::cout<< "ENTER PATH:";                                              //Prompts user input
        std::string path;
        std::cin >> path;                                                       //Stores input in path
        file.open(path + "/Falstad Circuit.txt");                               //Opens file at given location

        if(!file.is_open()) {
            std::cerr << "COULD NOT OPEN LOCATION\n"; 
            file.open(".\\Resources\\Output\\Falstad Circuit.txt");             //If file is not open, saves to resources folder
        }
        

        if(g_isSingleSupply){                                                       //Writing data for single supply amplifier
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
        else {                                                                      //Writing data for dual supply amplifier
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
        file.close();                                                               //Closing file stream
        more_data();                                                             //Call the next menu function
    }
    //Function that takes an input .csv file and simulates the wave going through the amplifier
    void generate_wave() {
        std::string filePath;                                                       //Create stream object
        float amp;                                                                  //Declare amplitude variable
        std::list<std::string> items = {"1. Use preset wave-shape", "2. Load from user specified file"};    //Menu items    
        print_menu("Generate a Signal Graph", "Select the source of the input signal:", items);             //Print menu
        int input = user_input(2);                                                  //Get user input, range 1-2
        
        if(input == 2) {                                                            //If input is 2, get file path for custom wave and set amplitude to 1
            print_menu("Load Custom Input Wave", "Enter the filepath of your custom wave:", emptyList);
            std::cout << "ENTER PATH:";
            std::cin >> filePath;
            amp = 1;
        }
        else {                                                                      //If input is 1, display options for predefined waveshapes
            std::list<std::string> waveShapes = {"1. Sine", "2. Square"};   
            print_menu("Select a Wave-Shape", "Select from the predefined waves:", waveShapes);
            int input = user_input(2);
            
            if(input == 1) {
                filePath = ".\\Resources\\Waveshapes\\SINE_WAVE.csv";                           //If sine wave is selected, set path to SINE_WAVE.csv
            }
            else if(input == 2) {
                filePath = ".\\Resources\\Waveshapes\\SQUARE_WAVE.csv";                         //If square wave is selected, set path to SQUARE_WAVE.csv
            }
            else if(input == 3) {
    //            filePath = ".\\Resources\\Waveshapes\\TRIANGLE_WAVE.csv";
            }
            else if(input == 4) {
    //            filePath = ".\\Resources\\Waveshapes\\RAMP_UP_WAVE.csv";
            }
            else {
    //            filePath = ".\\Resources\\Waveshapes\\RAMP_DN_WAVE.csv";
            }                                   
            print_menu("Wave Amplitude", "Enter the peak amplitude of the wave, in V:", emptyList);     //Print menu for amplitude
            std::cout << "ENTER VALUE:";                            
            std::cin >> amp;                                                        //Store input in amplitude
        }
        items = {"Enter a random input to save to resources:"};
        print_menu("Save Location", "Enter the path of the output file:", items);   //Print menu
        std::cout << "ENTER PATH:";
        std::string outPath;
        std::cin >> outPath;                                                        //Store input in outPath variable

        generate_wave_file(g_gain, g_supplyVoltage, g_isSingleSupply, amp, filePath, outPath);      //Call function to generate the wave CSV file

        more_data();                                                             //Call the next menu function
    }
    //Function to compare different op amps suitability for the amplifier
    void compare_opamp() {
        print_menu("Op-Amp Comparison", "This feature is not yet implemented", emptyList);      //Did not have time to implement this
    }
    //Function that handles going back to the main menu or calculating a new op-amp
    void move_on() {
        std::list<std::string> items = {"1. Yes", "2. No"};                         //Menu items
        print_menu("Exit Screen", "Do you wish to calculate different values?", items);     //Print menu
        int input = user_input(2);                                                  //Get input, range 1-2

        switch (input) {
            case 1: main_menu();                                                 //If input is 1, go to the main menu of the op-amp calculator
                break;
            case 2:                                                             //If input is 2, go to calculator main menu
                break;
        }
    }

    //Function to calculate the value of R2
    float calculate_r2(float gain, float rIn) {
        float r2 = gain * rIn;                                                      //R1*Gain
        return r2;                                                                  //Returns R2
    }

    //Function to calculate C1
    float calculate_c1(float r1, float fMin) {
        float c1 = 1 / (2 * PI * fMin * r1);                                        // C1 = 1 / 2PI * fMin * R1
        return c1;                                                                  //Returns C1
    }

    std::pair<float, std::string> to_npv(float val) {
        float npv = 0;                                                              //Initialise npv variable to 0
        std::string prefix;                                                         //Declare string variable
        int divisions = 0;                                                          //Initialise divisions to 0
        if(val > 999) {                          
            while(val >= 10) {                                                      //Loops until input value is in range 1 - 10, dividing by 10 each time
                val /= 10;
                divisions++;                                                        //Increment divisions counter
            }
        }
        else if(val < 1) {                                  
            while(val < 1) {                                                        //If value<1, loops until value is in range 1 - 10, multiplying by 10 each time 
                val *= 10;
                divisions--;                                                        //Decrement divisions counter
            }
        }

        for(int i = 0; i < g_e12.size(); i++) {                                     //Loop through E12 series vector
            if(i == g_e12.size()) {
                return std::make_pair(val, "CONVERSION FAILED");                    //If the value is greater than 10, the division operation will have failed
            }
            else {
                if(val >= g_e12[i] && val < g_e12[i + 1]) {                         //If the value is between the current E12 series value and the next
                    float diff = g_e12[i + 1] - g_e12[i];                           //Calculates which vector item the value is closer to
                    float valDiff = val - g_e12[i];                                 

                    if(valDiff < (diff / 2)) {                                      
                        npv = g_e12[i];                                             //If value is closer to current E12 value, it is set to current E12 value
                    }
                    else {
                        npv = g_e12[i + 1];                                         //If not it is set the the next E12 value
                    }
                }
            }
        }

        float rawVal;                                                               //Declare rawVal to store the fixed form NPV value

        int subDiv = divisions / 3;                                                 //SI unit prefixes increase every x10^3
        int remainder = abs(divisions) % 3;                                         //How far between prefixes

        if(divisions > 0) {                                                         //If input value was greater than 1
            rawVal = npv * pow(10, abs(divisions));                                 //Get raw value, in non scientific form
            npv *= pow(10, remainder);                                              //Multiply by 10 / 100 so that it will display propperly with the prefix
        }
        else {                                                                      //If input value was less than 1
            rawVal = npv / pow(10, abs(divisions));                                 //Get raw value, in non scientific form
            npv /= pow(10, remainder);                                              //divide by 10 / 100 to display with prefix
        }

        prefix = siPrefixes[subDiv];                                                //Get prefix from map, using the sub division

        std::string outString = std::to_string(npv) + prefix;                       //Create output string  
        
        return std::make_pair(rawVal, outString);                                   //Returns pair containing raw value and output string
    }

    //Function to handle reading .CSV file and writing new file with amplified signal
    void generate_wave_file(float gain, float vSupply, bool isSingleSupply, float amp, std::string filePath, std::string outPath) {
        std::ifstream file;                                                         //Create stream object

        file.open(filePath);                                                        //Open file at filePath
        if(!file.is_open()){
            std::cerr << "ERROR: No input file found, using sine wave\n";                            //If opening fails, print error
            file.open(".\\Resources\\Waveshapes\\SINE_WAVE.csv");                  //Sets save location to resources folder
        }

        int n = 0;                                                                  //Initialise line counter to 0
        std::string temp;                                                           //Declare temporary string
        while(getline(file, temp)) {                                                //For each line in file, increment counter
            n++;
        }

        file.clear();                                                               //Clear flags
        file.seekg(0);                                                              //Reset position in file to line 1, https://stackoverflow.com/questions/5343173/returning-to-beginning-of-file-after-getline

        std::list<std::vector<double>> readList;                                    //Declare list to read file in to

        for (int i = 0; i < n; i++) {                                               //Loop through every line
            std::vector<double> tempV;                                              //Declare temporary vector
            double tempD;                                                           //Declare temporary double
            getline(file, temp, ',');                                               //Get first value on line
            tempD = std::stod(temp);                                                //Convert string to double and store in tempD
            tempV.push_back(tempD);                                                 //Add double to end of temporary vector
            getline(file, temp);                                                    //Get secondary value in line
            tempD = std::stod(temp);                                                //Convert to double and store in temD
            tempD *= amp;                                                           //Multiply by amplitude of input signal
            tempV.push_back(tempD);                                                 //Store result on end of vector
            readList.push_back(tempV);                                              //Add vector to end of readList
        }
        file.close();                                                               //Close the file stream

        //Writing to list
        std::list<std::vector<double>> outList;                                     //Declare list to store output lines


        for(std::vector<double> v : readList) {                                     //Loop through vectors(lines) in readList
            std::vector<double> tempV;                                              //Create temp vector

            double iAmp = v[1];                                                     //Input amplitude = second value
            double ampVal = iAmp * -gain;                                           //Apply negative gain
            if(isSingleSupply){
                if(ampVal > (vSupply / 2)) {                                        //Cap values at +-half supply voltage if single supply
                    ampVal = vSupply / 2;
                }
                else if(ampVal < -(vSupply / 2 )) {
                    ampVal = -(vSupply / 2);
                }
            }
            else{
                if(ampVal > vSupply) {                                              //Cap values at +-supply voltage if dual supply
                    ampVal = vSupply;
                }
                else if (ampVal < -vSupply) {
                    ampVal = -vSupply;
                }
            }
            
            tempV.push_back(v[0]);                                                  //Push time value (t) into temp vector
            tempV.push_back(v[1]);                                                  //Push input voltage into temp vector
            tempV.push_back(ampVal);                                                //Push output voltage into temp vector
            outList.push_back(tempV);                                               //Push temp vector onto end of output list
        }

        std::ofstream outFile;                                                      //Create stream object for writing the file

        outFile.open(outPath + "\\Generated Wave.csv");                             //Open file at given output path

        if(!outFile.is_open()){
            std::cerr << "ERROR CREATING FILE, saving to resources\n";              //Prints error and exits if file cannot be opened
            outFile.open(".\\Resources\\Output\\Generated Wave.csv");               //Saves to resources folder
        }

        outFile << "Time,Input,Output\n";                                           //Write column headings to output file

        for(std::vector<double> v : outList) {                                      //For each vector (line) in output list
            outFile << v[0] << "," << v[1] << "," << v[2] << std::endl;             //Write all 3 values, separated by commas, then new line
        }
        outFile.close();                                                            //Close the output file
    }  
} 