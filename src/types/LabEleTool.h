//
// Created by 潘峰 on 2022/7/1.
//

#ifndef LAB_LABELETOOL_H
#define LAB_LABELETOOL_H

#include <memory>
#include <vector>
#include <map>

#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "./LabEle.h"
#include "./Lab_undefined.h"
#include "./Lab_number.h"
#include "./Lab_string.h"
#include "./Lab_boolean.h"
#include "./Lab_keyWord.h"
#include "./Lab_variable.h"
#include "./Lab_class.h"
#include "./Lab_function.h"
#include "./Lab_list.h"
#include "./Lab_json.h"
#include "./Lab_cons.h"

class LabEleTool
{
public:
    static LabEle *createLabEle()
    {
        return new Lab_undefined();
    };

    static LabEle *createLabEleString(std::string valueString);

    static LabEle *createLabEle(std::string valueString);

    static LabEle *createLabEle(bool boolV);

    //LabEle(std::vector<string> &strings);
    static LabEle *createLabEle(originalFn);

    static LabEle *createLabEle(Frame *);

    static LabEle *createLabEle(pair<LabEle *, LabEle *>);

    static LabEle *createLabEle(string, vector<Lab_Ptr>); //json

    static LabEle *createLabEle(vector<LabEle *>);

    static LabEle *createLabEle(vector<LabEle *>, LabCallback, Frame*);                    // 函数
    static LabEle *createLabEle(Frame*, Frame*, vector<LabEle *>, LabCallback); //_class
    static LabEle *createLabEle(macroCallBack);

    static LabEle *createLabEle(CodeUnit_Ptr oneCode);
};

#endif //LAB_LABELETOOL_H
