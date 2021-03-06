#pragma once
#include "Keyboard.h"
#include "DrawableConsole.h"

#include "Music.h"
#include "Musicroom.h"

#include <assert.h>
#include <iostream>
using namespace std;

Musicroom::Musicroom(SceneChanger* changer) : BaseScene(changer){
	aMusic.Play(-1);
	NowSelect = 0;
}
void Musicroom::Initialize() {
}
void Musicroom::Draw() {
	//assert(false);
	
	aDrawableConsole.draw(15, 12, "ＭＵＳＩＣ　１");
	aDrawableConsole.draw(15, 13, "ＭＵＳＩＣ　２");
	aDrawableConsole.draw(15, 14, "ＭＵＳＩＣ　３");
	aDrawableConsole.draw(15, 15, "ＭＵＳＩＣ　４");
	aDrawableConsole.draw(15, 16, "ＢＡＣＫＴＯＭＥＮＵ");
	aDrawableConsole.draw(13, 12+NowSelect, "●");
}

void Musicroom::Update() {
	if (Keyboard_Get(VK_DOWN) == 1) {//下キーが押されていたら
		NowSelect = (int(NowSelect) + 1) % int(5);//選択状態を一つ下げる
	}
	else if (Keyboard_Get(VK_UP) == 1) {//上キーが押されていたら
		NowSelect = ((int(NowSelect) + int(5) - 1) % int(5));//選択状態を一つ上げる
	}

	if (Keyboard_Get('Z') == 1) {//Zキーが押されたら
		switch (NowSelect) {//現在選択中の状態によって処理を分岐
		
		case 4:
			mSceneChanger->ChangeScene(eScene_Menu);
			break;
		default:
			
			aMusic.Play(NowSelect + 2);
		}
	}
}