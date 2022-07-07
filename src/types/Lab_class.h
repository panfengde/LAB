#ifndef LABCLASS
#define LABCLASS

#include "./LabEle.h"
#include "../LabTypes.h"
#include <iostream>
#include <string>
#include <map>

class Lab_class : public LabEle
{
private:
    /* data */
public:
    std::string value = "[_class native code]";
    vector<Lab_Ptr> args;
    LabCallback analyze_constructor;
    Frame *define_env;
    Frame *prototype;
    LabEle *container;
    Lab_class(Frame *, Frame *, vector<LabEle *>, LabCallback);
    Lab_class(std::string _value)
    {
        type = LabTypes::class_type;
    };
    void show()
    {
        std::cout << "object" << std::endl;
    }
    ~Lab_class(){};
};

#endif