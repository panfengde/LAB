//
// Created by 潘峰 on 2022/7/7.
//

#ifndef LAB_TEST_H
#define LAB_TEST_H

#include <map>
#include <utility>
#include <types/Lab_insertType.h>

LabEle *Test() {
    auto InsetObj = new Lab_insertType();
    InsetObj->property = new Frame();

    originalFn testMethod = [](vector<LabEle *> params) -> LabEle * {
        LabEle *result = LabEleTool::createLabEle("hello 插件");
        cout << "test___" << params[0]->stringV()->value << endl;
        return result;
    };
    LabEle *testMethod_lab = LabEleTool::createLabEle(testMethod);
    map<string, LabEle *> name_Methods;
    InsetObj->property->var_value.insert(pair<string, LabEle *>(string("test"), testMethod_lab));

    return InsetObj;
}


#endif //LAB_TEST_H
