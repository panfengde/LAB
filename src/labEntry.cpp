#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <initializer_list>
#include <memory>
#include "./LabTypes.h"
#include "./typeGlobal.h"
#include "./parseCode/codeStruct.h"
//#include "./parseCode/parseExp.cpp"
#include "./parseCode/parseExpNew.cpp"

#include "./types/LabEle.h"
#include "./types/LabEleTool.h"
#include "./define/Lab_list_define.h"
#include "./define/Lab_class_define.h"
#include "./define/Lab_cons_define.h"
#include "./define/Lab_json_define.h"
#include "./define/LabEle_define.h"
#include "./define/LabEle_function_define.h"
#include "./analyze/index.cpp"
#include "./frame/frame.h"
#include "./frame/frame.cpp"
#include "./readfile/read.cpp"
#include "./types/Lab_number.cpp"
#include "./global_vars/global_vars.cpp"
#include "./task/task.cpp"
#include "./types/LabEle.cpp"
#include "./types/LabEleTool.cpp"

using namespace std;

//typedef std::function<LabEle(Frame&)> LabCallback;
Lab_Ptr labEntry(string strCode) {

    //string strCode = read("./Lab/test.lab");
    //string strCode = read("./Lab/town.json");
    //strCode = "( begin " + strCode + " )";

    clock_t startTime, endTime;
    startTime = clock(); //计时开始

    shared_ptr<CodeUnit> oneExp = codeTxt_to_list(strCode);
    auto go = LabEleTool::createLabEle(oneExp);

    // go->show();
    endTime = clock(); //计时结束
    std::cout << "解析字符串时间: " << (double) (endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    clock_t startTime2, endTime2;
    startTime2 = clock(); //计时开始

    std::cout << "开始分析" << std::endl;
    LabCallback call_go = explainObj_entry(*go);
    std::cout << "开始执行" << std::endl;
    LabEle * result = call_go(global_env);
    std::cout << "执行结果：" << std::endl;
    std::cout << result->stringify() << endl;
    endTime2 = clock(); //计时开始
    std::cout << "执行代码时间: " << (double) (endTime2 - startTime2) / CLOCKS_PER_SEC << "s" << endl;
    std::cout << "总时间: " << (double) (endTime2 - startTime) / CLOCKS_PER_SEC << "s" << endl;
    std::cout << "结束" << std::endl;
    return result;
    //return LabEleTool::createLabEle();

}
