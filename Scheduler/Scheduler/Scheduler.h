#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>


using namespace std;

class Task {
public:
	
	virtual ~Task() {}
	virtual void init(const std::string& params) = 0;
	virtual std::string name() const = 0;
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


class Parser {

	map<std::string, Task*> result;
	std::string file_name;

public:
	Parser(const std::string file_name);
	std::string& GetFileName() const;
	std::map<std::string, Task*> DoParse();

	Task* CreateTask( std::string name, std::string params);



	//r->AddTask(time, ); put inside of an AddTaskToSchedule func?
};

class Runner {

	std::map <std::string, std::vector<Task*>> daily_tasks;


public:

	void AddTask(int time, Task*);
	void RunTask(int time);

};




