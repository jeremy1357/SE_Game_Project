#include "FPS_Timer.h"
#include <iostream>
#include <chrono>

//Need to test and see if the fps being measured is milliseconds or in frames per second

void FPS_Timer::start_FPS()	//This function begins the timer for the FPS
{
	first_tp = steady_clock::now();	//sets the first timer point to keep fps consistent
}

void FPS_Timer::end_FPS()	//This Funciton ends the timer and calculates how long the the updates were
{
	end_tp = steady_clock::now();	//gets the time from the first first timer point and the end timer point.
	m_fps = std::chrono::duration_cast<std::chrono::milliseconds>(end_tp - first_tp);

	if (m_fps.count() < 17)	//if the time is less than 17 milliseconds, then sleep to get to 17 milliseconds (~60 fps)
	{
		auto m_fps_timer = std::chrono::duration_cast<std::chrono::milliseconds>(17 - m_fps.count());
		std::this_thread::sleep_for(milliseconds{ m_fps_timer.count() }); 
	}
}