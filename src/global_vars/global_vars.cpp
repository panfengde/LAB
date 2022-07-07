#include "../types/Lab_string.h"
#include "../frame/frame.h"
#include <memory>

auto number_prototype = new Frame();
auto base_prototype = new Frame();
auto global_env = new Frame();

void base_init() {
    auto addName = LabEleTool::createLabEle(string("go"));
    // string addName = "temp";
    LabEle *value = LabEleTool::createLabEle(string("111"));
    base_prototype->insert_key_value(addName, value);
};

void number_init() {
    number_prototype->extend_env(base_prototype);
    LabEle *addName = LabEleTool::createLabEle(string("temp"));
    LabEle *value = LabEleTool::createLabEle(string("10000"));
    number_prototype->insert_key_value(addName, value);
};

void global_env_init() {
    auto macro_env = new Frame();
    global_env->extend_env(macro_env);
    originalFn add_define = [](vector<LabEle *> params) -> LabEle * {
        LabEle *result = LabEleTool::createLabEle(string("0"));
        for (LabEle *&param: params) {
            result->numberV()->value += param->numberV()->value;
        };
        return result;
    };
    LabEle *add_fun = LabEleTool::createLabEle(add_define);
    auto addName = (LabEleTool::createLabEle(string("+")));
    global_env->insert_key_value(addName, add_fun);

    originalFn subtract_define = [](vector<LabEle *> params) -> LabEle * {
        LabEle *result = LabEleTool::createLabEle(to_string(params[0]->numberV()->value));
        for (int i = 1; i < params.size(); i++) {
            result->numberV()->value -= params[i]->numberV()->value;
        }
        return result;
    };
    LabEle *subtract_fun = LabEleTool::createLabEle(subtract_define);
    auto subtract_name = (LabEleTool::createLabEle(string("-")));
    global_env->insert_key_value(subtract_name, subtract_fun);

    originalFn equal = [](vector<LabEle *> params) -> LabEle * {
        // LabEle* result = LabEleTool::createLabEle(true);
        LabEle *origin = params[0];
        bool result_temp = true;
        for (LabEle *param: params) {
            result_temp = origin->type == param->type && origin->numberV()->value == param->numberV()->value;
            if (!result_temp) {
                break;
            }
        };
        LabEle *result = LabEleTool::createLabEle(result_temp);
        return result;
    };
    LabEle *equal_fun = LabEleTool::createLabEle(equal);
    auto equal_name = (LabEleTool::createLabEle(string("=")));
    global_env->insert_key_value(equal_name, equal_fun);
}

void init() {
    base_init();
    number_init();
    global_env_init();
}