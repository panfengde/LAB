#ifndef LIST_DEFINE
#define LIST_DEFINE

#include <memory>
#include <vector>
#include <string>
#include "../LabTypes.h"
#include "../types/LabEle.h"
#include "../types/LabEleTool.h"
#include "../types/Lab_list.h"
#include "../parseCode/codeStruct.h"
#include "../utils/tools.h"

//#include "./Lab_cons.h"

using namespace std;

//class Lab_list : pubick Lab_cons
class LabEle;

Lab_list::Lab_list() {
    type = LabTypes::list_type;
};

Lab_list::Lab_list(vector<shared_ptr<CodeUnit>> CodeVec) {
    type = LabTypes::list_type;
    //vector<LabEle> *_eles = new vector<LabEle>{};
    eles = vector<LabEle *>();
    ///cout << CodeVec.size() << endl;
    for (shared_ptr<CodeUnit> temp: CodeVec) {
        eles.push_back(LabEleTool::createLabEle(temp));
    };
};

Lab_list::Lab_list(vector<LabEle *> LabEles) {
    type = LabTypes::list_type;
    eles = LabEles;
};

LabEle *Lab_list::car() {
    //return eles[0];
    return eles.front();
};

LabEle *Lab_list::cdr() {
    auto length = eles.size();

    if (length < 2) {
        return new LabEle();
    } else {
        vector<LabEle *>::const_iterator first = eles.begin() + 1;
        vector<LabEle *>::const_iterator end = eles.end();
        vector<LabEle *> _cdr(first, end);
        auto result = LabEleTool::createLabEle(_cdr);
        //cout << "cdr----" << result->stringify() << endl;
        return result;
    };
};

int Lab_list::length() {
    return eles.size();
}

LabEle *Lab_list::last_items() {
    if (eles.size() < 1) {
        return new LabEle();
    }
    // return else[ele.size()-1]
    return eles.back();
};

string Lab_list::value() {
    string result = "( ";
    for (int i = 0; i < eles.size(); i++) {
        result += eles[i]->value + ' ';
    }
    result += " )";
    return result;
}

string Lab_list::stringify() {
    string result = "[";
    auto size = eles.size();
    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            result += eles[i]->stringify();
        } else {
            result += eles[i]->stringify() + ',';
        }
    }
    result += ']';
    return result;
}

void Lab_list::show() {
    cout << value() << endl;
};

#endif