//
// Created by 潘峰 on 2022/7/7.
//

#ifndef LAB_LAB_INSERTTYPE_H
#define LAB_LAB_INSERTTYPE_H

#include "../LabTypes.h"
#include "./LabEle.h"
#include <iostream>
#include <map>

using namespace std;

class Lab_insertType : public LabEle {
public:
    // type
    Lab_insertType();
    LabEle *get(LabEle *attr);

    //void addMethods(map<std::string, LabEle *> *);
};


#endif //LAB_LAB_INSERTTYPE_H
