#ifndef LABLIST
#define LABLIST

#include "../LabTypes.h"
#include "../parseCode/codeStruct.h"

//#include "./Lab_cons.h"
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "./LabEle.h"

using namespace std;

//class Lab_list : pubick Lab_cons
class LabEle;

class Lab_list : public LabEle {
private:
public:

    LabEle *container;

    Lab_list();

    vector<LabEle*> eles;

    Lab_list(vector<shared_ptr<CodeUnit> > argv);

    Lab_list(vector<LabEle*>);

    LabEle* car();

    LabEle* cdr();

    LabEle* last_items();

    int length();

    template<class T>
    std::vector<T> map(T);

    string value();

    string stringify();

    void show();

    ~Lab_list() {
        //std::cout << "~~~~~~~~~~~~~~~~~~Lab_list" << std::endl;
    };
};

#endif