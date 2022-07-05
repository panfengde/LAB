#ifndef LABELE
#define LABELE

#include <regex>
#include <sstream>
//#include <memory>

//#include "../LabTypes.h"
#include "../typeGlobal.h"
//#include "./Lab_undefined.h"
//#include "./Lab_number.h"
//#include "./Lab_string.h"
//#include "./Lab_boolean.h"
//#include "./Lab_keyWord.h"
//#include "./Lab_variable.h"
//#include "./Lab_class.h"
//#include "./Lab_function.h"
//#include "./Lab_list.h"
//#include "./Lab_json.h"
//#include "./Lab_cons.h"

using namespace std;

//
class Lab_undefined;

class Lab_number;

class Lab_boolean;

class Lab_string;

class Lab_cons;

class Lab_list;

class Lab_json;

class Lab_variable;

class Lab_class;

class Lab_function;

class Lab_keyWord;

//
//class CodeUnit;
//
class Frame;

bool isNumber(const std::string &str) { //判断字符串是否为数字
    istringstream sin(str);
    double test;
    return sin >> test && sin.eof();
}

class LabEle {
public:
    LabTypes::LabTypes type = LabTypes::undefined_type;
    std::string value = "undefined";

    // 存储那些可以在LAB中使用的方法和属性---
    Frame *property;

    virtual LabEle *get(LabEle *attr);

    Lab_undefined *undefinedV();

    Lab_number *numberV();

    Lab_boolean *booleanV();

    Lab_string *stringV();

    Lab_cons *consV();

    Lab_list *listV();

    Lab_json *jsonV();

    Lab_class *classV();

    Lab_variable *variableV();

    Lab_function *functionV();

    Lab_keyWord *keyWordV();

    Frame *frameV();

    void show() {

    };

    virtual string stringify();

    LabEle *set(LabEle *);

    // ~LabEle();
};

#endif
