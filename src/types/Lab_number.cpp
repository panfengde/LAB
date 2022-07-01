
#include "../LabTypes.h"
#include "./Base.h"
#include <iostream>
#include <string>
#include "./Base.h"
#include "../frame/frame.h"
#include "../global_vars/global_vars.h"

using namespace std;

Lab_Ptr &Lab_number::get(Lab_Ptr &attr)
{
    //std::cout << "number--" << v << std::endl;
    return property->look_variable_env(*attr);
};

Lab_number::Lab_number(std::string v)
{
    //std::cout << "number--" << v << std::endl;
    value = std::stoi(v);
};
Lab_number::Lab_number(long v)
{
    value = v;
};

Lab_number::~Lab_number(){
    //std::cout << "~Lab_number" << std::endl;
};