//Required libraries for function declarations
#include <list>
#include <vector>
//Set the namespace so functions with the same name dont clash
namespace iamp {
    enum Position{LEFT, CENTRE, RIGHT};
    //Function declarations
    void print_menu(std::string title, std::string body, std::list<std::string> items);
    void print_page(std::string title, std::list<std::string> body);
    int user_input(int range);
    void user_cont();
    void print(Position pos, std::string s);
    std::list<std::string> string_to_list(const std::string& str);

    float calculate_r2(float gain, float rIn);
    float calculate_c1(float r1, float fMin);

    std::pair<float, std::string> to_npv(float val);

    void generate_wave_file(float gain, float vSupply, bool isSingleSupply, float amp, std::string filePath, std::string outPath);

    //Function declarations for each menu screen
    void main_menu();
    void supply_type_menu();
    void supply_voltage_menu();
    void gain_menu();
    void input_z_menu();
    void freq_menu();
    void calculations_main_menu();
    void more_data();
    void detailed_calculations();
    void save_to_text();
    void generate_circuit();
    void generate_wave();
    void compare_opamp();
    void move_on();
}