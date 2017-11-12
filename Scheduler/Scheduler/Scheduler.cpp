#include "Scheduler.h"
#include <windows.h>
#include <stdio.h>
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

int Parser::ConvertToTime(const std::string& time) {
	int h = 0;
	int m = 0;
	int s = 0;
	sscanf_s(time.c_str() , "%02d:%02d:%02d", &h, &m, &s);
	int res = h * 3600 + m * 60 + s;
	return res;
}


//Result of parsing 
std::map<int, vector<Task*>> Parser::DoParse() {

	std::map<int, vector<Task*>> result;
	std::ifstream file_to_read(GetFileName());
	while (file_to_read) {

		std::string time, name, params;
		file_to_read >> time >> name;
		if (name.empty() || time.empty())
			break;
		std::getline(file_to_read, params);

		//Creating task to fill with params
		Task* new_task = CreateTask(name, params);

		result[ConvertToTime(time)].push_back(new_task);
	}
	return result;

}


//Runner initialization and etc
/*void Runner::RunTask(int time) {
	auto it = tasks_to_run.find(time);
	if (it == tasks_to_run.end())
		return;
	auto& tasks = it->second;
	for (auto* task : tasks) {
		std::cout << task->name() << std::endl;
		//std::thread thread(&Task::run, task);
		std::thread  thread([task](){
			task->run();
		});
	    thread.detach();
	}
}*/



static Runner& Runner::GetInstace() {
	static Runner r;
	return r;
}

void Runner::SetTasks(const std::map <int, std::vector<Task*>>& tasks) {
	tasks_to_run = tasks;
}

std::chrono::steady_clock::time_point get_day_start() {
	time_t now =
		std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	tm t;
	localtime_s(&t, &now);
	t.tm_hour = 0;
	t.tm_min = 0;
	t.tm_sec = 0;

	auto day_start = std::chrono::system_clock::from_time_t(mktime(&t));

	auto sdy_now = std::chrono::steady_clock::now();
	auto sys_now = std::chrono::system_clock::now();
	return day_start - sys_now + sdy_now;
}

void Runner::WatchTime(int prev, int curr) {

	auto itlow = tasks_to_run.lower_bound(prev);
	auto itup = tasks_to_run.upper_bound(curr - 1);

	for (; itlow != itup; ++itlow) {
		auto& tasks_to_run = itlow->second;
		for (auto* task : tasks_to_run) {
			std::cout << task->name() << std::endl;
			std::thread  thread([task]() {
				task->run();
			});
			thread.detach();
		}
	}


}

void Runner::RunTime() {
	auto start = get_day_start();
	int prev_time = 0;

	while (1) {
		auto curr = std::chrono::steady_clock::now();
		int curr_time = std::chrono::duration_cast<std::chrono::seconds>(curr - start).count();
		WatchTime(prev_time, curr_time);
		prev_time = curr_time;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

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

void Runner::PrintTasks(int from, int to) {

	auto itlow = tasks_to_run.lower_bound(from);
	auto itup = tasks_to_run.upper_bound(to);

	for (; itlow != itup; ++itlow) {
		auto& tasks_to_run = itlow->second;
		for (auto* task : tasks_to_run) {
			std::cout << task->name() << std::endl;
		}
	}

}

void PrintTasks::run() {
	Runner::GetInstace().PrintTasks(from, to);


}
void PrintTasks::init(const std::string& params) {

	int th = 0;
	int tm = 0;
	int ts = 0;
	int fh = 0;
	int fm = 0;
	int fs = 0;
	sscanf_s(params.c_str(), "%02d:%02d:%02d%:02d:%02d:%02d", &th, &tm, &ts, &fh, &fm, &fs );

	from = th * 3600 + tm * 60 + ts;
	to = fh * 3600 + fm * 60 + fs;

}