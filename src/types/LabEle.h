#ifndef LABELE
#define LABELE

#include <regex>
#include <sstream>
#include <memory>

#include "../LabTypes.h"
#include "../typeGlobal.h"
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

using namespace std;

class Lab_list;

class CodeUnit;

class Frame;

bool isNumber(const std::string &str) { //判断字符串是否为数字
    istringstream sin(str);
    double test;
    return sin >> test && sin.eof();
}

class LabEle {
public:
    LabTypes::LabTypes type = LabTypes::undefined_type;
    shared_ptr<Lab_undefined> undefinedV;
    shared_ptr<Lab_number> numberV;
    shared_ptr<Lab_string> stringV;
    shared_ptr<Lab_boolean> booleanV;
    shared_ptr<Lab_class> classV;
    shared_ptr<Lab_function> functionV;
    shared_ptr<Lab_list> listV;
    shared_ptr<Lab_keyWord> keyWordV;
    shared_ptr<Lab_variable> variableV;
    shared_ptr<Lab_cons> consV;
    shared_ptr<Lab_json> jsonV;
    shared_ptr<Frame> frameV;

    LabEle() : type(LabTypes::undefined_type) {
        undefinedV = make_shared<Lab_undefined>();
        undefinedV->container = this;
    };

    LabEle(std::string valueString);

    LabEle(bool boolV);

    //LabEle(std::vector<string> &strings);
    LabEle(originalFn);

    LabEle(shared_ptr<Frame>);

    LabEle(pair<shared_ptr<LabEle>, shared_ptr<LabEle>>);

    LabEle(string, vector<Lab_Ptr>); //json
    LabEle(vector<shared_ptr<LabEle>>);

    LabEle(vector<shared_ptr<LabEle>>, LabCallback, shared_ptr<Frame>);                    // 函数
    LabEle(shared_ptr<Frame>, shared_ptr<Frame>, vector<shared_ptr<LabEle>>, LabCallback); //_class
    LabEle(macroCallBack);

    LabEle(CodeUnit oneCode);

    void clone(LabEle &);

    Lab_Ptr &get(Lab_Ptr &);

    // bindQuote是 set方法赋值用的，感觉不需要
    void bindQuote(Lab_Ptr &);

    void reset();

    void show();

    string value();

    string stringify();

    ~LabEle();
};

#endif
