// #ifndef explainObj_entry
// #define explainObj_entry
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "../types/Lab_list.h"
#include "../types/LabEle.h"
#include "../frame/frame.h"
#include "../LabTypes.h"
#include "../utils/tools.h"
#include "../typeGlobal.h"
#include "../global_vars/global_vars.h"
#include "../task/task.h"

//typedef std::function<LabEle(Frame&)> LabCallback;

LabCallback explainObj_entry(LabEle &parsed_code);

namespace macroFn
{
    Lab_Ptr findCondition(Lab_Ptr params, Lab_Ptr conditions);
    bool paramsArgsMatch(Lab_Ptr var_args, Lab_Ptr params);
    Lab_Ptr replace(Lab_Ptr vars, Lab_Ptr BranchTemplate, Lab_Ptr params);
    void add(Lab_Ptr origin, std::pair<string, Lab_Ptr> get_cons);
    Lab_Ptr loopTemplate(
        Lab_Ptr oneTemplate, Lab_Ptr vars, Lab_Ptr params, Lab_Ptr result = make_shared<LabEle>(vector<Lab_Ptr>() = {}));
    std::pair<string, Lab_Ptr> loopWord(Lab_Ptr word, Lab_Ptr vars, Lab_Ptr params);
    Lab_Ptr replaceMacro(Lab_Ptr conditions_list, Lab_Ptr params);
    //------申明

    Lab_Ptr findCondition(Lab_Ptr params, Lab_Ptr conditions)
    {

        if (conditions->type != LabTypes::undefined_type)
        {

            Lab_Ptr this_conditon = conditions->listV->car();
            Lab_Ptr rest_condition = conditions->listV->cdr();
            Lab_Ptr var_args = this_conditon->listV->car()->listV->cdr();

            if (macroFn::paramsArgsMatch(var_args, params))
            {
                return this_conditon;
            }
            else
            {
                return findCondition(params, rest_condition);
            }
        }
        else
        {
            cout << "没找到" << endl;
            auto result = make_shared<LabEle>();
            return result;
        }
    }

    bool paramsArgsMatch(Lab_Ptr var_args, Lab_Ptr params)
    {
        if (var_args->type == LabTypes::list_type && params->type == LabTypes::list_type)
        {
            Lab_Ptr _temp = var_args->listV->last_items();

            if (_temp->type != LabTypes::list_type && _temp->variableV->value.substr(0, 3) == "...")
            {
                auto length = params->listV->length();
                if (length >= var_args->listV->length() - 1)
                {
                    return length > 1 ? (macroFn::paramsArgsMatch(var_args->listV->car(), params->listV->car()) && macroFn::paramsArgsMatch(var_args->listV->cdr(), params->listV->cdr()))
                                      : (macroFn::paramsArgsMatch(var_args->listV->car(), params->listV->car()));
                }
                else
                {
                    return false;
                }
            }
            else
            {

                auto length = params->listV->length();
                if (params->listV->length() == var_args->listV->length())
                {
                    return length > 1 ? (macroFn::paramsArgsMatch(var_args->listV->car(), params->listV->car()) && macroFn::paramsArgsMatch(var_args->listV->cdr(), params->listV->cdr()))
                                      : (macroFn::paramsArgsMatch(var_args->listV->car(), params->listV->car()));
                }
                else
                {
                    return false;
                }
            }
        }
        else if (var_args->type != LabTypes::list_type && var_args->value().substr(0, 3) == "...")
        {
            return true;
        }
        else
        {

            return params->type != LabTypes::undefined_type;
        }
    }

    Lab_Ptr replace(Lab_Ptr vars, Lab_Ptr BranchTemplate, Lab_Ptr params)
    {
        return macroFn::loopTemplate(BranchTemplate, vars, params);
    }

    void add(Lab_Ptr origin, std::pair<string, Lab_Ptr> get_cons)
    {
        if (get_cons.second->type != LabTypes::undefined_type)
        {
            if (get_cons.first == "...")
            {
                auto eles = get_cons.second->listV->eles;
                origin->listV->eles.insert(
                    origin->listV->eles.end(),
                    std::make_move_iterator(eles.begin()),
                    std::make_move_iterator(eles.end()));
            }
            else if (get_cons.first == "word" || get_cons.first == "no_find")
            {
                origin->listV->eles.push_back(get_cons.second);
            }
            else if (get_cons.first == "none")
            {
            };
        }
    }

