#include "../types/LabEle.h"
#include "../frame/frame.h"
#include <memory>

auto number_prototype = make_shared<Frame>();
auto base_prototype = make_shared<Frame>();
auto global_env = make_shared<Frame>();
void base_init()
{
    LabEle addName = *(make_shared<LabEle>(string("go")));
    // string addName = "temp";
    Lab_Ptr value = make_shared<LabEle>(string("111"));
    base_prototype->insert_key_value(addName, value);
};

void number_init()
{
    number_prototype->extend_env(base_prototype);
    LabEle addName = *(make_shared<LabEle>(string("temp")));
    Lab_Ptr value = make_shared<LabEle>(string("10000"));
    number_prototype->insert_key_value(addName, value);
};

void global_env_init()
{
    auto macro_env = make_shared<Frame>();
    global_env->extend_env(macro_env);
    originalFn add_define = [](vector<Lab_Ptr> params) -> Lab_Ptr
    {
        Lab_Ptr result = make_shared<LabEle>(string("0"));
        for (Lab_Ptr &param : params)
        {
            result->numberV->value += param->numberV->value;
        };
        return result;
    };
    Lab_Ptr add_fun = make_shared<LabEle>(add_define);
    LabEle addName = *(make_shared<LabEle>(string("+")));
    global_env->insert_key_value(addName, add_fun);

    originalFn subtract_define = [](vector<Lab_Ptr> params) -> Lab_Ptr
    {
        Lab_Ptr result = make_shared<LabEle>(to_string(params[0]->numberV->value));
        for (int i = 1; i < params.size(); i++)
        {
            result->numberV->value -= params[i]->numberV->value;
        }
        return result;
    };
    Lab_Ptr subtract_fun = make_shared<LabEle>(subtract_define);
    LabEle subtract_name = *(make_shared<LabEle>(string("-")));
    global_env->insert_key_value(subtract_name, subtract_fun);

    originalFn equal = [](vector<Lab_Ptr> params) -> Lab_Ptr
    {
        // Lab_Ptr result = make_shared<LabEle>(true);
        Lab_Ptr origin = params[0];
        bool result_temp = true;
        for (Lab_Ptr &param : params)
        {
            result_temp = origin->type == param->type && origin->value() == param->value();
            if (!result_temp)
            {
                break;
            }
        };
        Lab_Ptr result = make_shared<LabEle>(result_temp);
        return result;
    };
    Lab_Ptr equal_fun = make_shared<LabEle>(equal);
    LabEle equal_name = *(make_shared<LabEle>(string("=")));
    global_env->insert_key_value(equal_name, equal_fun);
}

void init()
{
    base_init();
    number_init();
    global_env_init();
}