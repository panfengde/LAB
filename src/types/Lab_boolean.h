#ifndef BOOL
#define BOOL

#include "../LabTypes.h"
#include "./LabEle.h"
#include <iostream>

using namespace std;


class Lab_boolean : public LabEle {
private:
    /* data */
public:
    LabTypes::LabTypes type = LabTypes::boolean_type;
    bool value;
    LabEle *container;

    Lab_boolean(bool v) : value(v) {};

    template<typename T>
    Lab_boolean(T v);

    ~Lab_boolean();

    void show() {
        std::cout << (value ? "true" : "false") << std::endl;
    }
};

template<typename T>
Lab_boolean::Lab_boolean(T oring) {
    if (oring == "" || oring == "0" || oring == "false") {
        value = false;
    } else {
        value = true;
    }
};

Lab_boolean::~Lab_boolean() {};

#endif