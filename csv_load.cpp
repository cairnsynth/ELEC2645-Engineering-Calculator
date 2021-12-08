#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#define GAIN 40
#define V_SUPPLY 9

int count_lines();
std::list<std::vector<double>> read_to_list(int n);
std::list<std::vector<double>> generate_wave(std::list<std::vector<double>> iList, float gain, float vSupply);
void write_to_csv(std::list<std::vector<double>> iList);

void generate_amplified_wave(float gain, float vSupply);

int main(){
/*    int lines = count_lines();
    std::cout << lines << " counted\n";

    std::list<std::vector<double>> list = read_to_list(lines);
    
    std::list<std::vector<double>> ampList = generate_wave(list, GAIN, V_SUPPLY);

    for(std::vector<double> v : ampList) {
        for(double d : v) {
            std::cout << d << " , ";
        }
        std::cout << std::endl;
    }

    write_to_csv(ampList);
*/
    generate_amplified_wave(GAIN, V_SUPPLY);
}

int count_lines() {
    std::ifstream file;
    file.open("SINE_WAVE.csv");
    if(!file.is_open()){
        std::cerr << "ERROR: No input file found\n";
        exit(1);    
    }
    int n = 0;
    std::string temp;
    while(getline(file, temp)) {
        n++;
    }
    file.close();
    return n;
}

std::list<std::vector<double>> read_to_list(int n) {
    std::ifstream file;
    file.open("SINE_WAVE.csv");
    if(!file.is_open()){
        std::cerr << "CANNOT OPEN FILE";
        exit(1);
    }

    std::list<std::vector<double>> out;
    std::string temp;

    for (int i = 0; i < n; i++) {
        std::vector<double> tempV;
        double tempD;
        getline(file, temp, ',');
        tempD = std::stod(temp);
        tempV.push_back(tempD);
        getline(file, temp);
        tempD = std::stod(temp);
        tempV.push_back(tempD);
        out.push_back(tempV);
    }
    file.close();
    return out;
}

std::list<std::vector<double>> generate_wave(std::list<std::vector<double>> iList, float gain, float vSupply) {
    std::list<std::vector<double>> out;


    for(std::vector<double> v : iList) {
        std::vector<double> tempV;

        double iAmp = v[1];
        double ampVal = iAmp * -gain;
        if(ampVal > vSupply) {
            ampVal = vSupply;
        }
        else if (ampVal < -vSupply) {
            ampVal = -vSupply;
        }
        tempV.push_back(v[0]);
        tempV.push_back(v[1]);
        tempV.push_back(ampVal);
        out.push_back(tempV);

    }
    return out;
}

void write_to_csv(std::list<std::vector<double>> iList) {
    std::ofstream outFile;

    outFile.open("Generated Wave.csv");

    if(!outFile.is_open()){
        std::cerr << "ERROR CREATING FILE\n";
        exit(1);
    }

    outFile << "Time,Input,Output\n";

    for(std::vector<double> v : iList) {
        outFile << v[0] << "," << v[1] << "," << v[2] << std::endl;
    }
    outFile.close();
}

void generate_amplified_wave(float gain, float vSupply) {
    std::ifstream file;
    file.open("SINE_WAVE.csv");
    if(!file.is_open()){
        std::cerr << "ERROR: No input file found\n";
        exit(1);    
    }
    int n = 0;
    std::string temp;
    while(getline(file, temp)) {
        n++;
    }
    file.clear();
    file.seekg(0); //https://stackoverflow.com/questions/5343173/returning-to-beginning-of-file-after-getline

    std::list<std::vector<double>> readList;

    for (int i = 0; i < n; i++) {
        std::vector<double> tempV;
        double tempD;
        getline(file, temp, ',');
        tempD = std::stod(temp);
        tempV.push_back(tempD);
        getline(file, temp);
        tempD = std::stod(temp);
        tempV.push_back(tempD);
        readList.push_back(tempV);
    }
    file.close();

    std::list<std::vector<double>> outList;


    for(std::vector<double> v : readList) {
        std::vector<double> tempV;

        double iAmp = v[1];
        double ampVal = iAmp * -gain;
        if(ampVal > vSupply) {
            ampVal = vSupply;
        }
        else if (ampVal < -vSupply) {
            ampVal = -vSupply;
        }
        tempV.push_back(v[0]);
        tempV.push_back(v[1]);
        tempV.push_back(ampVal);
        outList.push_back(tempV);
    }

    std::ofstream outFile;

    outFile.open("Generated Wave.csv");

    if(!outFile.is_open()){
        std::cerr << "ERROR CREATING FILE\n";
        exit(1);
    }

    outFile << "Time,Input,Output\n";

    for(std::vector<double> v : outList) {
        outFile << v[0] << "," << v[1] << "," << v[2] << std::endl;
    }
    outFile.close();
}