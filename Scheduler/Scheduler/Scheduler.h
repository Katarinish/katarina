#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Parser {
 Runner* r;

 bool go_on;

public:
	
	Task* CreateTask();
	void AddTaskToSchedule(int time, Task* task);
	bool IfParsing();
	//r->AddTask(time, ); put inside of an AddTaskToSchedule func?
};

class Init {


public:
	virtual void InitTask(Task& task_to_init);
};


class Runner {

	std::map <std::string, std::vector<Task*>> daily_tasks;


public:

	void AddTask(int time, Task*);
	void RunTask(int time);

};






class Task {
public:
	virtual ~Task() {}
	virtual void run() = 0;

};

void run_task(Task &t) {
	t.run();
}

class PlayMusic : public Task {
public:

	PlayMusic(const std::string& params) {

	}

	void run() override {

	}

};

class PrintTasks : public Task {


	public	:

	void run() override {

	}
};

class CopyFile : public Task {

	public	:

	void run() override {

	}

};

class ShowMessage : public Task {

	public	:

	void run() override {

	}

};

class Open : Task {

	public	:

	void run() override {

	}

};