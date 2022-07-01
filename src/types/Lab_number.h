#ifndef NUMBER
#define NUMBER

#include "../LabTypes.h"
#include "./Base.h"
#include <iostream>
#include <string>
#include "./Base.h"
#include "../frame/frame.h"
#include "../global_vars/global_vars.h"

using namespace std;

class LabEle;

class Lab_number : public Base
{
private:
    /* data */

public:
    // shared_ptr<Frame> number_prototype;
    shared_ptr<Frame> property = number_prototype;
    LabTypes::LabTypes type = LabTypes::number_type;
    long value;
    LabEle *container;
    Lab_number(std::string v);
    Lab_number(long v);
    Lab_number *clone()
    {
        Lab_number *temp = new Lab_number(this->value);
        return temp;
    };
    Lab_Ptr &get(Lab_Ptr &);
    void show()
    {
        std::cout << value << std::endl;
    }
    string stringify();
    ~Lab_number();
};

#endif