    Lab_Ptr loopTemplate(Lab_Ptr oneTemplate, Lab_Ptr vars, Lab_Ptr params, Lab_Ptr result)
    {
        if (oneTemplate->type != LabTypes::list_type)
        {
            if (oneTemplate->type == LabTypes::undefined_type)
            {
            }
            else
            {
                add(result, macroFn::loopWord(oneTemplate->listV->car(), vars, params));
            }
        }
        else
        {
            if (tools::is_car_list(*oneTemplate))
            {

                result->listV->eles.push_back(loopTemplate(oneTemplate->listV->car(), vars, params));
                loopTemplate(oneTemplate->listV->cdr(), vars, params, result);
            }
            else
            {
                add(result, macroFn::loopWord(oneTemplate->listV->car(), vars, params));
                loopTemplate(oneTemplate->listV->cdr(), vars, params, result);
            }
        }
        return result;
    }

    std::pair<string, Lab_Ptr> loopWord(Lab_Ptr word, Lab_Ptr vars, Lab_Ptr params)
    {

        if (vars->type != LabTypes::list_type)
        {
            //
            return pair<string, Lab_Ptr>(string("no_find"), word);
        }
        else
        {

            if (vars->listV->car()->type == LabTypes::list_type)
            {
                //cout << "---hhhhhhhh————————" << word->value() << endl;
                pair<string, Lab_Ptr> temp = macroFn::loopWord(word, vars->listV->car(), params->listV->car());

                if (temp.first == "no_find")
                {
                    return macroFn::loopWord(word, vars->listV->cdr(), params->listV->cdr());
                }
                else
                {
                    return temp;
                }
            }
            else
            {
                //cout << "---xxxxxxxx———————" << word->value() << endl;
                if (word->value() == vars->listV->car()->value())
                {

                    //cout << "---找到了————————" << word->value() << endl;

                    if (word->value().substr(0, 3) == "...")
                    {

                        if (params->type == LabTypes::list_type)
                        {
                            return pair<string, Lab_Ptr>("...", params);
                        }
                        else
                        {
                            if (params->type == LabTypes::undefined_type)
                            {
                                //特殊情况，...对应空
                                //可能会有问题
                                return pair<string, Lab_Ptr>("none", make_shared<LabEle>());
                            }
                            else
                            {
                                return pair<string, Lab_Ptr>("word", params);
                            }
                        }
                    }
                    else
                    {

                        if (params->type == LabTypes::list_type)
                        {
                            return pair<string, Lab_Ptr>("word", params->listV->car());
                        }
                        else
                        {
                            if (params->type == LabTypes::undefined_type)
                            {
                                //特殊情况，...对应空
                                //可能会有问题
                                return pair<string, Lab_Ptr>("none", make_shared<LabEle>());
                            }
                            else
                            {
                                return pair<string, Lab_Ptr>("word", params->listV->car());
                            }
                        }
                    }
                }
                else
                {
                    if (params->type == LabTypes::undefined_type)
                    {
                        return pair<string, Lab_Ptr>("no_find", word);
                    }
                    else
                    {
                        return macroFn::loopWord(word, vars->listV->cdr(), params->listV->cdr());
                    }
                }
            };
        }
    }

    Lab_Ptr replaceMacro(Lab_Ptr conditions_list, Lab_Ptr params)
    {
        /*
        (define-syntax nil!
            (syntax-rules ()
            ((_ x)(set! x '()))
            ((_ x a)(set! x a))
            )
        )
        */

        Lab_Ptr conditon = findCondition(params, conditions_list);

        if (conditon->type != LabTypes::list_type)
        {
            throw "宏错误";
        }
        else
        {
            Lab_Ptr oneTemplate = conditon->listV->cdr()->listV->car();
            Lab_Ptr vars = conditon->listV->car()->listV->cdr();
            Lab_Ptr result = macroFn::replace(vars, oneTemplate, params);

            return result;
        }
    }

}

