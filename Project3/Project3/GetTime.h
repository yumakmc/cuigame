#pragma once
#include <time.h>
using namespace std;
static class TimeManeger{
public:
	clock_t GetDifference() {
		clock_t nowtime = clock();
		clock_t dif = nowtime - pretime;
		pretime = nowtime;
		return dif;
	}
	TimeManeger() :starttime(clock()) {

	}
private:
	const clock_t starttime;
	clock_t pretime;

}aTimeManeger;