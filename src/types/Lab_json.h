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
#include "./LabEle.h"

using namespace std;

class LabEle;
class Lab_cons;

class Lab_json :  public LabEle
{
private:
public:
  LabEle *container;
  Lab_json();
  Lab_json(string);
  Lab_json(vector<LabEle*>);
  //变量存储的字典；
  map<std::string, LabEle*> key_value;
  string stringify();
  std::string value();
  LabEle* get(LabEle* var);
  void show()
  {
    std::cout << value() << std::endl;
  }
  ~Lab_json();
};

#endif