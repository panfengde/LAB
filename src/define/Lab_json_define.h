#ifndef LABElE_JSON_DEFINE
#define LABElE_JSON_DEFINE

#include <memory>
#include <vector>
#include <string>
#include "../LabTypes.h"
#include "../types/LabEle.h"
#include "../types/Lab_cons.h"
#include "../types/Lab_json.h"
#include "../parseCode/codeStruct.h"
#include "../utils/tools.h"

Lab_json::Lab_json(vector<LabEle *> consLists)
{
    type = LabTypes::json_type;
    for (LabEle *oneCons : consLists)
    {
        auto consV = (Lab_cons *)(oneCons);
        string key = consV->key_value.first->value;

        key_value.insert(std::pair<std::string, LabEle *>(key, consV->key_value.second));
    };
};

LabEle *Lab_json::get(LabEle *var)
{
    string key = var->value;
    auto theFind = key_value.find(key);
    if (theFind != key_value.end())
    {

        return theFind->second;
    }
    else
    {
        //这里应该只需要一个undefined
        std::cout << "没有找到变量" << key << std::endl;
        auto result = new LabEle();
        return result;
    }
};

Lab_json::~Lab_json()
{
}

std::string Lab_json::value()
{

    map<string, LabEle *>::iterator iter;
    string jsonString = "{";
    for (iter = key_value.begin(); iter != key_value.end(); iter++)
    {
        //cout << iter->first << "-" << iter->second->value() << endl;
        jsonString += iter->first + ":" + iter->second->value + ",";
    }
    jsonString += "}";
    return jsonString;
}

std::string Lab_json::stringify()
{
    map<string, LabEle *>::iterator iter;
    map<string, LabEle *>::iterator iter2;
    string jsonString = "{";
    auto begin = key_value.begin();
    auto end = key_value.end();
    auto rbegin = key_value.rbegin();
    for (iter = begin; iter != end; iter++)
    {
        iter2 = iter;
        //cout << iter->first << "-" << iter->second->value() << endl;
        if (++iter2 == end)
        {
            jsonString += iter->first + ':' + iter->second->stringify();
        }
        else
        {
            jsonString += iter->first + ':' + iter->second->stringify() + ",";
        }
    }
    jsonString += '}';
    return jsonString;
}

#endif
