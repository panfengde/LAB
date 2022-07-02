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
#include "./LabEle.h"

using namespace std;

class LabEle;

class Lab_cons :  public LabEle
{
private:
public:
  LabEle *container;
  pair<LabEle *, LabEle *> key_value;
  Lab_cons();
  ~Lab_cons();
  Lab_cons(LabEle * key, LabEle * value);
  LabEle * car()
  {
    return key_value.first;
  };
  LabEle * cdr()
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