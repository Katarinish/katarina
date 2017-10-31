#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Time {
	int hours;
	int minutes;
	int seconds;
};

class Parser {
 Runner* r;
 Time* t;

 string param;
 string state;
 string string_time;

 int time;
 bool go_on;

public:
	//Creating a task to fill with parameters 
	Task& CreateTask(); //task* ?
	//Adding a full task to a schedule
	void AddTaskToSchedule(int time, Task* task);
	//Checking if the parsing is still going 
	bool IfParsing();
	//Initialazing Time structure
	void InitTime(Time& t);
	//Turning time into seconds
	void get_seconds(Time& t);


	//r->AddTask(time, ); put inside of an AddTaskToSchedule func?
};

class Runner {

	std::map <std::string, std::vector<Task*>> daily_tasks;


public:

	void AddTask(int time, Task*);
	void RunTask(int time);

};



class Init {


public:
	virtual void InitTask(const std::string& params) = 0;
};

class InitMusic : public Init {

public:

	void InitTask(Task& task_to_init) override {

	}

};

class InitCopyFile : public Init {
	
	public:

	void InitTask(Task& task_to_init) override {

	}

};

class InitPrintTask : public Init {

	public:

	void InitTask(Task& task_to_init) override {

	}

};

class InitShowMessage : public Init {

	public:

	void InitTask(Task& task_to_init) override {

	}

};

class InitOpen : public Init {

};

void init_task(Init &initialization, Task& task_to_init) {
	initialization.InitTask(task_to_init);
}




class Task {
public:
	virtual ~Task() {}
	virtual void run() = 0;

};

void run_task(Task &t) {
	t.run();
}

class PlayMusic : public Task {

	std::vector<std::string> files_to_play;
	//std::map<int,string>
	//int count

public:

	PlayMusic(const std::string& params) {
		//Initialization here
	}

	void run() override {

	}

};

class PrintTasks : public Task {

	//The number of tasks to print
	int count; 
	//Here we keep the time of tasks we need to print
	std::map<int, int> tasks_to_print;



	public	:

	void run() override {

	}
};

class CopyFile : public Task {

	int count;
	std::map<int, string> files_to_copy;

	public	:

	void run() override {

	}

};

class ShowMessage : public Task {

	std::string message;

	public	:

	void run() override {

	}

};

class Open : Task {

	int count;
	std::map<int, string> files_to_open;

	public	:

	void run() override {

	}

};