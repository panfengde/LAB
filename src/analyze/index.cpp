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
    LabEle *findCondition(LabEle *params, LabEle *conditions);

    bool paramsArgsMatch(LabEle *var_args, LabEle *params);

    LabEle *replace(LabEle *vars, LabEle *BranchTemplate, LabEle *params);

    void add(LabEle *origin, std::pair<string, LabEle *> get_cons);

    LabEle *loopTemplate(
        LabEle *oneTemplate, LabEle *vars, LabEle *params,
        LabEle *result = LabEleTool::createLabEle(vector<LabEle *>() = {}));

    std::pair<string, LabEle *> loopWord(LabEle *word, LabEle *vars, LabEle *params);

    LabEle *replaceMacro(LabEle *conditions_list, LabEle *params);
    //------申明

    LabEle *findCondition(LabEle *params, LabEle *conditions)
    {
        if (conditions->type != LabTypes::undefined_type)
        {

            LabEle *this_conditon = conditions->listV()->car();
            LabEle *rest_condition = conditions->listV()->cdr();
            LabEle *var_args = this_conditon->listV()->car()->listV()->cdr();

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
            auto result = LabEleTool::createLabEle();
            return result;
        }
    }

    bool paramsArgsMatch(LabEle *var_args, LabEle *params)
    {
        if (var_args->type == LabTypes::list_type && params->type == LabTypes::list_type)
        {
            LabEle *_temp = var_args->listV()->last_items();

            if (_temp->type != LabTypes::list_type && _temp->variableV()->value.substr(0, 3) == "...")
            {
                auto length = params->listV()->length();
                if (length >= var_args->listV()->length() - 1)
                {
                    return length > 1 ? (macroFn::paramsArgsMatch(var_args->listV()->car(), params->listV()->car()) &&
                                         macroFn::paramsArgsMatch(var_args->listV()->cdr(), params->listV()->cdr()))
                                      : (macroFn::paramsArgsMatch(var_args->listV()->car(), params->listV()->car()));
                }
                else
                {
                    return false;
                }
            }
            else
            {

                auto length = params->listV()->length();
                if (params->listV()->length() == var_args->listV()->length())
                {
                    return length > 1 ? (macroFn::paramsArgsMatch(var_args->listV()->car(), params->listV()->car()) &&
                                         macroFn::paramsArgsMatch(var_args->listV()->cdr(), params->listV()->cdr()))
                                      : (macroFn::paramsArgsMatch(var_args->listV()->car(), params->listV()->car()));
                }
                else
                {
                    return false;
                }
            }
        }
        else if (var_args->type != LabTypes::list_type && var_args->value.substr(0, 3) == "...")
        {
            return true;
        }
        else
        {

            return params->type != LabTypes::undefined_type;
        }
    }

    LabEle *replace(LabEle *vars, LabEle *BranchTemplate, LabEle *params)
    {
        return macroFn::loopTemplate(BranchTemplate, vars, params);
    }

    void add(LabEle *origin, std::pair<string, LabEle *> get_cons)
    {
        if (get_cons.second->type != LabTypes::undefined_type)
        {
            if (get_cons.first == "...")
            {
                auto eles = get_cons.second->listV()->eles;
                origin->listV()->eles.insert(
                    origin->listV()->eles.end(),
                    std::make_move_iterator(eles.begin()),
                    std::make_move_iterator(eles.end()));
            }
            else if (get_cons.first == "word" || get_cons.first == "no_find")
            {
                origin->listV()->eles.push_back(get_cons.second);
            }
            else if (get_cons.first == "none")
            {
            };
        }
    }

    LabEle *loopTemplate(LabEle *oneTemplate, LabEle *vars, LabEle *params, LabEle *result)
    {
        if (oneTemplate->type != LabTypes::list_type)
        {
            if (oneTemplate->type == LabTypes::undefined_type)
            {
            }
            else
            {
                add(result, macroFn::loopWord(oneTemplate->listV()->car(), vars, params));
            }
        }
        else
        {
            if (tools::is_car_list(oneTemplate))
            {
                result->listV()->eles.push_back(loopTemplate(oneTemplate->listV()->car(), vars, params));
                loopTemplate(oneTemplate->listV()->cdr(), vars, params, result);
            }
            else
            {
                add(result, macroFn::loopWord(oneTemplate->listV()->car(), vars, params));
                loopTemplate(oneTemplate->listV()->cdr(), vars, params, result);
            }
        }
        return result;
    }

    std::pair<string, LabEle *> loopWord(LabEle *word, LabEle *vars, LabEle *params)
    {

        if (vars->type != LabTypes::list_type)
        {
            //
            return pair<string, LabEle *>(string("no_find"), word);
        }
        else
        {

            if (vars->listV()->car()->type == LabTypes::list_type)
            {
                //cout << "---hhhhhhhh————————" << word->value() << endl;
                pair<string, LabEle *> temp = macroFn::loopWord(word, vars->listV()->car(), params->listV()->car());

                if (temp.first == "no_find")
                {
                    return macroFn::loopWord(word, vars->listV()->cdr(), params->listV()->cdr());
                }
                else
                {
                    return temp;
                }
            }
            else
            {
                //cout << "---xxxxxxxx———————" << word->value() << endl;
                if (word->value == vars->listV()->car()->value)
                {

                    //cout << "---找到了————————" << word->value() << endl;

                    if (word->value.substr(0, 3) == "...")
                    {

                        if (params->type == LabTypes::list_type)
                        {
                            return pair<string, LabEle *>("...", params);
                        }
                        else
                        {
                            if (params->type == LabTypes::undefined_type)
                            {
                                //特殊情况，...对应空
                                //可能会有问题
                                return pair<string, LabEle *>("none", LabEleTool::createLabEle());
                            }
                            else
                            {
                                return pair<string, LabEle *>("word", params);
                            }
                        }
                    }
                    else
                    {

                        if (params->type == LabTypes::list_type)
                        {
                            return pair<string, LabEle *>("word", params->listV()->car());
                        }
                        else
                        {
                            if (params->type == LabTypes::undefined_type)
                            {
                                //特殊情况，...对应空
                                //可能会有问题
                                return pair<string, LabEle *>("none", LabEleTool::createLabEle());
                            }
                            else
                            {
                                return pair<string, LabEle *>("word", params->listV()->car());
                            }
                        }
                    }
                }
                else
                {
                    if (params->type == LabTypes::undefined_type)
                    {
                        return pair<string, LabEle *>("no_find", word);
                    }
                    else
                    {
                        return macroFn::loopWord(word, vars->listV()->cdr(), params->listV()->cdr());
                    }
                }
            };
        }
    }

    LabEle *replaceMacro(LabEle *conditions_list, LabEle *params)
    {
        /*
        (define-syntax nil!
            (syntax-rules ()
            ((_ x)(set! x '()))
            ((_ x a)(set! x a))
            )
        )
        */

        LabEle *conditon = findCondition(params, conditions_list);

        if (conditon->type != LabTypes::list_type)
        {
            throw "宏错误";
        }
        else
        {
            LabEle *oneTemplate = conditon->listV()->cdr()->listV()->car();
            LabEle *vars = conditon->listV()->car()->listV()->cdr();
            LabEle *result = macroFn::replace(vars, oneTemplate, params);

            return result;
        }
    }

}

