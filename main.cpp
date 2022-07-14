//
// Created by 潘峰 on 2022/7/1.
//

#include <string>
#include <iostream>
#include "./LabEntry.h"
#include "./LabEntry.cpp"

using namespace std;


int main() {
    // 插入全局变量，方法等

    /*string strCode = R"(
        (sleep (+ 1 1) 10)
        (sleep (+ 2 2) 100)
        (sleep (+ 3 3) 1000)
        (sleep (+ 1000 100) 5000)
        (sleep (+ 4 4) 20)
     )";*/
    string strCode = R"(
           <div>
               <div>"123"</div>
               <div>"123"</div>
               <div>"123"</div>
            </div>
         )";
    //string strCode = read("./Lab/test.lab");
    //string strCode = read("./Lab/town.json");
    //strCode = "( begin " + strCode + " )";
    labEntry(strCode);
    std::cout << "开始执行任务" << std::endl;
    global_labTasks->doTasks();
    std::cout << "任务执行完毕" << std::endl;
}