#ifndef KEYWORD
#define KEYWORD

#include "../LabTypes.h"
#include <iostream>
#include <string>
#include <map>

class Lab_keyWord : public LabEle {
private:
    /* data */
public:
    std::string value;
    LabEle *container;
    keywordType::keywordType keywordType;

    Lab_keyWord(std::string _value, keywordType::keywordType _type) {
        //这里性能有问题！
        //std::cout << "Lab_keyWord----" << _value << std::endl;
        type = LabTypes::keyword_type;
        value = _value;
        keywordType = _type;
    };

    void show() {
        std::cout << "key_str" << std::endl;
    }

    ~Lab_keyWord() {};
};

#endif