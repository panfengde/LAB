#include <iostream>
#include <ctime>
#include <vector>
#include <ctime>
#include "../typeGlobal.h"
#include "./task.h"

using namespace std;
auto global_labTasks = make_shared<TaskList>();

void TaskList::doTasks()
{
    while (taskList.size() != 0)
    {
        loopTask();
    }
};

void TaskList::loopTask()
{
    vector<Task> prepareTasks = getTask();
    //cout << "size:" << prepareTasks.size() << endl;
    for (Task oneTask : prepareTasks)
    {
        //cout << "RunTime:" <<clock() << "|doTimer:" << oneTask.doTimer << "]" << oneTask.body(oneTask.env)->stringify() << endl;
        cout << oneTask.body(oneTask.env)->stringify() << endl;
    }
}

vector<Task> TaskList::getTask()
{
    vector<Task> prepareTasks;
    std::vector<Task>::iterator it;
    clock_t thisTime = clock();
    for (it = taskList.begin(); it != taskList.end();)
    {
        if (it->doTimer <= thisTime)
        {
            prepareTasks.push_back(*it);
            it = taskList.erase(it);
        }
        else
        {
            ++it;
        }
    }
    sort(prepareTasks.begin(),
         prepareTasks.end(),
         [](Task one, Task two) -> bool
         { return one.doTimer < two.doTimer; });
    return prepareTasks;
};

void TaskList::insertTask(LabCallback body, shared_ptr<Frame> env, int waitTime)
{
    Task tempTaks;
    tempTaks.body = body;
    tempTaks.env = env;
    tempTaks.doTimer = clock() + waitTime;
    cout << "tempTaks.doTimer " << waitTime << "|" << tempTaks.doTimer << endl;
    tempTaks.waiteTime = waitTime;
    taskList.push_back(tempTaks);
}

/* 
void settimer(int msec, BACKCALLFUNC backcallfunc) //方式一实现定时器
{
    if (msec < 0) //判断时间段是否满足 >=0
    {
        return;
    }
    clock_t start, finish;
    start = clock();      //计时函数
    double totaltime = 0; //定义时间变量
    while (1)
    {
        finish = clock();
        totaltime = (double)(finish - start);
        if (totaltime > msec)
        {
            backcallfunc(&totaltime);
            break;
        }
    }
}

void backcallfunc(void *arg)
{
    cout << "go to timer1:" << *(double *)arg << endl;
}

int main(int argc, char *argv[])
{
    clock_t thisTime = clock();
    cout << thisTime << endl;
    cout << thisTime + 400 << endl;
    // while (1) //不断循环
    // {
    //     settimer(100, backcallfunc);
    // }
    // return 0;
}
 */