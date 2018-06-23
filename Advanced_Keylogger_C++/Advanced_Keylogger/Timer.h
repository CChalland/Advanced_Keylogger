#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer
{
	std::thread Thread;
	bool Alive = false;
	long CallNumber = -1L;
	long repeat_count = -1L;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);
	std::function<void(void)> funct = nullptr;

	void SleepAndRun()
	{
		std::this_thread::sleep_for(interval);
		if (Alive)
		{
			Function()();
		}
	}

	void ThreadFunc()
	{
		if (CallNumber == Infinite)
			while (Alive)
				SleepAndRun();
		else
			while (repeat_count--)
				SleepAndRun();
	}
public:
	static const long Infinite = -1L;
	
	Timer(){}

	Timer(const std::function<void(void)> &f) : funct(f) {}

	Timer(const std::function<void(void)> &f,
		  const unsigned long &i,
		  const long repeat = Timer::Infinite) : funct (f),
												 interval(std::chrono::milliseconds(i)),
												 CallNumber(repeat) {}


};

#endif