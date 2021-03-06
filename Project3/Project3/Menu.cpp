#pragma once
#include "Menu.h"
#include "Keyboard.h"
#include "DrawableConsole.h"

#include "Music.h"

#include <assert.h>
#include <iostream>
using namespace std;

const int BLANK_FOR_MENU_UP = 10;
const int BLANK_FOR_MENU_DOWN = 18;
const int BLANK_FOR_MENU_LEFT =10;
const int BLANK_FOR_MENU_RIGHT = 30;

extern bool HaveColor;//BackGroundより　extern参照　BackGroundで色がつけばtrueに変わる。　

Menu::Menu(SceneChanger* changer) : BaseScene(changer),fallingobjectcollection(HaveColor){
	aMusic.Play(4);
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
}
void Menu::Draw(){
	//assert(false);
	fallingobjectcollection.Draw();
	for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
		for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
			aDrawableConsole.draw(x, y, "　");
		}
	}
	aDrawableConsole.draw(15, 12, "ＳＴＯＲＹ１バグ有　");
	aDrawableConsole.draw(15, 13, "ＳＴＯＲＹ２バグ有　");
	aDrawableConsole.draw(15, 14, "ＳＴＯＲＹ３　　　　");
	aDrawableConsole.draw(15, 15, "ＳＴＯＲＹ４　　　　");
	aDrawableConsole.draw(15, 16, "ＭＵＳＩＣ　ＲＯＯＭ");
	aDrawableConsole.draw(15, 17, "　　　ＥＸＩＴ　　　");
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Game://ゲーム選択中なら　そのうちかーげーに変更したい　実装だるそう
		
		aDrawableConsole.draw(13, 12, "●");
		break;
	case eMenu_Tranp://トランプ選択中なら	
		aDrawableConsole.draw(13, 13, "●");
		break;
	case eMenu_Rpg://RPG選択中なら	
		aDrawableConsole.draw(13, 14, "●");
		break;
	case eMenu_Rogue://ローグ選択中なら	
		aDrawableConsole.draw(13, 15, "●");
		break;
	case eMenu_Musicroom://音楽室選択中なら	
		aDrawableConsole.draw(13, 16, "●");
		break;
	case eMenu_Finish://終了選択中なら	
		aDrawableConsole.draw(13, 17, "●");
		break;
	}
}
void Menu::Draw(vector<string> &tmpfield) {
	assert(false);
	//BaseScene::Draw(tmpfield);//親クラスの描画メソッドを呼ぶ////////////////
	//afoc.Draw(tmpfield);
	//for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
	//	for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
	//		//tmpfield[y].replace(2*x, 2, "　");
	//		aDrawableConsole.draw(x, y, "　");
	//	}
	//}
	////tmpfield[BLANK_FOR_MENU_UP].replace(2 * BLANK_FOR_MENU_LEFT, (BLANK_FOR_MENU_RIGHT - BLANK_FOR_MENU_LEFT) * 2, "********************************");
	//tmpfield[12].replace(16, 12, "ＳＴＯＲＹ１");
	//aDrawableConsole.draw(8, 12, "ＳＴＯＲＹ１");
	//tmpfield[14].replace(16, 12, "ＳＴＯＲＹ２");
	//aDrawableConsole.draw(8, 14, "ＳＴＯＲＹ２");
	//tmpfield[16].replace(16, 8, "ＥＸＩＴ");
	//aDrawableConsole.draw(8, 16, "ＥＸＩＴ");
	//switch (NowSelect) {//現在の選択状態に従って処理を分岐
	//case eMenu_Game://ゲーム選択中なら　そのうちかーげーに変更したい　実装だるそう
	//	tmpfield[12].replace(10, 2, "●");
	//	aDrawableConsole.draw(5, 12, "●");
	//	break;
	//case eMenu_Tranp://トランプ選択中なら	
	//	tmpfield[14].replace(10, 14, "●");
	//	aDrawableConsole.draw(5, 14, "●");
	//	break;
	//case eMenu_Finish://終了選択中なら	
	//	tmpfield[16].replace(10, 16, "●");
	//	aDrawableConsole.draw(5, 16, "●");
	//	break;
	//}
}

void Menu::Update(){
	fallingobjectcollection.Update();
	if (Keyboard_Get(VK_DOWN) == 1){//下キーが押されていたら
		NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//選択状態を一つ下げる
	}else if (Keyboard_Get(VK_UP) == 1) {//上キーが押されていたら
		NowSelect = eMenu((int(NowSelect) +int(eMenu_count) - 1) % int(eMenu_count));//選択状態を一つ上げる
	}
	
	if (Keyboard_Get('Z') == 1){//Zキーが押されたら
		switch (NowSelect){//現在選択中の状態によって処理を分岐
		case eMenu_Game://ゲーム選択中なら
			//mSceneChanger->ChangeScene(eScene_Game);
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Tranp:
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Rpg:
			mSceneChanger->ChangeScene(eScene_Rpg);
			break;
		case eMenu_Rogue:
			mSceneChanger->ChangeScene(eScene_Rogue);
			break;
		case eMenu_Musicroom:
			mSceneChanger->ChangeScene(eScene_Musicroom);
			break;
		case eMenu_Finish:
			exit(1);
		}
	}
}


