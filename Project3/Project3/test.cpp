#pragma once 
#include "test.h"
#include <vector>
#include <assert.h>
using namespace std;

static int Scene = eScene_Menu;    //現在の画面(シーン)
const double FPS = 10.0;
const double TPF = CLOCKS_PER_SEC*1.0 / FPS;


int main(){
	SceneMgr scenemgr;
	scenemgr.Initialize();
	//aTimeManager
	//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
	clock_t time = 0;
	aTimeManager.GetDifference();
	int i=0;
	while (1){
		i++;
		i %= 2;
		HANDLE hSrceen = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
			);
		if (hSrceen == INVALID_HANDLE_VALUE) {
			scenemgr.Finalize();
			return -1;
		}
		LPDWORD cell(0);
		time += aTimeManager.GetDifference();

		if (time > TPF) {
			time -= TPF;
			Keyboard_Update();
			scenemgr.Update();
			//system("cls");
			vector<string> TmpField(SIZE_Y,"　　　　　　　　　　　　　　　　　　　　");//空白の数はSIZE_Xの数と同じ　修正したいけど重くなりそう
			scenemgr.Draw(TmpField);
			for (int y = 0; y < TmpField.size(); ++y) {
				assert(TmpField[y].size() == 2 * SIZE_X);
				const char* str = (TmpField[y]).c_str();
				WriteConsole(hSrceen, str, strlen(str), cell, NULL);
				const char* kaigyou = "\n";
				WriteConsole(hSrceen, kaigyou, strlen(kaigyou), cell, NULL);
				//cout << TmpField[y]<<endl;
			}
			SetConsoleActiveScreenBuffer(hSrceen);
		}
	}
	scenemgr.Finalize();
	return 0;
}
