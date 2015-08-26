#pragma once
#include "Menu.h"
#include "Keyboard.h"
#include "DrawableConsole.h"

#include "PlayMusic.h"

#include <assert.h>
#include <iostream>
using namespace std;

const int BLANK_FOR_MENU_UP = 10;
const int BLANK_FOR_MENU_DOWN = 18;
const int BLANK_FOR_MENU_LEFT = 2;
const int BLANK_FOR_MENU_RIGHT = 18;

Menu::Menu(SceneChanger* changer) : BaseScene(changer),afoc(){
	MyMusic::PlayMusic(-1);//‰¹Á‚·
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
}
void Menu::Draw(){
	//assert(false);
	afoc.Draw();
	for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
		for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
			aDrawableConsole.draw(x, y, "@");
		}
	}
	aDrawableConsole.draw(8, 12, "‚r‚s‚n‚q‚x‚P");
	aDrawableConsole.draw(8, 13, "‚r‚s‚n‚q‚x‚Q");
	aDrawableConsole.draw(8, 14, "‚r‚s‚n‚q‚x‚R");
	aDrawableConsole.draw(8, 16, "‚d‚w‚h‚s");
	switch (NowSelect) {//Œ»İ‚Ì‘I‘ğó‘Ô‚É]‚Á‚Äˆ—‚ğ•ªŠò
	case eMenu_Game://ƒQ[ƒ€‘I‘ğ’†‚È‚ç@‚»‚Ì‚¤‚¿‚©[‚°[‚É•ÏX‚µ‚½‚¢@À‘•‚¾‚é‚»‚¤
		aDrawableConsole.draw(5, 12, "œ");
		break;
	case eMenu_Tranp://ƒgƒ‰ƒ“ƒv‘I‘ğ’†‚È‚ç	
		aDrawableConsole.draw(5, 13, "œ");
		break;
	case eMenu_Rpg://RPG‘I‘ğ’†‚È‚ç	
		aDrawableConsole.draw(5, 14, "œ");
		break;
	case eMenu_Finish://I—¹‘I‘ğ’†‚È‚ç	
		aDrawableConsole.draw(5, 16, "œ");
		break;
	}
}
void Menu::Draw(vector<string> &tmpfield) {
	assert(false);
	//BaseScene::Draw(tmpfield);//eƒNƒ‰ƒX‚Ì•`‰æƒƒ\ƒbƒh‚ğŒÄ‚Ô////////////////
	//afoc.Draw(tmpfield);
	//for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
	//	for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
	//		//tmpfield[y].replace(2*x, 2, "@");
	//		aDrawableConsole.draw(x, y, "@");
	//	}
	//}
	////tmpfield[BLANK_FOR_MENU_UP].replace(2 * BLANK_FOR_MENU_LEFT, (BLANK_FOR_MENU_RIGHT - BLANK_FOR_MENU_LEFT) * 2, "********************************");
	//tmpfield[12].replace(16, 12, "‚r‚s‚n‚q‚x‚P");
	//aDrawableConsole.draw(8, 12, "‚r‚s‚n‚q‚x‚P");
	//tmpfield[14].replace(16, 12, "‚r‚s‚n‚q‚x‚Q");
	//aDrawableConsole.draw(8, 14, "‚r‚s‚n‚q‚x‚Q");
	//tmpfield[16].replace(16, 8, "‚d‚w‚h‚s");
	//aDrawableConsole.draw(8, 16, "‚d‚w‚h‚s");
	//switch (NowSelect) {//Œ»İ‚Ì‘I‘ğó‘Ô‚É]‚Á‚Äˆ—‚ğ•ªŠò
	//case eMenu_Game://ƒQ[ƒ€‘I‘ğ’†‚È‚ç@‚»‚Ì‚¤‚¿‚©[‚°[‚É•ÏX‚µ‚½‚¢@À‘•‚¾‚é‚»‚¤
	//	tmpfield[12].replace(10, 2, "œ");
	//	aDrawableConsole.draw(5, 12, "œ");
	//	break;
	//case eMenu_Tranp://ƒgƒ‰ƒ“ƒv‘I‘ğ’†‚È‚ç	
	//	tmpfield[14].replace(10, 14, "œ");
	//	aDrawableConsole.draw(5, 14, "œ");
	//	break;
	//case eMenu_Finish://I—¹‘I‘ğ’†‚È‚ç	
	//	tmpfield[16].replace(10, 16, "œ");
	//	aDrawableConsole.draw(5, 16, "œ");
	//	break;
	//}
}

void Menu::Update(){
	afoc.Update();
	if (Keyboard_Get(VK_DOWN) == 1){//‰ºƒL[‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
		NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//‘I‘ğó‘Ô‚ğˆê‚Â‰º‚°‚é
	}else if (Keyboard_Get(VK_UP) == 1) {//ãƒL[‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
		NowSelect = eMenu((int(NowSelect) +int(eMenu_count) - 1) % int(eMenu_count));//‘I‘ğó‘Ô‚ğˆê‚Âã‚°‚é
	}
	
	if (Keyboard_Get('Z') == 1){//ZƒL[‚ª‰Ÿ‚³‚ê‚½‚ç
		switch (NowSelect){//Œ»İ‘I‘ğ’†‚Ìó‘Ô‚É‚æ‚Á‚Äˆ—‚ğ•ªŠò
		case eMenu_Game://ƒQ[ƒ€‘I‘ğ’†‚È‚ç
			//mSceneChanger->ChangeScene(eScene_Game);
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Tranp://İ’è‘I‘ğ’†‚È‚ç
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Rpg://İ’è‘I‘ğ’†‚È‚ç
			mSceneChanger->ChangeScene(eScene_Rpg);
			break;
		case eMenu_Finish:
			exit(1);
		}
	}
}


