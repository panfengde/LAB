#ifndef UNDEFINED
#define UNDEFINED

#include "../LabTypes.h"
#include <iostream>
#include "./LabEle.h"

using namespace std;

class LabEle;

class Lab_undefined : public LabEle {
public:
    bool value = false;
    LabEle *container;

    Lab_undefined() {};

    ~Lab_undefined() {};

    string stringify();

    void show() {
        std::cout << "undefined" << std::endl;
    };
};

string Lab_undefined::stringify() {
    return string("undefined");
};

#endif