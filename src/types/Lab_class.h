#ifndef LABCLASS
#define LABCLASS

#include "./Base.h"
#include "../LabTypes.h"
#include <iostream>
#include <string>
#include <map>

class Lab_class : public Base
{
private:
    /* data */
public:
    std::string value = "[_class native code]";
    vector<Lab_Ptr> args;
    LabCallback analyze_constructor;
    shared_ptr<Frame> define_env;
    shared_ptr<Frame> prototype;
    LabEle *container;
    LabTypes::LabTypes type = LabTypes::class_type;
    Lab_class(shared_ptr<Frame>, shared_ptr<Frame>, vector<shared_ptr<LabEle>>, LabCallback);
    Lab_class(std::string _value){

    };
    void show()
    {
        std::cout << "object" << std::endl;
    }
    ~Lab_class(){};
};

#endif