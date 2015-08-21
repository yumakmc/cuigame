#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include <assert.h>
using namespace std;

Text::Text(vector<string> atexts, gameSceneChanger* changer) :gameBaseScene(changer),texts(atexts) {
	nowline = 0;
	nowtext = 0;
}
void Text::Initialize(){
}

void Text::Update(){
	static bool Zispushed=false;
	if (Keyboard_Get('Z')==1){//z
		//if (nowline == detail[nowtext].text.size() - 1){
			if (nowtext == texts.size()-1){
				mgameSceneChanger->ChangeScene(eGameScene_CardGame);
				return;
			}
			else{
				nowtext++;
				nowline = 0;
			}
		}
		else{
			nowline++;
		//}
	}
}
void Text::Draw(){
	assert(false);
	//string textline = detail[nowtext].text[nowline];

	//DrawString(TEXTLEFT, TEXTUP, textline.c_str(), GetColor(255, 255, 255));
	if (nowline >= 1){
		//string textline = detail[nowtext].text[nowline-1];
		//DrawString(TEXTLEFT, TEXTUP-TEXTUPSUKIMA, textline.c_str(), GetColor(255, 255, 255));
	}
	if (nowline >= 2){
		//string textline = detail[nowtext].text[nowline-2];
		//DrawString(TEXTLEFT, TEXTUP - TEXTUPSUKIMA*2, textline.c_str(), GetColor(255, 255, 255));
	}
	
}
void Text::Draw(vector<string> &tmpfield) {
	//string textline = detail[nowtext].text[nowline];
	tmpfield[0].replace(0, texts[nowtext].size(), texts[nowtext]);
	if (nowline >= 1) {
		//string textline = detail[nowtext].text[nowline-1];
		//DrawString(TEXTLEFT, TEXTUP-TEXTUPSUKIMA, textline.c_str(), GetColor(255, 255, 255));
	}
	if (nowline >= 2) {
		//string textline = detail[nowtext].text[nowline-2];
		//DrawString(TEXTLEFT, TEXTUP - TEXTUPSUKIMA*2, textline.c_str(), GetColor(255, 255, 255));
	}
}
