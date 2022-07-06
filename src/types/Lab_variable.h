#ifndef VARIABLE
#define VARIABLE

#include "../LabTypes.h"
#include "./LabEle.h"
#include <iostream>
#include <string>
#include <map>

class Lab_variable : public LabEle {
private:
    /* data */
public:
    std::string value;
    LabEle *container;

    Lab_variable(std::string _value) {
        type = LabTypes::variable_type;
        //变量名称检测
        value = _value;
    };

    void show() {
        std::cout << value << std::endl;
    }

    string stringify();

    ~Lab_variable();
};

string Lab_variable::stringify() {
    return string(value);
};

Lab_variable::~Lab_variable() {};
#endif