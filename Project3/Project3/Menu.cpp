#pragma once
#include "Menu.h"
#include "Keyboard.h"
#include <assert.h>
#include <iostream>
using namespace std;

const int BLANK_FOR_MENU_UP = 10;
const int BLANK_FOR_MENU_DOWN = 18;
const int BLANK_FOR_MENU_LEFT = 2;
const int BLANK_FOR_MENU_RIGHT = 18;

Menu::Menu(SceneChanger* changer) : BaseScene(changer),afoc(){
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
	
}
void Menu::Draw(){
	assert(false);
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	
	
	//DrawString(280, FINISH_Y, "おわる", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect){//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら
		break;
	case eMenu_Tranp://トランプ選択中なら	
		break;
	case eMenu_Finish://設定選択中なら	
		break;
	}
	afoc.Draw();
}
void Menu::Draw(vector<string> &tmpfield) {
	BaseScene::Draw(tmpfield);//親クラスの描画メソッドを呼ぶ////////////////
	afoc.Draw(tmpfield);
	for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
		for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
			tmpfield[y].replace(2*x, 2, "　");
		}
	}
	//tmpfield[BLANK_FOR_MENU_UP].replace(2 * BLANK_FOR_MENU_LEFT, (BLANK_FOR_MENU_RIGHT - BLANK_FOR_MENU_LEFT) * 2, "********************************");
	tmpfield[12].replace(16, 12, "ＳＴＯＲＹ１");
	tmpfield[14].replace(16, 12, "ＳＴＯＲＹ２");
	tmpfield[16].replace(16, 8, "ＥＸＩＴ");
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら　そのうちかーげーに変更したい　実装だるそう
		tmpfield[12].replace(10, 2, "●");
		break;
	case eMenu_Tranp://トランプ選択中なら	
		tmpfield[14].replace(10, 2, "●");
		break;
	case eMenu_Finish://終了選択中なら	
		tmpfield[16].replace(10, 2, "●");
		break;
	}
}

void Menu::Update(){
	afoc.Update();
	if (Keyboard_Get(VK_DOWN) == 1){//下キーが押されていたら
		NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//選択状態を一つ下げる
	}else if (Keyboard_Get(VK_UP) == 1) {//上キーが押されていたら
		NowSelect = eMenu((int(NowSelect) +int(eMenu_count) - 1) % int(eMenu_count));//選択状態を一つ上げる
	}
	
	if (Keyboard_Get(VK_RETURN) == 1){//エンターキーが押されたら
		switch (NowSelect){//現在選択中の状態によって処理を分岐
		case eMenu_Game://ゲーム選択中なら
			mSceneChanger->ChangeScene(eScene_Game);
			break;
		case eMenu_Tranp://設定選択中なら
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Finish:
			exit(1);
		}
	}
}


