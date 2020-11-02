#include "FPS_Timer.h"
#include <iostream>
#include <thread>
using fsecond = std::chrono::duration<float>;

FPS_Timer::FPS_Timer()
{
	max_FPS = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double, std::milli>(60.0));
}

void FPS_Timer::set_FPS(double set_FPS)
{
	max_FPS = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double, std::milli>(set_FPS));
}

void FPS_Timer::start_FPS()	//This function begins the timer for the FPS
{
	first_tp = steady_clock::now();	//sets the first timer point to keep fps consistent
}

void FPS_Timer::end_FPS()	//This Funciton ends the timer and calculates how long the the updates were
{
	end_tp = steady_clock::now();	//gets the time from the first first timer point and the end timer point.
	m_fps_timer = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - first_tp);
	std::chrono::milliseconds target(std::chrono::milliseconds(1000) / std::chrono::duration_cast<std::chrono::milliseconds>(max_FPS));
	const duration<double> sleep = target - m_fps_timer;

	if (m_fps_timer < target)
	{
		std::this_thread::sleep_for(sleep);
	}
	m_fps = fsecond(1) / (steady_clock::now() - first_tp);
}

FPS_Timer::~FPS_Timer()
{
	;
}