namespace eval
{
    Lab_Ptr eval_app(Lab_Ptr &operate, std::vector<Lab_Ptr> &operands)
    {
        //operate
        //((lambda (x) (+ x 1)) 100)
        if (operate->type == LabTypes::function_type)
        {
            shared_ptr<Lab_function> fun = operate->functionV;
            shared_ptr<Lab_class> _class = operate->classV;
            if (fun->funType == funType::original)
            {
                return fun->original_fn(operands);
            }
            else
            {

                LabCallback &function_body = fun->ananlyzed_body;
                vector<Lab_Ptr> &function_args = fun->args;
                shared_ptr<Frame> newEnv = make_shared<Frame>(function_args, operands);
                shared_ptr<Frame> defineEnv = fun->define_env;
                shared_ptr<Frame> thisEnv = fun->_this;
                newEnv->extend_env(defineEnv);

                //给函数作用域植入this
                Lab_Ptr _this = make_shared<LabEle>(std::string("this"));
                Lab_Ptr this_env = make_shared<LabEle>(thisEnv);
                newEnv->insert_key_value(*_this, this_env);
                return function_body(newEnv);
            }
        }
        else if (operate->type == LabTypes::class_type)
        {
            cout << " LabTypes::class_type--------" << endl;
            vector<Lab_Ptr> class_args = operate->classV->args;
            vector<Lab_Ptr> class_params = operands;

            LabCallback analyze_constructor = operate->classV->analyze_constructor;
            shared_ptr<Frame> class_define_env = operate->classV->define_env;
            shared_ptr<Frame> prototype_env = operate->classV->prototype;
            shared_ptr<Frame> example_env = make_shared<Frame>(class_args, class_params);

            example_env->extend_env(class_define_env);
            example_env->extend_prototype(prototype_env);

            Lab_Ptr _this = make_shared<LabEle>(std::string("this"));
            Lab_Ptr example_env_LabEle = make_shared<LabEle>(example_env);
            example_env->insert_key_value(*_this, example_env_LabEle);
            return analyze_constructor(example_env);
        }
        else
        {
            std::cout << "--------?eval_app?-----" << std::endl;
        }
    };
}
namespace analyze
{
    /**
     * 一些前置的方法，放这里
     **/
    LabCallback __seqeunces_run(LabCallback &first, LabCallback &second)
    {
        return [=](shared_ptr<Frame> env) -> Lab_Ptr
        {
            first(env);
            return second(env);
        };
    }

    LabCallback __loop(LabCallback &first_producer, std::vector<LabCallback> &rest_producers)
    {

        auto length = rest_producers.size();
        if (length > 0)
        {
            std::vector<LabCallback> reset;
            if (length > 1)
            {
                std::vector<LabCallback>::const_iterator first = rest_producers.begin() + 1;
                std::vector<LabCallback>::const_iterator end = rest_producers.end();
                reset = std::vector<LabCallback>(first, end);
            }
            LabCallback go_first = analyze::__seqeunces_run(first_producer, rest_producers[0]);

            return analyze::__loop(go_first, reset);
        }
        else
        {
            //std::cout << "seqeunces分析完成" << std::endl;
            return first_producer;
        };
    }

    LabCallback sequences_analyze(vector<Lab_Ptr> &eles)
    {
        //std::vector<LabEle> &eles = ele.listV->eles;
        std::vector<LabCallback> analyzed_sequences;
        for (Lab_Ptr ele : eles)
        {
            analyzed_sequences.push_back(explainObj_entry(*ele));
        };
        std::vector<LabCallback> reset;
        if (eles.size() > 1)
        {
            std::vector<LabCallback>::const_iterator first = analyzed_sequences.begin() + 1;
            std::vector<LabCallback>::const_iterator end = analyzed_sequences.end();
            reset = std::vector<LabCallback>(first, end);
        }
        return analyze::__loop(analyzed_sequences[0], reset);
    }

