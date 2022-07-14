#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <list>
#include <algorithm>
#include "./codeStruct.h"
//#include "../readfile/read.cpp"

using namespace std;

enum expType {
    null,
    isExp,
    isString,
    isSingleString,
    // isQuote,
    isWord,
    isArray,
    isJson,
    isDOMJson,
};

string aboutWord(string word) {
    if (word[0] == '[' && word[word.length() - 1] == ']') {
        return " " + word + " ";
    } else {
        return " \"" + word + "\" ";
    }
}

bool jude_point(std::string str) {
    auto index = str.find(".");
    return index != str.npos && str[index + 1] != '.';
};

string split(std::string str) {
    string pattern = ".";
    // cout << str << "........" << endl;
    if (str.find(pattern) == str.npos) {
        return str;
    }
    std::string::size_type pos;
    std::vector<std::string> word;
    str += pattern; //扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            word.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }

    std::string result = "( get " + word[0] + " " + aboutWord(word[1]) + " )";

    for (int i = 2; i < word.size(); i++) {
        string thisWord = word[i];
        if (thisWord[0] == '[' && thisWord[thisWord.length() - 1] == ']') {
            result = "( get " + result + " " + aboutWord(word[i]) + ")";
        } else {
            result = "( get " + result + " " + aboutWord(word[i]) + " )";
        }
    }

    return result;
}

string DomToJsonString(string &exp_str) {
    int DOMJsonFlag = 0;
    bool DOMJsonChildren = false;

    string tempResult = "";
    // 针对json的cons使用
    string temp_for_json = "";
    // 针对DOMJson使用
    string temp_for_DOMjson = "";

    auto exp_str_length = exp_str.length();

    auto exp_str_last_Index = exp_str_length - 1;
    std::vector<char> rubbishWords = {
            '\0',
            '\n',
            '\r',
            '\f',
            '\t',
            ' ',
    };
    auto start_addr = rubbishWords.begin();
    auto end_addr = rubbishWords.end();

    for (int i = 0; i < exp_str_length; i++) {
        char word = exp_str[i];
        auto it = find(start_addr, end_addr, word);
        if (it != end_addr) {
            continue;
        }
        if (word == '<') {
            DOMJsonFlag += 1;
            if (DOMJsonFlag == 1) {
                tempResult += "{ type:\"";
            } else if (DOMJsonChildren) {
                if (exp_str[i + 1] != '/') {
                    temp_for_DOMjson += '<';
                } else {
                    DOMJsonFlag -= 4;
                    if (DOMJsonFlag == -1) {

                        DOMJsonChildren = false;
                    } else if (DOMJsonChildren) {
                        temp_for_DOMjson += word;
                    }
                }
            }
        } else if (word == ' ' && DOMJsonFlag == 1) {
            tempResult += "\",";
        } else if (word == '=') {
            tempResult += ":";
        } else if (word == '>') {
            DOMJsonFlag += 1;
            if (DOMJsonChildren) {
                temp_for_DOMjson += word;
            } else if (DOMJsonFlag == 0) {
                auto childrenStr = DomToJsonString(temp_for_DOMjson);
                tempResult += (childrenStr + ",]}");
                temp_for_DOMjson = "";
            }
            if (DOMJsonFlag == 2) {
                if (!DOMJsonChildren) {
                    tempResult += "\",child:[";
                }
                DOMJsonChildren = true;
            }

        } else if (DOMJsonChildren) {
            temp_for_DOMjson += word;
        } else {
            if (DOMJsonFlag != -1) {
                tempResult += word;
            }
        }
    }
    cout << "dom----" << endl;
    cout << tempResult << endl;
    return tempResult;
};

