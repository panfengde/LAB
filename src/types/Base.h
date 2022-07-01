#ifndef BASE
#define BASE

#include <iostream>
#include <vector>
#include <memory>
#include "../frame/frame.h"
#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "../global_vars/global_vars.h"

using namespace std;

class LabEle;
class Frame;

class Base
{
public:
    //存储那些可以在LAB中使用的方法和属性---
    shared_ptr<Frame> property;
    Base();
    ~Base();
    virtual Lab_Ptr &get(Lab_Ptr &);
};


#endif