//
// Created by 潘峰 on 2022/7/1.
//
#include "LabEle.h"

LabEle *LabEle::get(LabEle *attr)
{
    attr->show();
    //std::cout << "init---addName2-----------" << std::endl;
    //base_prototype->look_vars_frame(addName2).show();
    return property->look_variable_env(attr);
};

Lab_number *LabEle::numberV()
{
    return dynamic_cast<Lab_number *>(this);
}

Lab_boolean *LabEle::booleanV()
{
    return dynamic_cast<Lab_boolean *>(this);
}

Lab_string *LabEle::stringV()
{
    return dynamic_cast<Lab_string *>(this);
}

Lab_list *LabEle::listV()
{
    return dynamic_cast<Lab_list *>(this);
}

Lab_variable *LabEle::variableV()
{
    return dynamic_cast<Lab_variable *>(this);
}

Lab_class *LabEle::classV()
{
    return dynamic_cast<Lab_class *>(this);
}

Lab_function *LabEle::functionV()
{
    return dynamic_cast<Lab_function *>(this);
}

Lab_keyWord *LabEle::keyWordV()
{
    return dynamic_cast<Lab_keyWord *>(this);
}

Frame *LabEle::frameV()
{
    return dynamic_cast<Frame *>(this);
}
