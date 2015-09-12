#pragma once
#include <ctime>
#include <deque>

class FPSTimer
{
private:
	std::deque<float> *lastFrameTimes;
	time_t lastFrame, tempTime;
	char *fpsString;
	int averageOfFrames;
	int framesToUpdate;
	float averageFps;
public:
	FPSTimer(int averageOfFrames);
	void timeFrame();
	char *getFps();
};