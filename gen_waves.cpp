#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

float dT = 0.00001042;
float maxT = 0.005;

int main(){

}

void gen_triangle(float amp, float period) {
    float hPeriod = period / 2;
    float time = 0;

    float triVal = 0;

    while(time < maxT) {
        float sinVal = 1 * sin(6283.2 * time);
        
        if(sinVal > 0) {

        }
    }
}