#pragma once
#include <time.h>
using namespace std;

static class TimeManager{
public:
	clock_t GetDifference() {
		clock_t nowtime = clock();
		clock_t dif = nowtime - pretime;
		pretime = nowtime;
		return dif;
	}
	TimeManager() :starttime(clock()) {

	}
private:
	const clock_t starttime;
	clock_t pretime;

}aTimeManager;