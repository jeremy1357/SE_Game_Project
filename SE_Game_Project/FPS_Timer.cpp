#include "FPS_Timer.h"

duration<double> uptime()
{
	if (first_tp == steady_clock::time_point{})
		return duration<double>{ 0 };

	return steady_clock::now() - first_tp;
}

double fps()
{
	const double uptime_sec = uptime().count();

	if (uptime_sec == 0)
		return 0;

	return fps_counter / uptime_sec;
}

void run_fps()
{
	std::cout << "Start FPS: " << fps() << '\n';
	first_tp = std::chrono::steady_clock::now();

	while (1)
	{
		std::cout << "FPS: " << fps() << '\n';
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		fps_counter++;
	}
}