namespace eval
{
    LabEle *eval_app(LabEle *&operate, std::vector<LabEle *> &operands)
    {
        //operate
        //((lambda (x) (+ x 1)) 100)
        if (operate->type == LabTypes::function_type)
        {
            Lab_function *fun = operate->functionV();
            Lab_class *_class = operate->classV();
            if (fun->funType == funType::original)
            {
                return fun->original_fn(operands);
            }
            else
            {

                LabCallback &function_body = fun->ananlyzed_body;
                vector<LabEle *> &function_args = fun->args;
                Frame *newEnv = new Frame(function_args, operands);
                Frame *defineEnv = fun->define_env;
                Frame *thisEnv = fun->_this;
                newEnv->extend_env(defineEnv);

                //给函数作用域植入this
                LabEle *_this = LabEleTool::createLabEle(std::string("this"));
                LabEle *this_env = LabEleTool::createLabEle(thisEnv);
                newEnv->insert_key_value(_this, this_env);
                return function_body(newEnv);
            }
        }
        else if (operate->type == LabTypes::class_type)
        {
            cout << " LabTypes::class_type--------" << endl;
            vector<LabEle *> class_args = operate->classV()->args;
            vector<LabEle *> class_params = operands;

            LabCallback analyze_constructor = operate->classV()->analyze_constructor;
            Frame *class_define_env = operate->classV()->define_env;
            Frame *prototype_env = operate->classV()->prototype;
            Frame *example_env = new Frame(class_args, class_params);

            example_env->extend_env(class_define_env);
            example_env->extend_prototype(prototype_env);

            LabEle *_this = LabEleTool::createLabEle(std::string("this"));
            LabEle *example_env_LabEle = LabEleTool::createLabEle(example_env);
            example_env->insert_key_value(_this, example_env_LabEle);
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
        return [=](Frame *env) -> LabEle *
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

    LabCallback sequences_analyze(vector<LabEle *> eles)
    {
        //std::vector<LabEle> &eles = ele.listV()->eles;
        std::vector<LabCallback> analyzed_sequences;
        for (LabEle *ele : eles)
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
        auto new_number = LabEleTool::createLabEle(to_string(ele.numberV()->value));
        return [new_number](Frame *env) -> LabEle *
        {
            // cout << ele.numberV()->value << endl;
            return new_number;
            // auto new_number =  LabEleTool::createLabEle();
            // //没有深度拷贝
            // //LabEle *new_number = new LabEle(std::string("100"));
            // *new_number = ele;
            // //new_number->clone(ele);
            // return new_number;
        };
    }

    LabCallback _string(LabEle &ele)
    {
        return [ele](Frame *env) mutable -> LabEle *
        {
            auto new_string = LabEleTool::createLabEle();
            //没有深度拷贝
            *new_string = ele;
            //new_string->clone(ele);
            return new_string;
        };
    }

    LabCallback boolean(LabEle &ele)
    {
        return [&ele](Frame *env) -> LabEle *
        {
            //没有深度拷贝
            auto new_string = LabEleTool::createLabEle();
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

        LabEle *syntax_body = ele.listV()->cdr()->listV()->cdr()->listV()->car();
        LabEle *syntax_name = ele.listV()->cdr()->listV()->car();
        if (syntax_body->listV()->car()->variableV()->value == "syntax-rules")
        {
            LabEle *syntax_condition = ele.listV()->cdr()->listV()->cdr()->listV()->car()->listV()->cdr()->listV()->cdr();
            // to-d
            /**
             *  1. 函数构造函数要扩展macroCallBack
             *  2. 参数长度可能不固定，函数怎么处理的，是否要修改
             *  3. 空环境的创建
             *  4. 宏替换的整理
             **/
            macroCallBack _result = [syntax_condition](LabEle *params) mutable -> LabEle *
            {
                LabEle *result = macroFn::replaceMacro(syntax_condition, params);

                return result;
            };
            LabEle *parse_result = LabEleTool::createLabEle(_result);
            global_env->father_frame->insert_key_value(
                syntax_name,
                parse_result);

            return [](Frame *env) mutable -> LabEle * {
                return LabEleTool::createLabEle();
            };

            /* return [syntax_name, syntax_body](Frame* env) mutable -> LabEle*
            {
                env->insert_key_value(
                    *syntax_name,
                    syntax_body);
                cout << "defineSyntax-ok" << endl;
                return  LabEleTool::createLabEle();
            }; */
        }
        else
        {
            throw "宏的定义需要syntax-rules";
        }
    }

    LabCallback variable(LabEle &ele)
    {
        return [&ele](Frame *env) mutable -> LabEle *
        {
            LabEle *findvar = env->look_variable_env(new LabEle(ele));
            return findvar;
            /* int a = 100;
            auto _result =  LabEleTool::createLabEle(a);
            return *_result; */
        };
    }

    LabCallback _if(LabEle &ele)
    {

        LabEle *if_info = ele.listV()->cdr();

        LabEle *pre = if_info->listV()->car();

        LabEle *true_action = if_info->listV()->cdr()->listV()->car();
        LabEle *false_action = if_info->listV()->cdr()->listV()->cdr();
        if (false_action->type != LabTypes::undefined_type)
        {
            false_action = false_action->listV()->car();
        }
        LabCallback pre_back = explainObj_entry(*pre);
        LabCallback true_action_back = explainObj_entry(*true_action);
        LabCallback false_action_back = explainObj_entry(*false_action);
        return [pre_back, true_action_back, false_action_back](Frame *env) mutable -> LabEle *
        {
            LabEle *pre_result = pre_back(env);
            if (pre_result->type == LabTypes::boolean_type)
            {
                if (pre_result->booleanV()->value)
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
                if (pre_result->numberV()->value != long(0))
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
                if (pre_result->stringV()->value != "")
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
        // LabCallback true_action = explainObj_entry(ele.listV()->cdr()->listV()->car());
        // LabCallback false_action = explainObj_entry(ele.listV()->cdr()->listV()->cdr()->listV()->car());
    }

    LabCallback quote(LabEle &ele)
    {
        //这里是错误的
        LabEle *findvar = ele.listV()->cdr()->listV()->car();
        return [findvar](Frame *env) -> LabEle * {
            return findvar;
        };
    }

    LabCallback define(LabEle &ele)
    {
        LabEle *LabEle_info = ele.listV()->cdr();
        LabEle *nameOrRgs = LabEle_info->listV()->car();
        LabEle *body = LabEle_info->listV()->cdr();
        if (nameOrRgs->type == LabTypes::list_type)
        {
            LabEle *name = nameOrRgs->listV()->car();
            vector<LabEle *> args = nameOrRgs->listV()->cdr()->listV()->eles;
            LabCallback analyzed_body = analyze::sequences_analyze(body->listV()->eles);
            return [args, analyzed_body, name](Frame *env) mutable -> LabEle *
            {
                LabEle *_function = LabEleTool::createLabEle(args, analyzed_body, env);
                env->insert_key_value(name, _function);
                return LabEleTool::createLabEle();
            };
        }
        else
        {
            LabEle *name = nameOrRgs;
            LabEle *value = body->listV()->car();

            LabCallback valueCallback = explainObj_entry(*value);

            return [name, valueCallback](Frame *env) mutable -> LabEle *
            {
                LabEle *truevalue = valueCallback(env);
                env->insert_key_value(name, truevalue);
                return LabEleTool::createLabEle();
            };
        };
    }

    LabCallback set(LabEle &ele)
    {
        LabEle *setInfo = ele.listV()->cdr();
        LabEle *name = setInfo->listV()->car();

        LabEle *value = setInfo->listV()->cdr()->listV()->car();
        LabCallback nameCallback = explainObj_entry(*name);
        LabCallback valueCallback = explainObj_entry(*value);
        // cout << "go-set" << name.variableV()->value << endl;
        return [=](Frame *env) mutable -> LabEle *
        {
            LabEle *trueObj = nameCallback(env);
            LabEle *truevalue = valueCallback(env);

            // trueObj->bindQuote(truevalue);
            return trueObj;
            //return truevalue;
        };
    }

    LabCallback get(LabEle &ele)
    {
        LabEle *getInfo = ele.listV()->cdr();
        LabEle *name = getInfo->listV()->car();
        LabEle *value = getInfo->listV()->cdr()->listV()->car();

        LabCallback nameCallback = explainObj_entry(*name);

        LabCallback valueCallback = explainObj_entry(*value);
        return [&ele, nameCallback, valueCallback](Frame *env) mutable -> LabEle *
        {
            LabEle *trueObj = nameCallback(env);
            LabEle *trueKey = valueCallback(env);
            LabEle *result = trueObj->get(trueKey);
            if (trueObj->type == LabTypes::frame_type && result->type == LabTypes::function_type)
            {
                result->functionV()->_this = trueObj->frameV();
                cout << "_this_____________________" << endl;
            }
            return result;
        };
    }

    LabCallback begin(LabEle &ele)
    {
        auto listV = ele.listV();
        auto bodyListV = (*(listV->cdr())).listV();
        return analyze::sequences_analyze(bodyListV->eles);
    }

    // LabCallback _let(LabEle &ele)
    // {
    //     LabEle* let_info = ele.listV()->cdr();
    //     vector<LabEle*> &arg_partment = let_info->listV()->car()->listV()->eles; //.cdr.car
    //     LabEle* body_sequence = let_info->listV()->cdr();
    //     make_shared<vector<LabEle*>> args_names{};
    //     make_shared<vector<LabEle*>> args_bodys{};

    //     for (LabEle* temp : arg_partment)
    //     {
    //         args_names->push_back(temp->listV()->car());
    //         args_bodys->push_back(temp->listV()->cdr()->listV()->car());
    //     };

    //     LabEle* _result =  LabEleTool::createLabEle(*args_names, analyzed_body, env);
    // }

    LabCallback lambda(LabEle &ele)
    {
        LabEle *lambdaInfo = ele.listV()->cdr();
        auto args = make_shared<vector<LabEle *>>(lambdaInfo->listV()->car()->listV()->eles);
        //cout << "生成lambda--参数--" << args->size() << endl;
        LabEle *body = lambdaInfo->listV()->cdr();
        LabCallback analyzed_body = analyze::sequences_analyze(body->listV()->eles);

        return [args, analyzed_body, ele](Frame *env) -> LabEle *
        {
            LabEle *_result = LabEleTool::createLabEle(*args, analyzed_body, env);

            //cout << "生成lambda" << endl;
            //cout << "生成lambda--参数--" << _result->functionV()->args.size() << endl;

            return _result;
        };
    }

    LabCallback sleep(LabEle &ele)
    {
        // (setTimeout (+ 1 1) 1000)
        LabEle *setTimeoutInfo = ele.listV()->cdr();
        LabEle *callBackBody = setTimeoutInfo->listV()->car();
        LabEle *callBackTime = setTimeoutInfo->listV()->cdr()->listV()->car();

        LabCallback analyzed_body = explainObj_entry(*callBackBody);
        LabCallback callBackTime_body = explainObj_entry(*callBackTime);

        return [analyzed_body, callBackTime_body](Frame *env) -> LabEle *
        {
            int time = callBackTime_body(env)->numberV()->value;

            global_labTasks->insertTask(analyzed_body, env, time);
            //cout << "生成lambda" << endl;
            //cout << "生成lambda--参数--" << _result->functionV()->args.size() << endl;

            // return _result;
            return LabEleTool::createLabEle();
        };
    }

    LabCallback _new(LabEle &ele)
    {
        cout << "_new——start" << endl;
        LabEle *trueExp = ele.listV()->cdr();
        LabCallback classParse = explainObj_entry(*trueExp);
        cout << "_new" << endl;
        return [classParse](Frame *env) mutable -> LabEle * {
            return classParse(env);
        };
    }

    LabCallback _class(LabEle &ele)
    {

        LabEle *name = ele.listV()->cdr()->listV()->car();
        LabEle *constructor = ele.listV()->cdr()->listV()->cdr()->listV()->car();
        auto constructor_args = make_shared<vector<LabEle *>>(
            constructor->listV()->cdr()->listV()->car()->listV()->eles);
        // LabEle* constructor_args = constructor->listV()->cdr()->listV()->car();
        LabEle *constructor_body = constructor->listV()->cdr()->listV()->cdr();
        LabEle *_this = LabEleTool::createLabEle(std::string("this"));
        constructor_body->listV()->eles.push_back(_this);
        LabEle *methods = ele.listV()->cdr()->listV()->cdr()->listV()->cdr();

        LabCallback ananlyzed_constructor_body = analyze::sequences_analyze(constructor_body->listV()->eles);
        LabCallback ananlyzed_methods = analyze::sequences_analyze(methods->listV()->eles);
        cout << "parse_class——————" << endl;
        return [name, constructor_args, ananlyzed_methods, ananlyzed_constructor_body](
                   Frame *env) mutable -> LabEle *
        {
            Frame *prototype_env = new Frame();
            prototype_env->extend_env(env);
            ananlyzed_methods(prototype_env);

            cout << "parse_class_3" << endl;
            LabEle *constructor_class = LabEleTool::createLabEle(env, prototype_env, *constructor_args,
                                                                 ananlyzed_constructor_body);
            env->insert_key_value(name, constructor_class);
            return LabEleTool::createLabEle();
        };
    }

    LabCallback cons(LabEle &ele)
    {
        LabEle *first = ele.listV()->cdr()->listV()->car();
        LabEle *second = ele.listV()->cdr()->listV()->cdr()->listV()->car();
        LabCallback firstValueCall = explainObj_entry(*first);
        LabCallback secondValueCall = explainObj_entry(*second);
        return [&ele, firstValueCall, secondValueCall](Frame *env) -> LabEle *
        {
            LabEle *firstValue = firstValueCall(env);
            LabEle *secondValue = secondValueCall(env);
            //secondValue->show();
            pair<LabEle *, LabEle *> theCons{firstValue, secondValue};
            auto new_cons = LabEleTool::createLabEle(theCons);
            //cout << "ok--" << endl;
            return new_cons;
        };
    }

    LabCallback array(LabEle &ele)
    {

        //cout << "array->length---" << ele.listV()->length() << endl;
        if (ele.listV()->length() == 1)
        {
            return [](Frame *env) -> LabEle *
            {
                std::vector<LabEle *> array;
                auto new_cons = LabEleTool::createLabEle(array);
                return new_cons;
            };
        }

        std::vector<LabEle *> array_data = ele.listV()->cdr()->listV()->eles;
        std::vector<LabCallback> array_data_callbacks;
        for (LabEle *&one_data : array_data)
        {
            array_data_callbacks.push_back(explainObj_entry(*one_data));
        };
        return [&ele, array_data_callbacks](Frame *env) -> LabEle *
        {
            std::vector<LabEle *> array;
            for (LabCallback data_call : array_data_callbacks)
            {
                array.push_back(data_call(env));
            };
            auto new_array = LabEleTool::createLabEle(array);
            return new_array;
        };
    }

    LabCallback json(LabEle &ele)
    {
        //cout << "ele.listV()->length---" << ele.listV()->length() << endl;
        if (ele.listV()->length() == 1)
        {
            return [](Frame *env) -> LabEle *
            {
                std::vector<LabEle *> consList;
                auto new_cons = LabEleTool::createLabEle("json", consList);
                return new_cons;
            };
        }
        std::vector<LabEle *> cons_list = ele.listV()->cdr()->listV()->eles;

        std::vector<LabCallback> cons_list_callbacks;
        for (LabEle *&oneCons : cons_list)
        {
            cons_list_callbacks.push_back(explainObj_entry(*oneCons));
        };
        return [&ele, cons_list_callbacks](Frame *env) -> LabEle *
        {
            std::vector<LabEle *> consList;
            for (LabCallback cons_call : cons_list_callbacks)
            {
                consList.push_back(cons_call(env));
            };

            auto new_cons = LabEleTool::createLabEle("json", consList);
            return new_cons;
        };
    }

    LabCallback app(LabEle &ele)
    {
        if (ele.listV()->eles.size() > 1)
        {
            LabEle *temp = ele.listV()->car();
            if (global_env->father_frame->is_key_exist(temp))
            {
                LabEle *true_macro = global_env->father_frame->look_vars_frame(temp);
                LabEle *macro_operands = ele.listV()->cdr();
                //宏的逻辑
                macroCallBack &macroCallBackBody = true_macro->functionV()->macroCallBackBody;
                LabEle *macroReusult = macroCallBackBody(macro_operands);
                return [macroReusult](Frame *env) mutable -> LabEle *
                {
                    //将获取到得字符串，进行运算获取到替换结果
                    return explainObj_entry(*macroReusult)(env);
                };
            }
            else
            {

                LabCallback operate = explainObj_entry(*temp);
                std::vector<LabCallback> operands_callbacks;
                LabEle *operands = ele.listV()->cdr();
                std::vector<LabEle *> operands_list = operands->listV()->eles;
                for (LabEle *&operand : operands_list)
                {
                    operands_callbacks.push_back(explainObj_entry(*operand));
                };

                return [ele, operate, operands, operands_callbacks](Frame *env) mutable -> LabEle *
                {
                    LabEle *true_operate = operate(env);
                    if (true_operate->type == LabTypes::function_type)
                    {
                        std::vector<LabEle *> true_operands;
                        for (LabCallback operand_callback : operands_callbacks)
                        {
                            //operand_callback(env);
                            true_operands.push_back(operand_callback(env));
                        };
                        LabEle *result = eval::eval_app(true_operate, true_operands);
                        return result;
                    }
                    else if (true_operate->type == LabTypes::class_type)
                    {
                        cout << "app--class_type------go" << endl;
                        std::vector<LabEle *> true_operands{};
                        for (LabCallback operand_callback : operands_callbacks)
                        {
                            //operand_callback(env);
                            true_operands.push_back(operand_callback(env));
                        };
                        LabEle *result = eval::eval_app(true_operate, true_operands);
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
    std::cout << "explainObj_entry::-------" << parsed_code.type << std::endl;
    if (parsed_code.type == LabTypes::list_type)
    {
        auto listV = parsed_code.listV();
        LabEle *checkType_LabEle = listV->car();
        if (checkType_LabEle->type == LabTypes::keyword_type)
        {
            auto keyWordV = checkType_LabEle->keyWordV();
            switch (keyWordV->keywordType)
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
                std::cout << "--------?what?-----" << checkType_LabEle->keyWordV()->keywordType << std::endl;
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
