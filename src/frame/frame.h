#ifndef FRAME
#define FRAME

#include <map>
#include <utility>
#include <string>
#include <vector>
#include <memory>
#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "../typeGlobal.h"
#include "../types/LabEle.h"

#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "./types/LabEle.h"
#include "./types/LabEleTool.h"
#include "./types/Lab_undefined.h"
#include "./types/Lab_number.h"
#include "./types/Lab_string.h"
#include "./types/Lab_boolean.h"
#include "./types/Lab_keyWord.h"
#include "./types/Lab_variable.h"
#include "./types/Lab_class.h"
#include "./types/Lab_function.h"
#include "./types/Lab_list.h"
#include "./types/Lab_json.h"
#include "./types/Lab_cons.h"

using namespace std;

class Lab_string;

class Frame : public LabEle {
private:
    /* data */
public:
    frameType areaType = frameType::topFrame;
    classFrameType prototype_type = classFrameType::topPototype;
    string xxx = "xxxxllll";
    //frameType type = frameType::frame;
    Frame *father_frame;
    Frame *father_prototype; //父级原型链条
    //变量存储的字典；
    map<std::string, LabEle *> var_value;

    Frame();

    Frame(vector<LabEle *> &, vector<LabEle *> &);

    void show();

    ~Frame();

    void extend_env(Frame *fatherFrame);

    void extend_prototype(Frame *fatherFrame);

    void insert_key_value(LabEle *var, LabEle *value);

    bool is_key_exist(LabEle *var);

    LabEle *look_vars_frame(LabEle *var);

    LabEle *look_variable_env(LabEle *var);

    LabEle *look_variable_class_env(LabEle &var);

    void set_variable_value_env(LabEle *var, LabEle *value);

    LabEle *look_variable_prototype(LabEle *var);
};

#endif