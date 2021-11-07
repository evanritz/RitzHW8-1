// control_GPIO.cpp
// 
// This program takes 3 arguments
// This program sets pin to given state and reads another pin
// Displays read pin value
// arg1 = pin to set arg2 = state of pin arg3 = pin to read
// e.g control_GPIO 60 hi 46 
//
// setDir(0) = input
// setDir(1) = output
// setVal(0) = low
// setVal(1) = high
//
// Written by Evan
//

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

#define PATH "/sys/class/gpio/"

string make_path(string pin) {
    ostringstream s;
    s << PATH << "gpio" << pin << "/";
    return s.str();
}

int write(string path, string filename, string value){
   fstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("GPIO: write failed to open file ");
	   return -1;
   }
   fs << value;
   fs.close();
   return 0;
}

string read(string path, string filename){
   fstream fs;
   fs.open((path + filename).c_str());
   if (!fs.is_open()){
	   perror("GPIO: read failed to open file ");
    }
   string input;
   getline(fs,input);
   fs.close();
   return input;
}

void setDirection(int dir, string gpio_pin){
   switch(dir){
   case 0: 
        write(gpio_pin, "direction", "in");
        break;
   case 1:
        write(gpio_pin, "direction", "out");
        break;
   }
}

void setValue(int value, string gpio_pin) {
    
    write(gpio_pin, "value", to_string(value));
}

int getValue(string gpio_pin) {
    string output = read(gpio_pin, "value");
    if (output == "0")
        return 0;
    else
        return 1; 
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "control_GPIO program by Evan" << endl;
        cout << "arg1 = pin to set arg2 = state of pin arg3 = pin to read" << endl;
        cout << "e.g control_GPIO 60 hi 60" << endl;
        cout << "Sets pin 60 to high and reads pin 60 state" << endl;
        return -1;
    }

    string opin(argv[1]);
    string state(argv[2]);
    string ipin(argv[3]);

    string opin_path = make_path(opin);
    string ipin_path = make_path(ipin);

    setDirection(0, ipin_path);
    setDirection(1, opin_path);

    if (state == "hi") {
        setValue(1, opin_path);
    }
    else if (state == "low") {
        setValue(0, opin_path);
    }
    else {
        cout << "Invaild state entered" << endl;
        return -2;
    }

    cout << "Set GPIO pin " << opin << " to write" << endl;
    cout << "Set GPIO pin " << opin << " to state " << state << endl;
    cout << "Set GPIO pin " << ipin << " to read" << endl;
    cout << "Reading of GPIO pin " << ipin << " is " << getValue(ipin_path) << endl;
    
    return 0;
}
