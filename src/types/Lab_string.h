#ifndef STRING
#define STRING

#include "../LabTypes.h"
#include <iostream>
#include "./Base.h"
using namespace std;

class LabEle;
class Lab_string: public Base
{
private:
    /* data */

public:
    LabTypes::LabTypes type = LabTypes::string_type;
    std::string value;
    LabEle *container;
    Lab_string(std::string v);
    ~Lab_string();
    void show()
    {
        std::cout << value << std::endl;
    };
    Lab_string *clone()
    {
        Lab_string *temp = new Lab_string(this->value);
        return temp;
    };
};

Lab_string::Lab_string(std::string v)
{
    //std::cout << "Lab_string" << std::endl;
    value = v;
};

Lab_string::~Lab_string(){};

#endif