    //  分割线------
    LabCallback number(LabEle &ele)
    {
        //std::cout << "分析number" << std::endl;

        return [ele](shared_ptr<Frame> env) -> Lab_Ptr
        {
            // cout << ele.numberV->value << endl;
            auto new_number = make_shared<LabEle>(to_string(ele.numberV->value));
            return new_number;

            // auto new_number = make_shared<LabEle>();
            // //没有深度拷贝
            // //LabEle *new_number = new LabEle(std::string("100"));
            // *new_number = ele;
            // //new_number->clone(ele);
            // return new_number;
        };
    }

    LabCallback _string(LabEle &ele)
    {
        return [ele](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            auto new_string = make_shared<LabEle>();
            //没有深度拷贝
            *new_string = ele;
            //new_string->clone(ele);
            return new_string;
        };
    }

    LabCallback boolean(LabEle &ele)
    {
        return [&ele](shared_ptr<Frame> env) -> Lab_Ptr
        {
            //没有深度拷贝
            auto new_string = make_shared<LabEle>();
            *new_string = ele;
            return new_string;
        };
    }

    LabCallback defineSyntax(LabEle &ele)
    {
        /*
        (define-syntax nil!
            (syntax-rules ()
            ((_ x)(set! x '()))
            ((_ x a)(set! x a))
            )
        )
        */

        Lab_Ptr syntax_body = ele.listV->cdr()->listV->cdr()->listV->car();
        Lab_Ptr syntax_name = ele.listV->cdr()->listV->car();
        if (syntax_body->listV->car()->variableV->value == "syntax-rules")
        {
            Lab_Ptr syntax_condition = ele.listV->cdr()->listV->cdr()->listV->car()->listV->cdr()->listV->cdr();
            // to-d
            /**
             *  1. 函数构造函数要扩展macroCallBack
             *  2. 参数长度可能不固定，函数怎么处理的，是否要修改
             *  3. 空环境的创建
             *  4. 宏替换的整理
             **/
            macroCallBack _result = [syntax_condition](Lab_Ptr params) mutable -> Lab_Ptr
            {
                Lab_Ptr result = macroFn::replaceMacro(syntax_condition, params);

                return result;
            };
            Lab_Ptr parse_result = make_shared<LabEle>(_result);
            global_env->father_frame->insert_key_value(
                *syntax_name,
                parse_result);

            return [](shared_ptr<Frame> env) mutable -> Lab_Ptr
            {
                return make_shared<LabEle>();
            };

            /* return [syntax_name, syntax_body](shared_ptr<Frame> env) mutable -> Lab_Ptr
            {
                env->insert_key_value(
                    *syntax_name,
                    syntax_body);
                cout << "defineSyntax-ok" << endl;
                return make_shared<LabEle>();
            }; */
        }
        else
        {
            throw "宏的定义需要syntax-rules";
        }
    }

    LabCallback variable(LabEle &ele)
    {
        return [ele](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            Lab_Ptr findvar = env->look_variable_env(ele);
            return findvar;
            /* int a = 100;
            auto _result = make_shared<LabEle>(a);
            return *_result; */
        };
    }

    LabCallback _if(LabEle &ele)
    {

        Lab_Ptr if_info = ele.listV->cdr();

        Lab_Ptr pre = if_info->listV->car();

        Lab_Ptr true_action = if_info->listV->cdr()->listV->car();
        Lab_Ptr false_action = if_info->listV->cdr()->listV->cdr();
        if (false_action->type != LabTypes::undefined_type)
        {
            false_action = false_action->listV->car();
        }
        LabCallback pre_back = explainObj_entry(*pre);
        LabCallback true_action_back = explainObj_entry(*true_action);
        LabCallback false_action_back = explainObj_entry(*false_action);
        return [pre_back, true_action_back, false_action_back](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            Lab_Ptr pre_result = pre_back(env);
            if (pre_result->type == LabTypes::boolean_type)
            {
                if (pre_result->booleanV->value)
                {
                    return true_action_back(env);
                }
                else
                {
                    return false_action_back(env);
                }
            }
            else if (pre_result->type == LabTypes::number_type)
            {
                if (pre_result->numberV->value != long(0))
                {
                    return true_action_back(env);
                }
                else
                {
                    return false_action_back(env);
                }
            }
            else if (pre_result->type == LabTypes::string_type)
            {
                if (pre_result->stringV->value != "")
                {
                    return true_action_back(env);
                }
                else
                {
                    return false_action_back(env);
                }
            }
            else if (pre_result->type == LabTypes::undefined_type)
            {
                return false_action_back(env);
            }
            else
            {
                return true_action_back(env);
            }
        };
        // LabCallback prediction = explainObj_entry(*());
        // LabCallback true_action = explainObj_entry(ele.listV->cdr()->listV->car());
        // LabCallback false_action = explainObj_entry(ele.listV->cdr()->listV->cdr()->listV->car());
    }

