#include "./codeStruct.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;
int main()
{
    shared_ptr<CodeUnit> codeContaine_all = make_shared<CodeUnit>();
    //codeContaine_all->elementList->push_back(temp);
    for (int i = 0; i < 200000; i++)
    {
        codeContaine_all->elementList.push_back(make_shared<CodeUnit>(string("begin")));
        //cout << "one_go" << endl;
        shared_ptr<CodeUnit> codeContainer1 = make_shared<CodeUnit>();
        shared_ptr<CodeUnit> a = make_shared<CodeUnit>(string("1"));
        shared_ptr<CodeUnit> b = make_shared<CodeUnit>(string("2"));
        shared_ptr<CodeUnit> c = make_shared<CodeUnit>(string("3"));
        shared_ptr<CodeUnit> d = make_shared<CodeUnit>(string("4"));
        //cout << "middle_go" << endl;
        codeContainer1->elementList.push_back(a);
        codeContainer1->elementList.push_back(b);
        codeContainer1->elementList.push_back(c);
        codeContainer1->elementList.push_back(d);
        codeContaine_all->elementList.push_back(codeContainer1);
        //cout << "one_end" << endl;
    }
    cout << "end-------------" << endl;

    /* std::vector<std::shared_ptr<std::string>> words;
    std::string word;
    std::cout << "Enter words separated by spaces, enter Ctrl+Z on a separate line to end:\n";
    while (true)
    {
        if ((std::cin >> word).eof())
        {
            std::cin.clear();
            break;
        }
        words.push_back(std::make_shared<string>(word)); // Create smart pointer to string & store it
    } */
};
