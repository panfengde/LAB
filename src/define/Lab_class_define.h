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

Lab_class::Lab_class(shared_ptr<Frame> def_env, shared_ptr<Frame> p_env, vector<shared_ptr<LabEle>> define_args, LabCallback define_body)
{
    args = define_args;
    analyze_constructor = define_body;
    define_env = def_env;
    prototype = p_env;
};

#endif