    LabCallback quote(LabEle &ele)
    {
        //这里是错误的
        return [=](shared_ptr<Frame> env) -> Lab_Ptr
        {
            Lab_Ptr findvar = ele.listV->cdr()->listV->car();
            return findvar;
        };
    }

    LabCallback define(LabEle &ele)
    {
        Lab_Ptr LabEle_info = ele.listV->cdr();
        Lab_Ptr nameOrRgs = LabEle_info->listV->car();
        Lab_Ptr body = LabEle_info->listV->cdr();
        if (nameOrRgs->type == LabTypes::list_type)
        {
            Lab_Ptr name = nameOrRgs->listV->car();
            vector<Lab_Ptr> args = nameOrRgs->listV->cdr()->listV->eles;
            LabCallback analyzed_body = analyze::sequences_analyze(body->listV->eles);
            return [args, analyzed_body, name](shared_ptr<Frame> env) mutable -> Lab_Ptr
            {
                Lab_Ptr _function = make_shared<LabEle>(args, analyzed_body, env);
                env->insert_key_value(*name, _function);
                return make_shared<LabEle>();
            };
        }
        else
        {
            Lab_Ptr name = nameOrRgs;
            Lab_Ptr value = body->listV->car();

            LabCallback valueCallback = explainObj_entry(*value);

            return [name, valueCallback](shared_ptr<Frame> env) mutable -> Lab_Ptr
            {
                Lab_Ptr truevalue = valueCallback(env);
                env->insert_key_value(*name, truevalue);
                return make_shared<LabEle>();
            };
        };
    }

    LabCallback set(LabEle &ele)
    {
        Lab_Ptr setInfo = ele.listV->cdr();
        Lab_Ptr name = setInfo->listV->car();

        Lab_Ptr value = setInfo->listV->cdr()->listV->car();
        LabCallback nameCallback = explainObj_entry(*name);
        LabCallback valueCallback = explainObj_entry(*value);
        // cout << "go-set" << name.variableV->value << endl;
        return [=](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            Lab_Ptr trueObj = nameCallback(env);
            Lab_Ptr truevalue = valueCallback(env);
            trueObj->bindQuote(truevalue);
            return trueObj;
            //return truevalue;
        };
    }

    LabCallback get(LabEle &ele)
    {
        Lab_Ptr getInfo = ele.listV->cdr();
        Lab_Ptr name = getInfo->listV->car();
        Lab_Ptr value = getInfo->listV->cdr()->listV->car();

        LabCallback nameCallback = explainObj_entry(*name);

        LabCallback valueCallback = explainObj_entry(*value);
        return [&ele, nameCallback, valueCallback](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            Lab_Ptr trueObj = nameCallback(env);
            Lab_Ptr trueKey = valueCallback(env);
            Lab_Ptr result = trueObj->get(trueKey);
            if (trueObj->type == LabTypes::frame_type && result->type == LabTypes::function_type)
            {
                result->functionV->_this = trueObj->frameV;
                cout << "_this_____________________" << endl;
            }
            return result;
        };
    }

    LabCallback begin(LabEle &ele)
    {
        Lab_Ptr body = ele.listV->cdr();
        return analyze::sequences_analyze(body->listV->eles);
    }