shared_ptr<CodeUnit> strExp_to_List(string &exp_str, shared_ptr<CodeUnit> result = make_shared<CodeUnit>()) {
    //std::cout << exp_str << std::endl;
    expType type = expType::null;
    int expFlag = 0;
    int stringFlag = 0;
    int arrayFlag = 0;
    int jsonFlag = 0;
    int DOMJsonFlag = 0;

    auto exp_str_length = exp_str.length();
    auto exp_str_last_Index = exp_str_length - 1;
    std::vector<char> rubbishWords = {
            '\0',
            '\n',
            '\r',
            '\f',
            '\t',
            ' ',
    };
    auto start_addr = rubbishWords.begin();
    auto end_addr = rubbishWords.end();
    vector<char>::iterator it;
    string tempResult = "";
    // 针对json的cons使用
    string temp_for_json = "";


    for (int i = 0; i < exp_str_length; i++) {
        char word = exp_str[i];
        if (type == expType::null) {
            it = find(start_addr, end_addr, word);
            if (it == end_addr) {
                if (word == '\"') {
                    type = expType::isString;
                } else if (word == '\'') {
                    type = expType::isSingleString;
                }
                    // else if (word == '\'')
                    // {
                    //   type = expType::isQuote;
                    // }
                else if (word == '(') {
                    //std::cout << "go->exp" << std::endl;
                    type = expType::isExp;
                } else if (word == '{') {
                    type = expType::isJson;
                } else if (word == '<') {
                    type = expType::isDOMJson;
                } else if (word == '[') {
                    type = expType::isArray;
                } else {
                    type = expType::isWord;
                }
            }
        }
        //std::cout << word << std::endl;

        switch (type) {
            case expType::null:
                break;
            case expType::isString:
                tempResult += word;
                //cout << word << endl;
                if (word == '\"' && tempResult.length() > 1) {
                    //std::cout << "string:" << tempResult << std::endl;
                    auto result_shared = make_shared<CodeUnit>(tempResult);
                    result->elementList.push_back(result_shared);
                    type = expType::null;
                    tempResult = "";
                }
                break;
            case expType::isSingleString:
                tempResult += word;
                //cout << word << endl;
                if (word == '\'' && tempResult.length() > 1) {
                    //std::cout << "string:" << tempResult << std::endl;
                    auto result_shared = make_shared<CodeUnit>(tempResult);
                    result->elementList.push_back(result_shared);
                    type = expType::null;
                    tempResult = "";
                }
                break;
            case expType::isExp:
                if (word == '(') {
                    expFlag += 1;
                    if (tempResult.length() != 0 || expFlag != 1) {
                        tempResult += word;
                    }
                } else if (word == ')') {
                    expFlag -= 1;
                    if (expFlag == 0) {
                        //std::cout << "exp:" << tempResult << std::endl;
                        auto result_shared = strExp_to_List(tempResult);
                        result->elementList.push_back(result_shared);
                        type = expType::null;
                        tempResult = "";
                    } else {
                        tempResult += word;
                    }
                } else {
                    tempResult += word;
                }
                break;
            case expType::isWord:
                it = find(start_addr, end_addr, word);
                if (it == end_addr) {
                    tempResult += word;
                } else {
                    if (jude_point(tempResult)) {
                        //处理属性表达式 a.b.c
                        auto exp_str = split(tempResult);
                        auto result_shared = strExp_to_List(exp_str, result);
                    } else {
                        auto result_shared = make_shared<CodeUnit>(tempResult);
                        result->elementList.push_back(result_shared);
                    }
                    type = expType::null;
                    tempResult = "";
                }

                if (i == exp_str_last_Index && tempResult.length() > 0) {
                    if (jude_point(tempResult)) {
                        auto exp_str = split(tempResult);
                        auto result_shared = strExp_to_List(exp_str, result);
                    } else {
                        auto result_shared = make_shared<CodeUnit>(tempResult);
                        result->elementList.push_back(result_shared);
                    }
                    type = expType::null;
                    tempResult = "";
                }
                break;
            case expType::isArray:
                it = find(start_addr, end_addr, word);
                if (it != end_addr) {
                    if (!(stringFlag != 0 && word == ' ')) {
                        break;
                    }
                }

                if (word == '\"') {
                    stringFlag == 0 ? stringFlag += 1 : stringFlag -= 1;
                }

                if (word == '{') {
                    jsonFlag += 1;
                } else if (word == '}') {
                    jsonFlag -= 1;
                }

                if (word == ',' && jsonFlag == 0) {
                    tempResult += ' ';
                    break;
                }
                if (word == '[') {
                    arrayFlag += 1;
                    if (arrayFlag == 1) {
                        tempResult += "Array ";
                    } else {
                        tempResult += word;
                    }
                } else if (word == ']') {
                    arrayFlag -= 1;
                    if (arrayFlag == 0) {
                        auto result_shared = strExp_to_List(tempResult);
                        result->elementList.push_back(result_shared);
                        tempResult = "";
                        type = expType::null;
                    } else {
                        tempResult += word;
                    }
                } else {
                    tempResult += word;
                }
                break;
            case expType::isJson:
                it = find(start_addr, end_addr, word);
                if (it != end_addr) {
                    if (stringFlag == 0 && stringFlag != ' ') {
                        break;
                    }
                }

                if (word == '\"') {
                    stringFlag == 0 ? stringFlag += 1 : stringFlag -= 1;
                }

                if (word == '[') {
                    arrayFlag += 1;
                } else if (word == ']') {
                    arrayFlag -= 1;
                }

                if (word == '{') {
                    jsonFlag += 1;
                    if (jsonFlag == 1) {
                        tempResult += "Json ";
                    } else {
                        temp_for_json += word;
                    }
                } else if (word == '}') {
                    jsonFlag -= 1;
                    if (jsonFlag == 0) {
                        // 针对json的cons使用
                        if (temp_for_json.length() != 0) {
                            tempResult += "( Cons " + temp_for_json + ')';
                        }
                        //cout << tempResult << endl;
                        auto result_shared = strExp_to_List(tempResult);
                        result->elementList.push_back(result_shared);
                        tempResult = "";
                        temp_for_json = "";
                        type = expType::null;
                    } else {
                        temp_for_json += word;
                    }
                } else {
                    if (jsonFlag == 1 && word == ':') {
                        if (temp_for_json[0] != '\"') {
                            temp_for_json = '\"' + temp_for_json + '\"';
                        }
                        temp_for_json += ' ';
                    } else if (jsonFlag == 1 && arrayFlag == 0 && word == ',') {
                        tempResult += "( Cons " + temp_for_json + ')';
                        temp_for_json = "";
                    } else {
                        temp_for_json += word;
                    }
                };
                break;
            case expType::isDOMJson:
                tempResult += word;
                if (word == '<') {
                    DOMJsonFlag += 1;
                } else if (word == '>') {
                    DOMJsonFlag += 1;
                    if (DOMJsonFlag == 0) {
                        auto JsonString = DomToJsonString(tempResult);
                        type = expType::null;
                        strExp_to_List(JsonString, result);
                        break;
                    }
                } else if (word == '/') {
                    DOMJsonFlag -= 4;
                }

                break;
            default:
                std::cout << "----default------" << std::endl;
                throw "语法错误";
                break;
        }
    };

    return result;
}

shared_ptr<CodeUnit> codeTxt_to_list(string &exp_str) {
    auto result = make_shared<CodeUnit>();
    auto beginFlag = make_shared<CodeUnit>("begin");

    result->elementList.push_back(beginFlag);
    return strExp_to_List(exp_str, result);
};

// int main()
// {
//   string strCode = read("../Lab/test.lab");
//   strExp_to_List(strCode);
//   return 1;
// };