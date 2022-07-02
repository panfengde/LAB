#ifndef LABElE_FUNCTION_DEFINE
#define LABElE_FUNCTION_DEFINE

#include <sstream>
#include <string>
#include <utility>
#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "../utils/tools.h"
#include "../types/LabEle.h"
#include "../frame/frame.h"
#include "../types/Lab_function.h"
//typedef std::function<LabEle(std::vector<LabEle>)> function_define;

Lab_function::Lab_function()
{
    type = LabTypes::function_type;
};

Lab_function::Lab_function(originalFn callBack)
{
    type = LabTypes::function_type;
    funType = funType::original;
    original_fn = callBack;
};

Lab_function::Lab_function(vector<LabEle *> define_args, LabCallback define_body, Frame *env)
{
    type = LabTypes::function_type;
    funType = funType::compound;
    args = define_args;
    ananlyzed_body = define_body;
    define_env = env;
    _this = env;
};

Lab_function::Lab_function(macroCallBack callback)
{
    type = LabTypes::function_type;
    funType = funType::macro;
    macroCallBackBody = callback;
};

Lab_function::~Lab_function(){
    //std::cout << "~~~~~~~~~~~~~~~~~~Lab_function" << std::endl;
};

#endif