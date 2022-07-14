//
// Created by 潘峰 on 2022/7/8.
//

#ifndef LAB_LABENTRY_H
#define LAB_LABENTRY_H

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
#include "./define/Lab_insertType.cpp"
#include "./analyze/index.cpp"
#include "./frame/frame.h"
#include "./frame/frame.cpp"
#include "./readfile/read.h"
#include "./types/Lab_number.cpp"
#include "./global_vars/global_vars.cpp"
#include "./task/task.cpp"
#include "./types/LabEle.cpp"
#include "./types/LabEleTool.cpp"

#include "./insertTypes/Test.h"

LabEle *labEntry(string strCode);

#endif //LAB_LABENTRY_H
