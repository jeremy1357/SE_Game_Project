#include "FPS_Timer.h"
#include <iostream>
#include <chrono>

using fsecond = std::chrono::duration<float>;

//Need to test and see if the fps being measured is milliseconds or in frames per second

void FPS_Timer::start_FPS()	//This function begins the timer for the FPS
{
	first_tp = steady_clock::now();	//sets the first timer point to keep fps consistent
}

void FPS_Timer::end_FPS()	//This Funciton ends the timer and calculates how long the the updates were
{
	end_tp = steady_clock::now();	//gets the time from the first first timer point and the end timer point.
	m_fps_timer = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - first_tp);
	std::chrono::milliseconds target(17);
	const duration<double> sleep = target - m_fps_timer;

	if (m_fps_timer.count() < 17)	//if the time is less than 17 milliseconds, then sleep to get to 17 milliseconds (~60 fps)
	{
		std::this_thread::sleep_for(sleep); 
	}
	m_fps = fsecond(1) / (steady_clock::now() - first_tp);
}