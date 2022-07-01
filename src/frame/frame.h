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

using namespace std;

class Frame
{
private:
    /* data */
public:
    frameType type = frameType::topFrame;
    classFrameType prototype_type = classFrameType::topPototype;
    //frameType type = frameType::frame;
    shared_ptr<Frame> father_frame;
    shared_ptr<Frame> father_prototype; //父级原型链条
    //变量存储的字典；
    map<std::string, Lab_Ptr> var_value;
    Frame();
    Frame(vector<Lab_Ptr> &, vector<Lab_Ptr> &);
    void show();
    ~Frame();
    void extend_env(shared_ptr<Frame> fatherFrame);
    void extend_prototype(shared_ptr<Frame> fatherFrame);
    void insert_key_value(LabEle &var, Lab_Ptr &value);

    bool is_key_exist(LabEle &var);
    Lab_Ptr &look_vars_frame(LabEle &var);
    Lab_Ptr &look_variable_env(LabEle var);
    Lab_Ptr &look_variable_class_env(LabEle &var);
    void set_variable_value_env(LabEle &var, Lab_Ptr &value);

    Lab_Ptr &look_variable_prototype(LabEle var);
};

Frame::Frame()
{
}
void Frame::show()
{
    cout << "frame" << endl;
}
Frame::Frame(vector<Lab_Ptr> &name, vector<Lab_Ptr> &value)
{
    if (name.size() != value.size())
    {
        cout << "形式参数和实际参数个数不一致" << endl;
        throw("形式参数和实际参数个数不一致");
    }
    else
    {
        vector<Lab_Ptr>::const_iterator n_iter = name.cbegin();
        vector<Lab_Ptr>::const_iterator v_iter = value.cbegin();
        for (; n_iter != name.cend(); n_iter++, v_iter++)
        {
            //cout << (*iter) << endl;
            auto _name = **n_iter;
            auto _value = *v_iter;
            insert_key_value(_name, _value);
        }
    }
};

Frame::~Frame()
{
}
void Frame::insert_key_value(LabEle &var, Lab_Ptr &value)
{
    string key = var.value();
    var_value.insert(std::pair<std::string, Lab_Ptr &>(key, value));
}

void Frame::extend_env(shared_ptr<Frame> fatherFrame)
{
    type = frameType::frame;
    father_frame = fatherFrame;
}

void Frame::extend_prototype(shared_ptr<Frame> fatherPrototype)
{
    prototype_type = classFrameType::framePototype;
    father_prototype = fatherPrototype;
}

bool Frame::is_key_exist(LabEle &var)
{

    string key = var.value();
    //cout << "is_key_exist  " << key << endl;
    auto theFind = var_value.find(key);
    if (theFind != var_value.end())
    {
        return true;
    }
    else
    {
        //std::cout << "没有找到变量" << key << std::endl;
        return false;
    }
};

Lab_Ptr &Frame::look_vars_frame(LabEle &var)
{

    string key = var.value();
    auto theFind = var_value.find(key);
    if (theFind != var_value.end())
    {
        return theFind->second;
    }
    else
    {
        //这里应该只需要一个undefined
        std::cout << "没有找到变量" << key << std::endl;
        auto result = make_shared<LabEle>();
        return result;
    }
};

Lab_Ptr &Frame::look_variable_env(LabEle var)
{
    string key = var.value();
    auto theFind = var_value.find(key);

    if (theFind != var_value.end())
    {
        return theFind->second;
    }
    else if (type != frameType::topFrame)
    {
        return this->father_frame->look_variable_env(var);
    }
    else
    {
        //这里应该只需要一个undefined
        std::cout << "没有找到变量" << key << std::endl;
        auto result = make_shared<LabEle>();
        return result;
    };
}

void Frame::set_variable_value_env(LabEle &var, Lab_Ptr &value)
{
    string key = var.value();
    auto theFind = var_value.find(key);
    std::cout << "1" << endl;
    if (theFind != var_value.end())
    {
        std::cout << "2" << endl;
        theFind->second = value;
    }
    else if (type != frameType::topFrame)
    {
        return this->father_frame->set_variable_value_env(var, value);
    }
    else
    {
        std::cout << "环境中没有该变量";
        throw("环境中没有该变量");
    };
}

Lab_Ptr &Frame::look_variable_prototype(LabEle var)
{
    string key = var.value();
    auto theFind = var_value.find(key);

    if (theFind != var_value.end())
    {
        return theFind->second;
    }
    else if (prototype_type != classFrameType::topPototype)
    {
        return this->father_prototype->look_variable_prototype(var);
    }
    else
    {
        //这里应该只需要一个undefined
        std::cout << "没有找到方法" << key << std::endl;
        auto result = make_shared<LabEle>();
        return result;
    };
}
#endif