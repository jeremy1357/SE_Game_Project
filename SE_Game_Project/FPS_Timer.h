#pragma once
#include <chrono>
#include <thread>

using namespace std::chrono;

class FPS_Timer
{
public:
	duration<double> Start_fps();
	duration<double> End_fps();

	steady_clock::time_point first_tp;
	double m_fps;
	double m_fps_timer;
};