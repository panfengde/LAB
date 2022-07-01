#include <string>
#include <iostream>
#include <regex>
#include <vector>
#include <utility>
#include <memory>
#include <list>
#include "./codeStruct.h"

using namespace std;

bool jude_barckets(string &str)
{
    regex brackets("^\\s*\\([\\s\\S]*\\S+[\\s\\S]*\\)\\s*$");
    return regex_match(str, brackets);
};

bool jude_quote(string &str)
{
    //这里匹配'()错误
    regex brackets("^\\s*[\\r\\n]*\\s*'\\w+|^\\s*[\\r\\n]*\\s*'\\(\\w+");

    return regex_match(str, brackets);
};

string aboutWord(string word)
{
    if (word[0] == '[' && word[word.length() - 1] == ']')
    {
        return " " + word + " ";
    }
    else
    {
        return " \"" + word + "\" ";
    }
}

bool jude_point(std::string str)
{
    auto index = str.find(".");
    return index != str.npos && str[index + 1] != '.';
};

string split(std::string str)
{
    string pattern = ".";
    // cout << str << "........" << endl;
    if (str.find(pattern) == str.npos)
    {
        return str;
    }
    std::string::size_type pos;
    std::vector<std::string> word;
    str += pattern; //扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size)
        {
            std::string s = str.substr(i, pos - i);
            word.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }

    std::string result = "( get " + word[0] + " " + aboutWord(word[1]) + " )";

    for (int i = 2; i < word.size(); i++)
    {
        string thisWord = word[i];
        if (thisWord[0] == '[' && thisWord[thisWord.length() - 1] == ']')
        {
            result = "( get " + result + " " + aboutWord(word[i]) + ")";
        }
        else
        {
            result = "( get " + result + " " + aboutWord(word[i]) + " )";
        }
    }

    return result;
}

string kill_startEnd_rubbish(string &str)
{
    //txt.replace(/^\s*[\r\n]*\s*|\s*[\r\n]*\s*$/g, "")
    regex brackets("^\\s*[\\r\\n]*\\s*|\\s*[\\r\\n]*\\s*$");
    return regex_replace(str, brackets, "");
};

string quoteHandle(string &str)
{
    if (jude_quote(str))
    {
        string newStr = regex_replace(str, regex("^\\s*[\\r\\n]*\\s*'"), "");
        list<int> temp = {1};
        bool car_over = false;
        string car = "(";
        string cdr = "";
        for (int i = 1; i < str.length(); i++)
        {
            char word = str[i];
            if (word == '(')
            {
                temp.push_back(1);
            }
            else if (word == ')')
            {
                temp.pop_back();
            }

            if (!car_over)
            {
                car += word;
            }
            else
            {
                cdr += word;
            }

            if (temp.size() == 0 && !car_over)
            {
                car_over = true;
            };
        };

        return string("quote " + car + ") " + cdr);
    }
    else
    {
        return str;
    }
};

/**
    * 获取括号表达式内的内容--会去掉第一层括号和首尾的垃圾
    * 如果不是括号表达式，就返回去除收尾垃圾的信息（字符串表达式不祛除）
    * 表达式经过了预处理，首位不会有空值和换行符号
     */
string get_brackets_content(string &str)
{
    return regex_replace(str, regex("^\\s*[\\r\\n]*\\(?\\s*[\\r\\n]*\\s*|\\s*[\\r\\n]*\\s*\\)?\\s*[\\r\\n]*\\s*$"), "");
};

pair<string, string> parse_brackets(string code_str)
{
    string exp_str = quoteHandle(code_str);

    exp_str = get_brackets_content(exp_str);
    string car = "";
    string cdr = "";
    bool car_over = false;
    bool doubleFlag_lock = false;
    exp_str = quoteHandle(exp_str);
    if (exp_str[0] != '(')
    {
        for (int i = 0; i < exp_str.length(); i++)
        {
            char world = exp_str[i];
            if (world == '\n')
            {
                //处理回车
                continue;
            }

            //字符串
            if (world == '\"')
            {
                doubleFlag_lock = !doubleFlag_lock;
            };
            //分词结束
            if (!doubleFlag_lock && (world == ' ' || world == '('))
            {
                car_over = true;
            };

            if (!car_over)
            {
                car += world;
            }
            else
            {
                cdr += world;
            };
        }
        cdr = kill_startEnd_rubbish(cdr);
        cdr = quoteHandle(cdr);
        return pair<string, string>{car, string('(' + cdr + ')')};
    }
    else
    {
        //表达式的car为括号队的时候
        list<int> temp{1};
        car_over = false;
        car = "(";
        for (int i = 1; i < exp_str.length(); i++)
        {
            char world = exp_str[i];
            if (world == '\"')
            {
                doubleFlag_lock = !doubleFlag_lock;
            };

            if (!doubleFlag_lock)
            {
                if (world == '(')
                {
                    temp.push_back(1);
                }
                else if (world == ')')
                {
                    temp.pop_back();
                };
            };

            if (!car_over)
            {
                car += world;
            }
            else
            {
                cdr += world;
            };

            if (!doubleFlag_lock && (temp.size() == 0 && !car_over))
            {
                car_over = true;
            };
        }
        return pair<string, string>{car, string('(' + cdr + ')')};
    }
}

shared_ptr<CodeUnit> strExp_to_List(string &exp_str, shared_ptr<CodeUnit> result = make_shared<CodeUnit>())
{
    if (jude_barckets(exp_str) || jude_quote(exp_str))
    {
        pair<string, string> get = parse_brackets(exp_str);
        result->elementList.push_back(strExp_to_List(get.first));
        strExp_to_List(get.second, result);
        //reulst.push(Parse.strExp_to_List(car))
    }
    else
    {
        if (jude_point(exp_str))
        {
            //处理属性表达式 a.b.c
            exp_str = split(exp_str);
            strExp_to_List(exp_str, result);
        }
        else
        {
            result = make_shared<CodeUnit>(exp_str);
        }
    }
    return result;
}

int _main()
{
    string strCode = "'( 2 )";

    //kill_startEnd_rubbish(strCode2);
    //std::cout << kill_startEnd_rubbish(strCode) << std::endl;
    //std::cout << get_brackets_content(strCode) << std::endl;
    std::cout << jude_quote(strCode) << std::endl;

    strExp_to_List(strCode);

    return 1;
}