#include "Scheduler.h"

Parser::Parser(const std::string f_name) {
	file_name = f_name;
}

std::string& Parser::GetFileName() const {
	return file_name;
}

std::map<std::string, Task*> Parser::DoParse() {

	std::ifstream file_to_read("my_file.txt");
	//std::ifstream file_to_read(GetFileName);

	if (file_to_read) {

		while (file_to_read) {

			std::string line;
			//getline(file_to_read, line);
			file_to_read >> line;

			//finding time
			int pos = line.find(' ');
			std::string time = line.substr(0, pos);
			//finding task type
			int pos1 = line.find(pos + 1, ' ');
			std::string name = line.substr(pos + 1, pos1);
			//finding parametrs of the task
			std::string params = line.substr(pos1 + 1);

			//Creating task to fill with params
			Task new_task = CreateTask(name, params);



		}
	}
	else {
		//throw.....
	}

}