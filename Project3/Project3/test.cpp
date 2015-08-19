#pragma once 
#include "test.h"
#include <vector>

using namespace std;

static int Scene = eScene_Menu;    //現在の画面(シーン)
const double FPS = 10.0;
const double TPF = CLOCKS_PER_SEC*1.0 / FPS;

int main(){
	SceneMgr scenemgr;
	scenemgr.Initialize();
	//aTimeManeger
	//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){
	clock_t time = 0;
	aTimeManeger.GetDifference();
	while (1){
		time += aTimeManeger.GetDifference();
		if (time > TPF) {
			time -= TPF;
			Keyboard_Update();
			scenemgr.Update();
			system("cls");
			vector<string> TmpField(SIZE_Y,"　　　　　　　　　　　　　　　　　　　　");//空白の数はSIZE_Xの数と同じ修正したいけど重くなりそう
			scenemgr.Draw(TmpField);
			for (int y = 0; y < TmpField.size(); ++y) {
				cout << TmpField[y]<<endl;
			}
		}
	}
	scenemgr.Finalize();
	return 0;
}
