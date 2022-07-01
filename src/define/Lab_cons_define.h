#ifndef LABElE_CONS_DEFINE
#define LABElE_CONS_DEFINE

#include <memory>
#include <vector>
#include <string>
#include "../LabTypes.h"
#include "../types/LabEle.h"
#include "../types/Lab_cons.h"
#include "../parseCode/codeStruct.h"
#include "../utils/tools.h"

Lab_cons::~Lab_cons()
{
}

Lab_cons::Lab_cons(Lab_Ptr key, Lab_Ptr value)
{
  key_value.first = key;
  key_value.second = value;
};

std::string Lab_cons::value()
{
  string result = "( ";
  result += (key_value.first->value() + " · " + key_value.second->value());
  result += ")";
  return result;
}


#endif