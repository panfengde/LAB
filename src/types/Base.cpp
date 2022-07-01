
#include <iostream>
#include <vector>
#include <memory>
#include "../frame/frame.h"
#include "../LabTypes.h"
#include "../typeGlobal.h"
using namespace std;

Base::Base()
{
    property = base_prototype;
}
Lab_Ptr &Base::get(Lab_Ptr &attr)
{
    attr->show();
    //std::cout << "init---addName2-----------" << std::endl;
    //base_prototype->look_vars_frame(addName2).show();
    return property->look_variable_env(*attr);
}
Base::~Base()
{
}