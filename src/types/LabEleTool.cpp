//
// Created by 潘峰 on 2022/7/1.
//

#include "LabEleTool.h"

LabEle *LabEleTool::createLabEle(CodeUnit_Ptr CodeVec) {
    if (CodeVec->type == codeType::exp) {
        return new Lab_list(CodeVec->elementList);
    } else {
        return LabEleTool::createLabEle(*(CodeVec->element));
    }
};

LabEle *LabEleTool::createLabEle(vector<LabEle *> oneLabEle) {
    return new Lab_list(oneLabEle);
};

LabEle *LabEleTool::createLabEleString(std::string valueString) {
    return new Lab_string(valueString);
}

LabEle *LabEleTool::createLabEle(std::string valueString) {
    if (isNumber(valueString)) {
        return new Lab_number(valueString);
    } else if (valueString[0] == '\"') {
        string stringValue = valueString.substr(1, valueString.length() - 2);
        return new Lab_string(stringValue);
    } else if (valueString == "false") {
        return new Lab_boolean(false);
    } else if (valueString == "true" || valueString == "else") {
        return new Lab_boolean(true);
    } else {
        std::pair<bool, keywordType::keywordType> keyWord = tools::iskeyWord(valueString);
        if (keyWord.first) {
            return new Lab_keyWord(valueString, keyWord.second);
        } else {
            //保留
            //variableV = new Lab_variable(valueString);
            //std::cout << "variableV---variableV--------" << std::endl;
            return new Lab_variable(valueString);
        }
    }
};

LabEle *LabEleTool::createLabEle(bool boolv) {
    return new Lab_boolean(boolv);
}

LabEle *LabEleTool::createLabEle(originalFn c) {
    return new Lab_function(c);
};

LabEle *LabEleTool::createLabEle(std::pair<LabEle *, LabEle *> thePair) {
    return new Lab_cons(thePair.first, thePair.second);
};

//json
LabEle *LabEleTool::createLabEle(string _, vector<Lab_Ptr> theCons) {
    return new Lab_json(theCons);
};

LabEle *LabEleTool::createLabEle(vector<LabEle *> a, LabCallback c, Frame *e) {
    return new Lab_function(a, c, e);
};

LabEle *LabEleTool::createLabEle(Frame *c_env, Frame *m_env, vector<LabEle *> args,
                                 LabCallback fn) {
    return new Lab_class(c_env, m_env, args, fn);
};

LabEle *LabEleTool::createLabEle(macroCallBack callback) {
    return new Lab_function(callback);
};

LabEle *LabEleTool::createLabEle(Frame *f) {
    return f;
};