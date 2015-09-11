#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include <array>
using namespace std;

struct BaseSaveData {

};

 class BaseSaveManager {
public:
	BaseSaveManager();
	virtual int Save(const int num,BaseSaveData *savedata)=0;
	virtual int Load(const int num, BaseSaveData* loaddata)=0;
 protected:
	 array<unsigned int, 100> Sizes;
private:
	virtual string GetFileName(const int num)=0;
	

};