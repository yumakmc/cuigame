#pragma once
#include "Menu.h"
#include <assert.h>
#include <iostream>
using namespace std;



Menu::Menu(SceneChanger* changer) : BaseScene(changer),afoc(){
	
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
	
}
void Menu::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	
	
	//DrawString(280, FINISH_Y, "おわる", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect){//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら
		break;
	case eMenu_Config://設定選択中なら	
		break;
	case eMenu_Finish://設定選択中なら	
		break;
	}
	afoc.Draw();
	//DrawString(250, y, "■", GetColor(255, 255, 255));
}
void Menu::Draw(vector<string> &tmpfield) {
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ////////////////
					  //DrawString(280, FINISH_Y, "おわる", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら
		break;
	case eMenu_Config://設定選択中なら	
		break;
	case eMenu_Finish://設定選択中なら	
		break;
	}
	afoc.Draw(tmpfield);
	//DrawString(250, y, "■", GetColor(255, 255, 255));
}

void Menu::Update(){
	afoc.Update();
	//if (Keyboard_Get(KEY_INPUT_DOWN) == 1){//下キーが押されていたら
	//	NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//選択状態を一つ下げる
	//}
	//
	//if (Keyboard_Get(KEY_INPUT_RETURN) == 1){//エンターキーが押されたら
	//	switch (NowSelect){//現在選択中の状態によって処理を分岐
	//	case eMenu_Game://ゲーム選択中なら
	//		mSceneChanger->ChangeScene(eScene_Game);
	//		break;
	//	case eMenu_Config://設定選択中なら
	//		mSceneChanger->ChangeScene(eScene_Config);
	//		break;
	//	case eMenu_Finish:
	//		exit(1);
	//	}
	//}
}