    // LabCallback _let(LabEle &ele)
    // {
    //     Lab_Ptr let_info = ele.listV->cdr();
    //     vector<Lab_Ptr> &arg_partment = let_info->listV->car()->listV->eles; //.cdr.car
    //     Lab_Ptr body_sequence = let_info->listV->cdr();
    //     make_shared<vector<Lab_Ptr>> args_names{};
    //     make_shared<vector<Lab_Ptr>> args_bodys{};

    //     for (Lab_Ptr temp : arg_partment)
    //     {
    //         args_names->push_back(temp->listV->car());
    //         args_bodys->push_back(temp->listV->cdr()->listV->car());
    //     };

    //     Lab_Ptr _result = make_shared<LabEle>(*args_names, analyzed_body, env);
    // }

    LabCallback lambda(LabEle &ele)
    {
        Lab_Ptr lambdaInfo = ele.listV->cdr();
        auto args = make_shared<vector<Lab_Ptr>>(lambdaInfo->listV->car()->listV->eles);
        //cout << "生成lambda--参数--" << args->size() << endl;
        Lab_Ptr body = lambdaInfo->listV->cdr();
        LabCallback analyzed_body = analyze::sequences_analyze(body->listV->eles);

        return [args, analyzed_body, ele](shared_ptr<Frame> env) -> Lab_Ptr
        {
            Lab_Ptr _result = make_shared<LabEle>(*args, analyzed_body, env);

            //cout << "生成lambda" << endl;
            //cout << "生成lambda--参数--" << _result->functionV->args.size() << endl;

            return _result;
        };
    }

    LabCallback sleep(LabEle &ele)
    {
        // (setTimeout (+ 1 1) 1000)
        Lab_Ptr setTimeoutInfo = ele.listV->cdr();
        Lab_Ptr callBackBody = setTimeoutInfo->listV->car();
        Lab_Ptr callBackTime = setTimeoutInfo->listV->cdr()->listV->car();

        LabCallback analyzed_body = explainObj_entry(*callBackBody);
        LabCallback callBackTime_body = explainObj_entry(*callBackTime);

        return [analyzed_body, callBackTime_body](shared_ptr<Frame> env) -> Lab_Ptr
        {
            int time = callBackTime_body(env)->numberV->value;

            global_labTasks->insertTask(analyzed_body, env, time);
            //cout << "生成lambda" << endl;
            //cout << "生成lambda--参数--" << _result->functionV->args.size() << endl;

            // return _result;
            return make_shared<LabEle>();
        };
    }

    LabCallback _new(LabEle &ele)
    {
        cout << "_new——start" << endl;
        Lab_Ptr trueExp = ele.listV->cdr();
        LabCallback classParse = explainObj_entry(*trueExp);
        cout << "_new" << endl;
        return [classParse](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            return classParse(env);
        };
    }

    LabCallback _class(LabEle &ele)
    {

        Lab_Ptr name = ele.listV->cdr()->listV->car();
        Lab_Ptr constructor = ele.listV->cdr()->listV->cdr()->listV->car();
        auto constructor_args = make_shared<vector<Lab_Ptr>>(constructor->listV->cdr()->listV->car()->listV->eles);
        // Lab_Ptr constructor_args = constructor->listV->cdr()->listV->car();
        Lab_Ptr constructor_body = constructor->listV->cdr()->listV->cdr();
        Lab_Ptr _this = make_shared<LabEle>(std::string("this"));
        constructor_body->listV->eles.push_back(_this);
        Lab_Ptr methods = ele.listV->cdr()->listV->cdr()->listV->cdr();

        LabCallback ananlyzed_constructor_body = analyze::sequences_analyze(constructor_body->listV->eles);
        LabCallback ananlyzed_methods = analyze::sequences_analyze(methods->listV->eles);
        cout << "parse_class——————" << endl;
        return [name, constructor_args, ananlyzed_methods, ananlyzed_constructor_body](shared_ptr<Frame> env) mutable -> Lab_Ptr
        {
            shared_ptr<Frame> prototype_env = make_shared<Frame>();
            prototype_env->extend_env(env);
            ananlyzed_methods(prototype_env);

            cout << "parse_class_3" << endl;
            Lab_Ptr constructor_class = make_shared<LabEle>(env, prototype_env, *constructor_args, ananlyzed_constructor_body);
            env->insert_key_value(*name, constructor_class);
            return make_shared<LabEle>();
        };
    }

