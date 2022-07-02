
#include "../LabTypes.h"
#include <iostream>
#include <string>
#include "../frame/frame.h"
#include "../global_vars/global_vars.h"

using namespace std;

LabEle *Lab_number::get(LabEle *attr)
{
    //std::cout << "number--" << v << std::endl;
    return property->look_variable_env(attr);
};

Lab_number::Lab_number(std::string v)
{
    type = LabTypes::number_type;
    //std::cout << "number--" << v << std::endl;
    value = std::stoi(v);
};

Lab_number::Lab_number(long v)
{
    type = LabTypes::number_type;
    value = v;
};

Lab_number::~Lab_number(){
    //std::cout << "~Lab_number" << std::endl;
};