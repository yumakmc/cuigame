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
	int i=0;
	HANDLE hSrceen[2] = { CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
		), CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL
			) };
	CONSOLE_CURSOR_INFO info = {};
	
	if (hSrceen[0] == INVALID_HANDLE_VALUE) {
		scenemgr.Finalize();
		return -1;
	}

	::GetConsoleCursorInfo(hSrceen[0], &info);
	info.bVisible = false;
	SetConsoleCursorInfo(hSrceen[0], &info);
	::GetConsoleCursorInfo(hSrceen[1], &info);
	info.bVisible = false;
	SetConsoleCursorInfo(hSrceen[1], &info);

	aTimeManager.GetDifference();
	while (1){
		time += aTimeManager.GetDifference();
		if (time > TPF) {
			time -= TPF;
			Keyboard_Update();
			scenemgr.Update();
			vector<string> TmpField(SIZE_Y,"　　　　　　　　　　　　　　　　　　　　");//空白の数はSIZE_Xの数と同じ　修正したいけど重くなりそう
			scenemgr.Draw(TmpField);
			LPDWORD cell(0);
			for (int y = 0; y < TmpField.size(); ++y) {
				assert(TmpField[y].size() == 2 * SIZE_X);
				const char* str = (TmpField[y]).c_str();
				WriteConsole(hSrceen[i], str, strlen(str), cell, NULL);
				const char* kaigyou = "\n";
				WriteConsole(hSrceen[i], kaigyou, strlen(kaigyou), cell, NULL);
			}
			SetConsoleActiveScreenBuffer(hSrceen[i]);
			DWORD wbyte;
			COORD coord = {};
			TCHAR str[801] = ("");
			i++;
			i %= 2;
			::SetConsoleCursorPosition(hSrceen[i], coord);
			::WriteConsole(hSrceen[i], str, static_cast<DWORD>(800), &wbyte, NULL);
		}
	}
	CloseHandle(hSrceen[0]);
	CloseHandle(hSrceen[1]);
	hSrceen[0] = NULL;
	hSrceen[1] = NULL;
	scenemgr.Finalize();
	return 0;
}
