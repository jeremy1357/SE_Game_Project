#pragma once
#include <chrono>

using namespace std::chrono;

class FPS_Timer
{
private:
	steady_clock::time_point first_tp;
	steady_clock::time_point end_tp;
	duration<double> m_fps_default;
	duration<double> max_FPS;
public:
	FPS_Timer();
	const duration<double> set_FPS(duration<double> max_FPS);
	void start_FPS();
	void end_FPS();
	float m_fps;
	duration<double> m_fps_timer;
	~FPS_Timer();
};