    LabCallback cons(LabEle &ele)
    {
        Lab_Ptr first = ele.listV->cdr()->listV->car();
        Lab_Ptr second = ele.listV->cdr()->listV->cdr()->listV->car();
        LabCallback firstValueCall = explainObj_entry(*first);
        LabCallback secondValueCall = explainObj_entry(*second);
        return [&ele, firstValueCall, secondValueCall](shared_ptr<Frame> env) -> Lab_Ptr
        {
            Lab_Ptr firstValue = firstValueCall(env);
            Lab_Ptr secondValue = secondValueCall(env);
            //secondValue->show();
            pair<Lab_Ptr, Lab_Ptr> theCons{firstValue, secondValue};
            auto new_cons = make_shared<LabEle>(theCons);
            //cout << "ok--" << endl;
            return new_cons;
        };
    }

    LabCallback array(LabEle &ele)
    {

        //cout << "array->length---" << ele.listV->length() << endl;
        if (ele.listV->length() == 1)
        {
            return [](shared_ptr<Frame> env) -> Lab_Ptr
            {
                std::vector<Lab_Ptr> array;
                auto new_cons = make_shared<LabEle>(array);
                return new_cons;
            };
        }

        std::vector<Lab_Ptr> array_data = ele.listV->cdr()->listV->eles;
        std::vector<LabCallback> array_data_callbacks;
        for (Lab_Ptr &one_data : array_data)
        {
            array_data_callbacks.push_back(explainObj_entry(*one_data));
        };
        return [&ele, array_data_callbacks](shared_ptr<Frame> env) -> Lab_Ptr
        {
            std::vector<Lab_Ptr> array;
            for (LabCallback data_call : array_data_callbacks)
            {
                array.push_back(data_call(env));
            };
            auto new_array = make_shared<LabEle>(array);
            return new_array;
        };
    }

    LabCallback json(LabEle &ele)
    {
        //cout << "ele.listV->length---" << ele.listV->length() << endl;
        if (ele.listV->length() == 1)
        {
            return [](shared_ptr<Frame> env) -> Lab_Ptr
            {
                std::vector<Lab_Ptr> consList;
                auto new_cons = make_shared<LabEle>("json", consList);
                return new_cons;
            };
        }
        std::vector<Lab_Ptr> cons_list = ele.listV->cdr()->listV->eles;

        std::vector<LabCallback> cons_list_callbacks;
        for (Lab_Ptr &oneCons : cons_list)
        {
            cons_list_callbacks.push_back(explainObj_entry(*oneCons));
        };
        return [&ele, cons_list_callbacks](shared_ptr<Frame> env) -> Lab_Ptr
        {
            std::vector<Lab_Ptr> consList;
            for (LabCallback cons_call : cons_list_callbacks)
            {
                consList.push_back(cons_call(env));
            };

            auto new_cons = make_shared<LabEle>("json", consList);
            return new_cons;
        };
    }

