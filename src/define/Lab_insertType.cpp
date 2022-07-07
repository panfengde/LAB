//
// Created by 潘峰 on 2022/7/7.
//

#include "../types/Lab_insertType.h"

Lab_insertType::Lab_insertType() {
    type = LabTypes::insertType;
    value = "insertType";
}

LabEle *Lab_insertType::get(LabEle *attr) {
    //std::cout << "number--" << v << std::endl;
    return property->look_variable_env(attr);
};
/*
void Lab_insertType::addMethods(map<std::string, LabEle *> name_fn) {
    //cout << "AAAA------：" << property<< endl;
    property = new Frame();
    property->var_value.swap(name_fn);
}*/
