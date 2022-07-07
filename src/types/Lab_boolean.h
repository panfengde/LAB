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
    bool value;
    LabEle *container;

    Lab_boolean(bool v) : value(v) {
        type = LabTypes::boolean_type;
    };

    template<typename T>
    Lab_boolean(T v);

    ~Lab_boolean();

    string stringify();

    void show() {
        std::cout << (value ? "true" : "false") << std::endl;
    }
};

string Lab_boolean::stringify() {
    return value ? "true" : "false";
};

template<typename T>
Lab_boolean::Lab_boolean(T oring) {
    type = LabTypes::boolean_type;
    if (oring == "" || oring == "0" || oring == "false") {
        value = false;
    } else {
        value = true;
    }
};

Lab_boolean::~Lab_boolean() {};

#endif