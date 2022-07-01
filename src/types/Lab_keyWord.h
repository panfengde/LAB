#ifndef KEYWORD
#define KEYWORD

#include "../LabTypes.h"
#include <iostream>
#include <string>
#include <map>

class Lab_keyWord
{
private:
    /* data */
public:
    std::string value;
    LabEle *container;
    LabTypes::LabTypes type = LabTypes::keyword_type;
    keywordType::keywordType keywordType;
    Lab_keyWord(std::string _value, keywordType::keywordType _type)
    {
        //这里性能有问题！
        //std::cout << "Lab_keyWord----" << _value << std::endl;
        value = _value;
        keywordType = _type;
    };
    void show()
    {
        std::cout << "key_str" << std::endl;
    }
    ~Lab_keyWord(){};
};

#endif