#ifndef LABElE_DEFINE
#define LABElE_DEFINE

#include <regex>
#include <sstream>
#include <string>
#include <memory>
#include <utility>
#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "../utils/tools.h"
#include "../types/Lab_undefined.h"
#include "../types/Lab_keyWord.h"
#include "../types/Lab_number.h"
#include "../types/Lab_string.h"
#include "../types/Lab_boolean.h"
#include "../types/LabEle.h"
//#include "../types/baseStruct/Lab_cons.h"
#include "../types/Lab_list.h"
#include "../types/Lab_class.h"
#include "../types/Lab_function.h"
#include "../parseCode/codeStruct.h"

class CodeUnit;

class Frame;

using namespace std;

LabEle::LabEle(CodeUnit CodeVec) {
    if (CodeVec.type == codeType::exp) {
        this->type = LabTypes::list_type;
        listV = make_shared<Lab_list>(CodeVec.elementList);
        listV->container = this;
        //std::cout << "exp----------------ok" << std::endl;
    } else {
        //std::cout<<"one----"<<std::endl;
        new(this) LabEle(*(CodeVec.element));
    }
};

LabEle::LabEle(vector<shared_ptr<LabEle>> oneLabEle) {
    type = LabTypes::list_type;
    listV = make_shared<Lab_list>(oneLabEle);
    listV->container = this;
};

LabEle::LabEle(std::string valueString) {
    if (isNumber(valueString)) {
        numberV = make_shared<Lab_number>(valueString);
        numberV->container = this;
        type = LabTypes::number_type;
    } else if (valueString[0] == '\"') {
        string stringValue = valueString.substr(1, valueString.length() - 2);
        stringV = make_shared<Lab_string>(stringValue);
        stringV->container = this;
        type = LabTypes::string_type;
    } else if (valueString == "false") {
        booleanV = make_shared<Lab_boolean>(false);
        booleanV->container = this;
        type = LabTypes::boolean_type;
    } else if (valueString == "true" || valueString == "else") {
        booleanV = make_shared<Lab_boolean>(true);
        booleanV->container = this;
        type = LabTypes::boolean_type;
    } else {
        std::pair<bool, keywordType::keywordType> keyWord = tools::iskeyWord(valueString);
        if (keyWord.first) {
            keyWordV = make_shared<Lab_keyWord>(valueString, keyWord.second);
            keyWordV->container = this;
            type = LabTypes::keyword_type;
        } else {
            //保留
            //variableV = new Lab_variable(valueString);
            //std::cout << "variableV---variableV--------" << std::endl;
            variableV = make_shared<Lab_variable>(valueString);
            variableV->container = this;
            //new (numberV) Lab_number(valueString);
            type = LabTypes::variable_type;
        }
    }
};

LabEle::LabEle(bool boolv) {
    booleanV = make_shared<Lab_boolean>(boolv);
    booleanV->container = this;
    type = LabTypes::boolean_type;
}

LabEle::LabEle(originalFn c) {
    type = LabTypes::function_type;
    functionV = make_shared<Lab_function>(c);
    functionV->container = this;
};

LabEle::LabEle(std::pair<shared_ptr<LabEle>, shared_ptr<LabEle>> thePair) {
    consV = make_shared<Lab_cons>(thePair.first, thePair.second);
    consV->container = this;
    type = LabTypes::cons_type;
};

//json
LabEle::LabEle(string _, vector<Lab_Ptr> theCons) {
    jsonV = make_shared<Lab_json>(theCons);
    jsonV->container = this;
    type = LabTypes::json_type;
};

LabEle::LabEle(vector<shared_ptr<LabEle>> a, LabCallback c, shared_ptr<Frame> e) {
    type = LabTypes::function_type;
    functionV = make_shared<Lab_function>(a, c, e);
    functionV->container = this;
};

LabEle::LabEle(shared_ptr<Frame> c_env, shared_ptr<Frame> m_env, vector<shared_ptr<LabEle>> args, LabCallback fn) {
    type = LabTypes::class_type;
    classV = make_shared<Lab_class>(c_env, m_env, args, fn);
    classV->container = this;
};

