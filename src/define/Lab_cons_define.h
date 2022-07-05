#ifndef LABElE_CONS_DEFINE
#define LABElE_CONS_DEFINE

#include <memory>
#include <vector>
#include <string>
#include "../LabTypes.h"
#include "../types/LabEle.h"
#include "../types/Lab_cons.h"
#include "../parseCode/codeStruct.h"
#include "../utils/tools.h"

Lab_cons::~Lab_cons() {
    type = LabTypes::cons_type;
}

Lab_cons::Lab_cons(LabEle * key, LabEle * value) {
    type = LabTypes::cons_type;
    key_value.first = key;
    key_value.second = value;
};

std::string Lab_cons::stringify() {
    string result = "( ";
    result += (key_value.first->stringify() + " · " + key_value.second->stringify());
    result += ")";
    return result;
}


#endif