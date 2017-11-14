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
	
	Runner::GetInstace().SetTasks(tasks);
	Runner::GetInstace().RunTime();
 	system("pause");
	return 0;
}