LabEle::LabEle(macroCallBack callback) {
    type = LabTypes::function_type;
    functionV = make_shared<Lab_function>(callback);
    functionV->container = this;
};

LabEle::LabEle(shared_ptr<Frame> f) {
    type = LabTypes::frame_type;
    frameV = f;
    //classV->container = this;
};

//LabEle::LabEle(function_define callbAck){}
Lab_Ptr &LabEle::get(Lab_Ptr &key) {
    auto result = make_shared<LabEle>();
    switch (this->type) {
        case LabTypes::number_type:
            return (this->numberV->get(key));
            break;
        case LabTypes::string_type:
            return (this->stringV->get(key));
            break;
        case LabTypes::boolean_type:
            return (this->booleanV->get(key));
            break;
        case LabTypes::class_type:
            return (this->listV->get(key));
            break;
        case LabTypes::function_type:
            return (this->listV->get(key));
            break;
        case LabTypes::list_type:
            return (this->listV->get(key));
            break;
        case LabTypes::keyword_type:
            return (this->listV->get(key));
            break;
        case LabTypes::variable_type:
            return (this->listV->get(key));
            break;
        case LabTypes::undefined_type:
            return result;
            break;
        case LabTypes::frame_type:
            return (this->frameV->look_variable_prototype(*key));
            break;
        case LabTypes::cons_type:
            return this->consV->get(key);
            break;
        case LabTypes::json_type:
            return this->jsonV->get(*key);
            break;
        default:
            return result;
            break;
    };
}

void LabEle::clone(LabEle &value) {
    switch (value.type) {
        case LabTypes::number_type:
            type = LabTypes::number_type;
            numberV->container = this;
            numberV = value.numberV;
            break;
        case LabTypes::string_type:
            type = LabTypes::string_type;
            stringV = value.stringV;
            break;
        case LabTypes::boolean_type:
            type = LabTypes::boolean_type;
            booleanV = value.booleanV;
            break;
        case LabTypes::class_type:
            type = LabTypes::class_type;
            classV = value.classV;
            break;
        case LabTypes::function_type:
            type = LabTypes::function_type;
            functionV = value.functionV;
            break;
        case LabTypes::list_type:
            type = LabTypes::list_type;
            listV = value.listV;
            break;
        case LabTypes::keyword_type:
            type = LabTypes::keyword_type;
            keyWordV = value.keyWordV;
            break;
        case LabTypes::variable_type:
            type = LabTypes::variable_type;
            variableV = value.variableV;
            break;
        case LabTypes::undefined_type:
            type = LabTypes::undefined_type;
            undefinedV = value.undefinedV;
            break;
        case LabTypes::frame_type:
            type = LabTypes::frame_type;
            functionV = value.functionV;
            break;
        case LabTypes::cons_type:
            type = LabTypes::cons_type;
            consV = value.consV;
            break;
        case LabTypes::json_type:
            type = LabTypes::json_type;
            jsonV = value.jsonV;
            break;
        default:
            break;
    };
}

/**
 * 引用绑定
 **/
void LabEle::bindQuote(Lab_Ptr &value) {

    this->reset();

    //cout << type << ":" << numberV->value << "|" << value->type << value->numberV->value << endl;
    //cout << value->numberV->value << endl;
    switch (value->type) {
        case LabTypes::number_type:

            type = LabTypes::number_type;
            numberV->container = this;
            numberV = value->numberV;
            break;
        case LabTypes::string_type:

            type = LabTypes::string_type;
            stringV = value->stringV;
            break;
        case LabTypes::boolean_type:
            type = LabTypes::boolean_type;
            booleanV = value->booleanV;
            break;
        case LabTypes::class_type:
            type = LabTypes::class_type;
            classV = value->classV;
            break;
        case LabTypes::function_type:
            type = LabTypes::function_type;
            functionV = value->functionV;
            break;
        case LabTypes::list_type:
            type = LabTypes::list_type;
            listV = value->listV;
            break;
        case LabTypes::keyword_type:
            throw "can't set var keyWord";
            break;
        case LabTypes::variable_type:
            type = LabTypes::variable_type;
            variableV = value->variableV;
            break;
        case LabTypes::undefined_type:
            type = LabTypes::undefined_type;
            undefinedV = value->undefinedV;
            break;
        case LabTypes::frame_type:
            type = LabTypes::frame_type;
            frameV = value->frameV;
            break;
        case LabTypes::cons_type:
            type = LabTypes::cons_type;
            consV = value->consV;
            break;
        case LabTypes::json_type:
            type = LabTypes::frame_type;
            jsonV = value->jsonV;
            break;
        default:
            break;
    };
}

