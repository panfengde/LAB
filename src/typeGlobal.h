#ifndef TYPEGLOBAL
#define TYPEGLOBAL

#include <vector>
#include <string>
#include <memory>
#include <functional>

using namespace std;

class LabEle;

class Frame;

class Lab_undefined;

class CodeUnit;

//typedef shared_ptr<Lab_undefined> shared_undefined;

typedef LabEle *Lab_Ptr;

typedef shared_ptr<CodeUnit> CodeUnit_Ptr;

typedef function<LabEle(vector<LabEle>)> function_define;

typedef function<LabEle *(Frame *)> LabCallback;

typedef function<LabEle *(LabEle *)> macroCallBack;

typedef function<LabEle *(vector<LabEle *> &)> originalFn;

#endif