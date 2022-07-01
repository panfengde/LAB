#ifndef TYPEGLOBAL
#define TYPEGLOBAL

#include <vector>
#include <string>
#include <memory>
#include <functional>
using namespace std;

class LabEle;
class Frame;
typedef shared_ptr<LabEle> Lab_Ptr;

typedef function<LabEle(vector<LabEle>)> function_define;

typedef function<shared_ptr<LabEle>(shared_ptr<Frame>)> LabCallback;

typedef function<Lab_Ptr(Lab_Ptr)> macroCallBack;

typedef function<Lab_Ptr(vector<Lab_Ptr> &)> originalFn;

#endif