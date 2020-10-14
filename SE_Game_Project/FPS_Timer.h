#pragma once
#include <chrono>
#include <thread>

using namespace std::chrono;

class FPS_Timer
{
public:
	void start_FPS();
	void end_FPS();

	steady_clock::time_point first_tp;
	steady_clock::time_point end_tp;
	duration<double> m_fps;
};