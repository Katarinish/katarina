#pragma comment(lib,"Winmm.lib")
#include <windows.h>
#include "Scheduler.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		return 0;
	}
	Parser parser(argv[1]);
	auto tasks = parser.DoParse();
	Runner runner;
	runner.SetTasks(tasks);
	runner.RunTask("21:30:15");
	//runner.RunTask("10:00:00");
 	system("pause");
	return 0;
}