    LabCallback app(LabEle &ele)
    {
        if (ele.listV->eles.size() > 1)
        {
            Lab_Ptr temp = ele.listV->car();
            if (global_env->father_frame->is_key_exist(*temp))
            {
                Lab_Ptr true_macro = global_env->father_frame->look_vars_frame(*temp);
                Lab_Ptr macro_operands = ele.listV->cdr();
                //宏的逻辑
                macroCallBack &macroCallBackBody = true_macro->functionV->macroCallBackBody;
                Lab_Ptr macroReusult = macroCallBackBody(macro_operands);
                return [macroReusult](shared_ptr<Frame> env) mutable -> Lab_Ptr
                {
                    //将获取到得字符串，进行运算获取到替换结果
                    return explainObj_entry(*macroReusult)(env);
                };
            }
            else
            {

                LabCallback operate = explainObj_entry(*temp);
                std::vector<LabCallback> operands_callbacks;
                Lab_Ptr operands = ele.listV->cdr();
                std::vector<Lab_Ptr> operands_list = operands->listV->eles;
                for (Lab_Ptr &operand : operands_list)
                {
                    operands_callbacks.push_back(explainObj_entry(*operand));
                };

                return [ele, operate, operands, operands_callbacks](shared_ptr<Frame> env) mutable -> Lab_Ptr
                {
                    Lab_Ptr true_operate = operate(env);
                    if (true_operate->type == LabTypes::function_type)
                    {
                        std::vector<Lab_Ptr> true_operands;
                        for (LabCallback operand_callback : operands_callbacks)
                        {
                            //operand_callback(env);
                            true_operands.push_back(operand_callback(env));
                        };
                        Lab_Ptr result = eval::eval_app(true_operate, true_operands);
                        return result;
                    }
                    else if (true_operate->type == LabTypes::class_type)
                    {
                        cout << "app--class_type------go" << endl;
                        std::vector<Lab_Ptr> true_operands{};
                        for (LabCallback operand_callback : operands_callbacks)
                        {
                            //operand_callback(env);
                            true_operands.push_back(operand_callback(env));
                        };
                        Lab_Ptr result = eval::eval_app(true_operate, true_operands);
                        return result;
                    }
                    else
                    {

                        cout << "app_type错误" << true_operate->type << endl;
                        ele.show();
                    };
                };
            };
        }
        else
        {
            //无参数函数的执行；
        };
    };

};

LabCallback explainObj_entry(LabEle &parsed_code)
{
    //std::cout << "explainObj_entry::-------" << parsed_code.type << std::endl;
    if (parsed_code.type == LabTypes::list_type)
    {
        Lab_Ptr checkType_LabEle = parsed_code.listV->car();
        if (checkType_LabEle->type == LabTypes::keyword_type)
        {
            switch (checkType_LabEle->keyWordV->keywordType)
            {
            case keywordType::define:
                return analyze::define(parsed_code);
                break;
            case keywordType::quote:
                return analyze::quote(parsed_code);
                break;
            case keywordType::set:
                return analyze::set(parsed_code);
                break;
            case keywordType::get:
                return analyze::get(parsed_code);
                break;
            case keywordType::_if:
                return analyze::_if(parsed_code);
                break;
            case keywordType::cons:
                return analyze::cons(parsed_code);
                break;
            case keywordType::json:
                return analyze::json(parsed_code);
                break;
            case keywordType::array:
                return analyze::array(parsed_code);
                break;
            case keywordType::sleep:
                return analyze::sleep(parsed_code);
                break;
            case keywordType::begin:
                return analyze::begin(parsed_code);
                break;
            /* case keywordType::let:
                break; */
            case keywordType::lambda:
                return analyze::lambda(parsed_code);
                break;
            case keywordType::_class:
                return analyze::_class(parsed_code);
                break;
            case keywordType::_new:
                return analyze::_new(parsed_code);
                break;
            case keywordType::define_syntax:
                return analyze::defineSyntax(parsed_code);
                break;
            default:

                std::cout << "--------?what?-----" << checkType_LabEle->keyWordV->keywordType << std::endl;
            }
        }
        else
        {
            return analyze::app(parsed_code);
        }
    }
    else
    {
        switch (parsed_code.type)
        {
        case LabTypes::undefined_type:
            return analyze::number(parsed_code);
            break;
        case LabTypes::number_type:
            return analyze::number(parsed_code);
            break;
        case LabTypes::string_type:
            return analyze::_string(parsed_code);
            break;
        case LabTypes::boolean_type:
            return analyze::boolean(parsed_code);
            break;
        case LabTypes::variable_type:
            return analyze::variable(parsed_code);
            break;
        case LabTypes::list_type:
            return analyze::app(parsed_code);
            break;
        default:
            cout << "--?---" << endl;
            parsed_code.show();
            std::cout << "--------?what?-----" << parsed_code.type << std::endl;
            break;
        };
    };
};
// #endif

//g++ main.cpp -o main  "f:\\tryMyBest\\loveAsBefore_gcc\\LabComponent\\main"
