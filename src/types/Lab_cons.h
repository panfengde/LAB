#ifndef LABCONS
#define LABCONS

#include "../LabTypes.h"
#include "../parseCode/codeStruct.h"

//#include "./Lab_cons.h"
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include "./Base.h"

using namespace std;

class LabEle;

class Lab_cons : public Base
{
private:
public:
  LabTypes::LabTypes type = LabTypes::cons_type;
  LabEle *container;
  pair<Lab_Ptr, Lab_Ptr> key_value;
  Lab_cons();
  ~Lab_cons();
  Lab_cons(Lab_Ptr key, Lab_Ptr value);
  Lab_Ptr car()
  {
    return key_value.first;
  };
  Lab_Ptr cdr()
  {
    return key_value.second;
  };
  std::string value();
  void show()
  {
    std::cout << value() << std::endl;
  }
};

#endif