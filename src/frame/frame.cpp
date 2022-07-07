//
// Created by 潘峰 on 2022/7/1.
//

#include "./frame.h"

Frame::Frame() {
    type = LabTypes::frame_type;
}

void Frame::show() {
    cout << "frame" << endl;
}

Frame::Frame(vector<LabEle *> &name, vector<LabEle *> &value){
    type = LabTypes::frame_type;
    if (name.size() != value.size()) {
        cout << "形式参数和实际参数个数不一致" << endl;
        throw ("形式参数和实际参数个数不一致");
    } else {
        vector<LabEle *>::const_iterator n_iter = name.cbegin();
        vector<LabEle *>::const_iterator v_iter = value.cbegin();
        for (; n_iter != name.cend(); n_iter++, v_iter++) {
            //cout << (*iter) << endl;
            auto _name = *n_iter;
            auto _value = *v_iter;
            insert_key_value(_name, _value);
        }
    }
};

Frame::~Frame() {
}

void Frame::insert_key_value(LabEle *var, LabEle *value) {
    string key = (var->type == LabTypes::variable_type) ? var->variableV()->value
                                                        : var->stringV()->value;
    var_value.insert(std::pair<std::string, LabEle *>(key, value));
}

void Frame::extend_env(Frame *fatherFrame) {
    areaType = frameType::frame;
    father_frame = fatherFrame;
}

void Frame::extend_prototype(Frame *fatherPrototype) {
    prototype_type = classFrameType::framePototype;
    father_prototype = fatherPrototype;
}

bool Frame::is_key_exist(LabEle *var) {
    string key = (var->type == LabTypes::variable_type) ? var->variableV()->value
                                                        : var->stringV()->value;
    auto theFind = var_value.find(key);
    if (theFind != var_value.end()) {
        return true;
    } else {
        //std::cout << "没有找到变量" << key << std::endl;
        return false;
    }
};

LabEle *Frame::look_vars_frame(LabEle *var) {
    string key = (var->type == LabTypes::variable_type) ? var->variableV()->value
                                                        : var->stringV()->value;
    auto theFind = var_value.find(key);
    if (theFind != var_value.end()) {
        return theFind->second;
    } else {
        //这里应该只需要一个undefined
        std::cout << "没有找到变量" << key << std::endl;
        auto result = LabEleTool::createLabEle();
        return result;
    }
};

LabEle *Frame::look_variable_env(LabEle *var) {
//    auto keyEle =
//            (var->type == LabTypes::variable_type) ? var->variableV()
//                                                   : var->stringV();
    string key = (var->type == LabTypes::variable_type) ? var->variableV()->value
                                                        : var->stringV()->value;

    auto theFind = var_value.find(key);

    if (theFind != var_value.end()) {
        return theFind->second;
    } else if (areaType != frameType::topFrame) {
        return this->father_frame->look_variable_env(var);
    } else {
        //这里应该只需要一个undefined
        std::cout << "没有找到变量" << key << std::endl;
        auto result = LabEleTool::createLabEle();
        return result;
    };
}

void Frame::set_variable_value_env(LabEle *var, LabEle *value) {
    string key = (var->type == LabTypes::variable_type) ? var->variableV()->value
                                                        : var->stringV()->value;

    auto theFind = var_value.find(key);
    std::cout << "1" << endl;
    if (theFind != var_value.end()) {
        std::cout << "2" << endl;
        theFind->second = value;
    } else if (areaType != frameType::topFrame) {
        return this->father_frame->set_variable_value_env(var, value);
    } else {
        std::cout << "环境中没有该变量";
        throw ("环境中没有该变量");
    };
}

LabEle *Frame::look_variable_prototype(LabEle *var) {
    string key = (var->type == LabTypes::variable_type) ? var->variableV()->value
                                                        : var->stringV()->value;
    auto theFind = var_value.find(key);

    if (theFind != var_value.end()) {
        return theFind->second;
    } else if (prototype_type != classFrameType::topPototype) {
        return this->father_prototype->look_variable_prototype(var);
    } else {
        //这里应该只需要一个undefined
        std::cout << "没有找到方法" << key << std::endl;
        auto result = LabEleTool::createLabEle();
        return result;
    };
}