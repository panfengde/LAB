#ifndef LABLIST
#define LABLIST
#include "../LabTypes.h"
#include "../parseCode/codeStruct.h"

//#include "./Lab_cons.h"
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "./Base.h"

using namespace std;
//class Lab_list : pubick Lab_cons
class LabEle;

class Lab_list : public Base
{
private:
public:
    LabTypes::LabTypes type = LabTypes::list_type;
    LabEle *container;
    Lab_list();
    vector<shared_ptr<LabEle> > eles;
    Lab_list(vector<shared_ptr<CodeUnit> > argv);
    Lab_list(vector<shared_ptr<LabEle> >);
    Lab_Ptr car();
    Lab_Ptr cdr();
    Lab_Ptr last_items();
    int length();
    template <class T>
    std::vector<T> map(T);
    string value();
    string stringify();
    void show();
    ~Lab_list(){
        //std::cout << "~~~~~~~~~~~~~~~~~~Lab_list" << std::endl;
    };
};

#endif