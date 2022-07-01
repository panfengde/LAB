#ifndef VARIABLE
#define VARIABLE

#include "../LabTypes.h"
#include "./Base.h"
#include <iostream>
#include <string>
#include <map>

class Lab_variable
{
private:
    /* data */
public:
    std::string value;
    LabEle *container;
    LabTypes::LabTypes type = LabTypes::variable_type;
    Lab_variable(std::string _value)
    {
        //变量名称检测
        value = _value;
    };
    void show()
    {
        std::cout << value << std::endl;
    }
    ~Lab_variable();
};

Lab_variable::~Lab_variable(){};
#endif