#ifndef LOOPTASKS
#define LOOPTASKS
#include <iostream>
#include <vector>
#include <ctime>
#include <memory>
#include "../frame/frame.h"
#include "../typeGlobal.h"

using namespace std;
struct Task
{
  int waiteTime;
  clock_t doTimer;
  LabCallback body;
  shared_ptr<Frame> env;
};

class TaskList
{
public:
  vector<Task> taskList;
  void insertTask(LabCallback, shared_ptr<Frame>, int);
  vector<Task> getTask();
  void deleteTask();
  void loopTask();
  void doTasks();
};

extern shared_ptr<TaskList> global_labTasks;

#endif
