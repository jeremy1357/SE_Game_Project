#include "FPS_Timer.h"
#include <iostream>
#include <chrono>

//Need to test and see if the fps being measured is milliseconds or in frames per second

duration<double> FPS_Timer::Start_fps()	//This function begins the timer for the FPS
{
	first_tp = steady_clock::time_point{};	//reset the first timer point to keep fps consistent
	return duration<double> {0};
}

duration<double> FPS_Timer::End_fps()	//This Funciton ends the timer and calculates how long the the updates were
{
	if (first_tp == steady_clock::time_point{})	//if the first time point is not 0, then the time elapsed is the new time - old time
		return duration<double> {0};

	duration<double> m_fps_timer =  steady_clock::now() - first_tp;	//gets the amount of milliseconds that have passed

	if (m_fps_timer.count() < 17)	//if the time is less than 17 milliseconds, then sleep to get the fps up to ~60
	{
		std::this_thread::sleep_for(milliseconds{ 10 }); //10 is a place holder for now to keep the function going
	}
}