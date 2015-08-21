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
	while (1){
		time += aTimeManager.GetDifference();
		if (time > TPF) {
			time -= TPF;
			Keyboard_Update();
			scenemgr.Update();
			system("cls");
			vector<string> TmpField(SIZE_Y,"　　　　　　　　　　　　　　　　　　　　");//空白の数はSIZE_Xの数と同じ　修正したいけど重くなりそう
			scenemgr.Draw(TmpField);
			for (int y = 0; y < TmpField.size(); ++y) {
				assert(TmpField[y].size() == 2 * SIZE_X);
				cout << TmpField[y]<<endl;
			}
		}
	}
	scenemgr.Finalize();
	return 0;
}
