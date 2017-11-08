#include "Scheduler.h"
#include <windows.h>
#include <ShellAPI.h>

//Parser constructor
Parser::Parser(const std::string& f_name) {
	file_name = f_name;
}
//Getting the path to the scheduler 
const std::string& Parser::GetFileName() const {
	return file_name;
}
//Creating task by the action from scheduler
Task* Parser::CreateTask(std::string name, std::string params) {

	if (name == "print_tasks") {
		auto* newtask = new PrintTasks;
		newtask->init(params);
		return newtask;
	}
	if (name == "play_music") {
		auto* newtask = new PlayMusic;
		newtask->init(params);
		return newtask;
	}
	if (name == "copy_file") {
		auto* newtask = new CopyFileTask;
		newtask->init(params);
		return newtask;
	}
	if (name == "show_message") {
		auto* newtask = new ShowMessage;
		newtask->init(params);
		return newtask;
	}
	if (name == "open") {
		auto* newtask = new Open;
		newtask->init(params);
		return newtask;
	}

	return nullptr;

}
//Result of parsing 
std::map<std::string, vector<Task*>> Parser::DoParse() {

	std::map<std::string, vector<Task*>> result;
	std::ifstream file_to_read(GetFileName());
	while (file_to_read) {

		std::string time, name, params;
		//getline(file_to_read, line);
		file_to_read >> time >> name;
		if (name.empty() || time.empty())
			break;
		std::getline(file_to_read, params);

		//Creating task to fill with params
		Task* new_task = CreateTask(name, params);

		result[time].push_back(new_task);
	}
	return result;

}


//Runner initialization and etc
void Runner::RunTask(const std::string& time) {
	auto it = tasks_to_run.find(time);
	if (it == tasks_to_run.end())
		return;
	auto& tasks = it->second;
	for (auto* task : tasks) {
		std::cout << task->name() << std::endl;
		std::thread thread(&Task::run, task);
	    thread.detach();
		//task->run();
	}
}
void Runner::SetTasks(const std::map <std::string, std::vector<Task*>>& tasks) {
	tasks_to_run = tasks;
}


//PlayMusic stuff
void PlayMusic::init(const std::string& params) {
	file_to_play = params;
}
void PlayMusic::run() {
	PlaySoundA(file_to_play.c_str(), NULL, SND_FILENAME);
}

//CopyFile stuff 
void CopyFileTask::init(const std::string& params) {
	
	int pos = params.find(' ');
	from = params.substr(0, pos);
	to = params.substr(pos + 1);

}
void CopyFileTask::run() {

	std::ifstream  src(from, std::ios::binary);
	std::ofstream  dst(to, std::ios::binary);
	dst << src.rdbuf();
}

//Show Message stuff 
void ShowMessage::init(const std::string& params) {
	message = params;
}
void ShowMessage::run() {
	MessageBoxA(NULL, message.c_str(), "Сообщение", MB_OK | MB_ICONEXCLAMATION);
}

//Open stuff 

void Open::run() {
	ShellExecuteA(NULL, "open", file_to_open.c_str(), NULL, NULL, SW_RESTORE);
}
void Open::init(const std::string& params) {
	file_to_open = params;
}