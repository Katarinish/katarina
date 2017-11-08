#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <thread>


using namespace std;

class Task {
public:
	
	virtual ~Task() {}
	virtual void init(const std::string& params) = 0;
	virtual std::string name() const = 0;
	virtual void run() = 0;

};


class PlayMusic : public Task {

	std::string file_to_play;


public:

	PlayMusic() {

	};

	void init(const std::string& params) override;
	void run() override;
	
	std::string name() const override {
		return "play_music";
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

	void init(const std::string& params) override {

	}

	std::string name() const override {
		return "print_task";
	}
};

class CopyFileTask : public Task {

	 std::string from;
	 std::string to;

public	:

	void run() override;
	void init(const std::string& params) override;

	std::string name() const override {
		return "copy_file";
	}

};

class ShowMessage : public Task {

	std::string message;

	public	:

	void run() override;
	void init(const std::string& params) override;

	std::string name() const override {
		return "show_message";
	}
};

class Open : public Task {

	int count;
	std::string file_to_open;

public	:
	void run() override;
	void init(const std::string& params) override;

	std::string name() const override {
		return "open";
	}
};


class Parser {

	map<std::string, Task*> result;
	std::string file_name;

public:
	Parser(const std::string& file_name);
	const std::string& GetFileName() const;
	std::map<std::string, vector<Task*>> DoParse();

	Task* CreateTask( std::string name, std::string params);
};

class Runner {

	std::map <std::string, std::vector<Task*>> tasks_to_run;


public:

	void SetTasks(const std::map <std::string, std::vector<Task*>>& tasks);
	void RunTask(const std::string& time);
};