void LabEle::reset() {

    switch (this->type) {
        case LabTypes::number_type:
            numberV->~Lab_number();
            break;
        case LabTypes::string_type:
            stringV->~Lab_string();
            break;
        case LabTypes::boolean_type:
            booleanV->~Lab_boolean();
            break;
        case LabTypes::class_type:
            classV->~Lab_class();
            break;
        case LabTypes::function_type:
            functionV->~Lab_function();
            break;
        case LabTypes::list_type:
            listV->~Lab_list();
            break;
        case LabTypes::keyword_type:
            keyWordV->~Lab_keyWord();
            break;
        case LabTypes::variable_type:
            variableV->~Lab_variable();
            break;
        case LabTypes::undefined_type:
            break;
        case LabTypes::frame_type:
            frameV->~Frame();
            break;
        case LabTypes::cons_type:
            consV->~Lab_cons();
            break;
        case LabTypes::json_type:
            jsonV->~Lab_json();
            break;
        default:
            throw "error";
            break;
    };

    // undefinedV = make_shared<Lab_undefined>();
    // undefinedV->container = this;
}

void LabEle::show() {

    switch (this->type) {
        case LabTypes::number_type:
            numberV->show();
            break;
        case LabTypes::string_type:
            stringV->show();
            break;
        case LabTypes::boolean_type:
            booleanV->show();
            break;
        case LabTypes::class_type:
            classV->show();
            break;
        case LabTypes::function_type:
            functionV->show();
            break;
        case LabTypes::list_type:
            listV->show();
            break;
        case LabTypes::keyword_type:
            keyWordV->show();
            break;
        case LabTypes::variable_type:
            variableV->show();
            break;
        case LabTypes::undefined_type:
            undefinedV->show();
            break;
        case LabTypes::frame_type:
            frameV->show();
            break;
        case LabTypes::cons_type:
            consV->show();
            break;
        case LabTypes::json_type:
            jsonV->show();
            break;
        default:
            throw "error";
            break;
    };

    // undefinedV = make_shared<Lab_undefined>();
    // undefinedV->container = this;
}

string LabEle::value() {
    switch (this->type) {
        case LabTypes::number_type:
            return to_string(numberV->value);
            break;
        case LabTypes::string_type:
            return "\"" + stringV->value + "\"";
            break;
        case LabTypes::boolean_type:
            return to_string(booleanV->value);
            break;
        case LabTypes::class_type:
            return classV->value;
            break;
        case LabTypes::function_type:
            return functionV->value;
            break;
        case LabTypes::list_type:
            return listV->value();
            break;
        case LabTypes::keyword_type:
            return keyWordV->value;
            break;
        case LabTypes::variable_type:
            return variableV->value;
            break;
        case LabTypes::undefined_type:
            return to_string(undefinedV->value);
            break;
        case LabTypes::cons_type:
            return consV->value();
            break;
        case LabTypes::json_type:
            return jsonV->value();
            break;
        default:
            throw "error";
            break;
    };
}

string LabEle::stringify() {
    switch (this->type) {
        case LabTypes::list_type:
            return listV->stringify();
            break;
        case LabTypes::json_type:
            return jsonV->stringify();
            break;
        default:
            return value();
            break;
    };
}

LabEle::~LabEle() {
}

#endif