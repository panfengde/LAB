#ifndef UNDEFINED
#define UNDEFINED

#include "../LabTypes.h"
#include <iostream>
#include "./Base.h"
using namespace std;

class LabEle;
class Lab_undefined
{
public:
    LabTypes::LabTypes type = LabTypes::undefined_type;
    bool value = false;
    LabEle *container;
    Lab_undefined(){};
    ~Lab_undefined(){};
    void show(){
         std::cout << "undefined" << std::endl;
    };
};

#endif