#pragma once
#include <Windows.h>

class Timer
{
public:
	void startMeasure() {
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
	};
	double stopMeasure() {
		QueryPerformanceCounter(&end);
		secs = end.QuadPart - start.QuadPart;
		secs = secs / freq.QuadPart;
		return secs;
	};

private:
	double secs;
	LARGE_INTEGER  start, end, freq;
};

