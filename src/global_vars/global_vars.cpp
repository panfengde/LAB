#include "../types/Lab_string.h"
#include "../frame/frame.h"
#include <memory>

auto number_prototype = new Frame();
auto base_prototype = new Frame();
auto global_env = new Frame();

void base_init() {
    auto addName = LabEleTool::createLabEle(string("go"));
    // string addName = "temp";
    Lab_Ptr value = LabEleTool::createLabEle(string("111"));
    base_prototype->insert_key_value(addName, value);
    cout << "base_init" << endl;
};

void number_init() {
    cout << "number_init" << endl;
    number_prototype->extend_env(base_prototype);
    Lab_Ptr addName = LabEleTool::createLabEle(string("temp"));
    Lab_Ptr value = LabEleTool::createLabEle(string("10000"));
    number_prototype->insert_key_value(addName, value);
    cout << "number_init" << endl;
};

void global_env_init() {
    auto macro_env = new Frame();
    global_env->extend_env(macro_env);
    originalFn add_define = [](vector<Lab_Ptr> params) -> Lab_Ptr {
        Lab_Ptr result = LabEleTool::createLabEle(string("0"));
        for (Lab_Ptr &param: params) {
            result->numberV()->value += param->numberV()->value;
        };
        std::cout << "result------" << result->numberV()->value << endl;
        return result;
    };
    Lab_Ptr add_fun = LabEleTool::createLabEle(add_define);
    auto addName = (LabEleTool::createLabEle(string("+")));
    global_env->insert_key_value(addName, add_fun);

    originalFn subtract_define = [](vector<Lab_Ptr> params) -> Lab_Ptr {
        Lab_Ptr result = LabEleTool::createLabEle(to_string(params[0]->numberV()->value));
        for (int i = 1; i < params.size(); i++) {
            result->numberV()->value -= params[i]->numberV()->value;
        }
        return result;
    };
    Lab_Ptr subtract_fun = LabEleTool::createLabEle(subtract_define);
    auto subtract_name = (LabEleTool::createLabEle(string("-")));
    global_env->insert_key_value(subtract_name, subtract_fun);

    originalFn equal = [](vector<Lab_Ptr> params) -> Lab_Ptr {
        // Lab_Ptr result = LabEleTool::createLabEle(true);
        Lab_Ptr origin = params[0];
        bool result_temp = true;
        for (Lab_Ptr &param: params) {
            result_temp = origin->type == param->type && origin->value == param->value;
            if (!result_temp) {
                break;
            }
        };
        Lab_Ptr result = LabEleTool::createLabEle(result_temp);
        return result;
    };
    Lab_Ptr equal_fun = LabEleTool::createLabEle(equal);
    auto equal_name = (LabEleTool::createLabEle(string("=")));
    global_env->insert_key_value(equal_name, equal_fun);
    cout << "base_init" << endl;
}

void init() {
    base_init();
    number_init();
    global_env_init();
}