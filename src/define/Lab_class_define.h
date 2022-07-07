#ifndef LABElE_CLASS_DEFINE
#define LABElE_CLASS_DEFINE

#include <sstream>
#include <string>
#include <utility>
#include "../LabTypes.h"
#include "../typeGlobal.h"
#include "../utils/tools.h"
#include "../types/LabEle.h"
#include "../frame/frame.h"
#include "../types/Lab_class.h"
//typedef std::function<LabEle(std::vector<LabEle>)> function_define;

Lab_class::Lab_class(Frame *def_env, Frame *p_env, vector<LabEle *> define_args, LabCallback define_body)
{
    type = LabTypes::class_type;
    args = define_args;
    analyze_constructor = define_body;
    define_env = def_env;
    prototype = p_env;
};

#endif