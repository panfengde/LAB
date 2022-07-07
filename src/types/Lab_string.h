#ifndef STRING
#define STRING

#include "../LabTypes.h"
#include <iostream>
#include "./LabEle.h"

using namespace std;

class LabEle;

class Lab_string : public LabEle {
private:
    /* data */

public:
    std::string value;
    LabEle *container;

    Lab_string(std::string v);

    ~Lab_string();

    void show() {
        std::cout << value << std::endl;
    };

    string stringify();

    Lab_string *clone() {
        Lab_string *temp = new Lab_string(this->value);
        return temp;
    };
};

Lab_string::Lab_string(std::string v) {
    type = LabTypes::string_type;
    //std::cout << "Lab_string" << std::endl;
    value = v;
};

string Lab_string::stringify() {
    return "\"" + value + "\"";
};

Lab_string::~Lab_string() {};

#endif