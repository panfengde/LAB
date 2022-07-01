#ifndef CODEVECTOR
#define CODEVECTOR
//#include "./Lab_cons.h"
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "../LabTypes.h"

using namespace std;


/* enum codeType
{
    ele=10,
    exp
};
 */
class CodeUnit
{
public:
    vector<shared_ptr<CodeUnit>> elementList;
    //vector<shared_ptr<string>> words;
    shared_ptr<string> element;
    codeType type = codeType::exp;
    CodeUnit(string code)
    {
        type = codeType::ele;
        element = make_shared<string>(string(code));
    };
    CodeUnit();
    ~CodeUnit()
    {
        //cout << "~CodeUnit" << endl;
    }
};

CodeUnit::CodeUnit()
{
    //element.string::~string();
    //new vector<CodeUnit> temp = {};
    type = codeType::exp;
    elementList = vector<shared_ptr<CodeUnit>>();
};

#endif