#ifndef LABFUNCTION
#define LABFUNCTION

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "./Base.h"
#include "../LabTypes.h"
#include "../typeGlobal.h"
//#include "../frame/frame.h"

using namespace std;

class LabEle;
class Frame;

class Lab_function : public Base
{

public:
    LabTypes::LabTypes type = LabTypes::function_type;
    std::string value = "[lambda native code]";
    funType funType = funType::original;
    LabEle *container;
    Lab_function();
    Lab_function(originalFn);
    Lab_function(vector<Lab_Ptr>, LabCallback, shared_ptr<Frame>);
    Lab_function(macroCallBack);
    originalFn original_fn;

    ~Lab_function();
    void show()
    {
        std::cout << value << std::endl;
    }
    vector<Lab_Ptr> args;
    LabCallback ananlyzed_body;
    macroCallBack macroCallBackBody;
    shared_ptr<Frame> define_env;
    shared_ptr<Frame> _this;
};

#endif