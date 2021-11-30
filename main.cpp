#include <iostream>
#include <string>
#include <list>

void print_menu(std::string _title, std::list<std::string> _items);
void ia_main_menu();
float calculate_r2(float _gain, float _rIn);

float g_gain;
float g_rIn;

int main() {
    std::cout << "Enter the amount of gain you want:";
    std::cin >> g_gain;
    std::cout << std::endl << "Enter the input impedance:";
    std::cin >> g_rIn;

    float r2 = calculate_r2(g_gain, g_rIn);
    std::cout << r2;
}

void print_menu(std::string _title, std::list<std::string> _items){
    std::cout << _title << std::endl;
    for(std::string item : _items) {
        std::cout << item << std::endl;
    }
}

void ia_main_menu(){
    std::cout << "------ Inverting Op-Amp Calculator\n\n";
    std::list<std::string> menu = {"Yes, run on a single supply", "Nooo"};
    print_menu("First select whether the op-amp should run on a single supply voltage or not:", menu);

}

float calculate_r2(float gain_, float rIn_) {
    float r2 = gain_ * rIn_;
    return r2;
}
