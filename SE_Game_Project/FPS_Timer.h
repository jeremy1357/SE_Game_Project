//Corey Deeves
#pragma once
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono;
steady_clock::time_point first_tp;
unsigned int m_fps;
unsigned long fps_counter = 0;

class FPS_Timer
{
public:	
	duration<double> uptime();
	double fps();
	void run_fps();
};

