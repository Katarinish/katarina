#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <iostream>
#include <stdio.h>


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

	int from;
	int to;




	public	:

		void run() override;

	void init(const std::string& params) override;

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

	std::map<std::string, Task*> result;
	std::string file_name;

public:
	Parser(const std::string& file_name);
	const std::string& GetFileName() const;
	std::map<int, vector<Task*>> DoParse();
	Task* CreateTask( std::string name, std::string params);
	int ConvertToTime(const std::string& time);
};

class Runner {

	friend class PrintTasks;

	std::map <int, std::vector<Task*>> tasks_to_run;
	std::vector <std::thread> SavedThreads;
	
	void WatchTime(int prev, int curr);
	void PrintTasks(int from, int to);

	Runner() = default;
	~Runner();


public:
	void SetTasks(const std::map <int, std::vector<Task*>>& tasks);
	static Runner& GetInstace();
	void RunTime();
};






