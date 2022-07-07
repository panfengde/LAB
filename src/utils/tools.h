#ifndef TOOL
#define TOOL

#include <string>
#include <regex>
#include <sstream>
#include <map>
#include <utility>
#include "../LabTypes.h"
#include "../types/LabEle.h"
//#include "../define/LabEle_define.h"
#include "../types/Lab_list.h"
#include "../parseCode/codeStruct.h"

namespace tools {

    bool isNumber(const string &str) { //判断字符串是否为数字
        istringstream sin(str);
        double test;
        return sin >> test && sin.eof();
    }

    bool isString(const string &str) { //判断字符串是否为数字

        if (str[0] == '\"') {
            return true;
        } else {
            return false;
        }
    }

    bool isBool(const string &str) {
        if (str == "true" || str == "false") {
            return true;
        } else {
            return false;
        }
    }

    bool isUndefined(const string &str) {
        // todo
        return false;
    }

    std::pair<bool, keywordType::keywordType> iskeyWord(const string &str) {
        map<std::string, keywordType::keywordType> keyWords;
        keyWords["define"] = keywordType::define;
        keyWords["quote"] = keywordType::quote;
        keyWords["if"] = keywordType::_if;
        keyWords["begin"] = keywordType::begin;
        keyWords["set"] = keywordType::set;
        keyWords["lambda"] = keywordType::lambda;
        keyWords["class"] = keywordType::_class;
        keyWords["define-syntax"] = keywordType::define_syntax;
        // keyWords["let"] = keywordType::let;
        keyWords["'"] = keywordType::quote;
        keyWords["new"] = keywordType::_new;
        keyWords["get"] = keywordType::get;
        keyWords["Cons"] = keywordType::cons;
        keyWords["Array"] = keywordType::array;
        keyWords["Json"] = keywordType::json;
        keyWords["sleep"] = keywordType::sleep;
        auto iter = keyWords.find(str);
        if (iter != keyWords.end()) {
            keywordType::keywordType type = iter->second;
            return std::pair<bool, keywordType::keywordType>{true, type};
        } else {
            return std::pair<bool, keywordType::keywordType>{false, keywordType::define};
        }
    }

    bool is_list(CodeUnit *ele) {
        if (ele->type == codeType::exp) {
            return true;
        } else {
            return false;
        };
    };

    bool is_list(LabEle &ele) {
        if (ele.type == LabTypes::list_type) {
            return true;
        } else {
            return false;
        };
    };

    bool is_cdr_list(Lab_Ptr ele) {
        if (ele->type == LabTypes::list_type) {
            auto Ele = (Lab_list *) ele;

            auto length = Ele->eles.size();
            if (length > 1) {
                return true;
            } else {
                return false;
            };
        } else {
            return false;
        };
    };

    bool is_car_list(Lab_Ptr ele) {
        if (ele->type == LabTypes::list_type) {
            auto Ele = (Lab_list *) ele;
            Lab_Ptr _car = Ele->car();
            return tools::is_list(*_car);
        } else {
            return false;
        };
    };

}

#endif