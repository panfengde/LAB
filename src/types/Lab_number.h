#ifndef NUMBER
#define NUMBER

#include "../LabTypes.h"
#include <iostream>
#include <string>
#include "./LabEle.h"
#include "../frame/frame.h"
#include "../global_vars/global_vars.h"

using namespace std;

class LabEle;

class Lab_number : public LabEle
{
private:
    /* data */

public:
    // shared_ptr<Frame> number_prototype;
    long value;
    LabEle *container;
    Lab_number(std::string v);
    Lab_number(long v);
    Lab_number *clone()
    {
        Lab_number *temp = new Lab_number(this->value);
        return temp;
    };
    LabEle *get(LabEle *);
    //    void show()
    //    {
    //        std::cout << value << std::endl;
    //    }
    string stringify();
    ~Lab_number();
};

#endif