#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>
#include "BaseSaveManager.h"
#include "RogueGame.h"
using namespace std;



static class RogueSaveManager:public BaseSaveManager {
public:
	RogueSaveManager();
	int Save(const int num, BaseSaveData* savedata);
	BaseSaveData* Load(const int num, BaseSaveData* loaddata);
	
private:
	string GetFileName(const int num);

}aRogueSaveManager;