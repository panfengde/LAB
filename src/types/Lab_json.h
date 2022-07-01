#ifndef LABJSON
#define LABJSON

#include "../LabTypes.h"
#include "../parseCode/codeStruct.h"

//#include "./Lab_cons.h"
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include "./Base.h"

using namespace std;

class LabEle;
class Lab_cons;

class Lab_json : public Base
{
private:
public:
  LabTypes::LabTypes type = LabTypes::json_type;
  LabEle *container;
  Lab_json();
  Lab_json(string);
  Lab_json(vector<Lab_Ptr>);
  //变量存储的字典；
  map<std::string, Lab_Ptr> key_value;
  string stringify();
  std::string value();
  Lab_Ptr &get(LabEle var);
  void show()
  {
    std::cout << value() << std::endl;
  }
  ~Lab_json();
};

#endif