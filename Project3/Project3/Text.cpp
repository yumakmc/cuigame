#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include <assert.h>
#include <windows.h>
using namespace std;

const vector<vector<string>> ad = {
	{"考えたんだけどさ………………",
	"季節が４つってさ",
	"絶対に多過ぎるよね",
	"冬は糞寒いし",
	"秋は自分と被ってやがるし",
	"夏は………殺してやりたい",
	"………よし、やろう"
	},
	{ 
	"やった倒せた………",
	"………次はどうしようか",
	"………………",
	"まあどっちでもいいし",
	"秋にしとくか　特に理由はないけど",
	"………よし、いこう"
	},
	{
	"まさか二人とも倒せるとは………流石自分",
	"あーで、残った奴が………",
	"………まあやるしかないよね",
	"最初からあいつが目的だったんだし………",
	"逃げたくなる前にさっさとやらないと",
	"………よし………"
	},
	{ "こうして",
	"せかいには春だけが残りました。",
	"春は他の季節からすべてを",
	"最初からあいつが目的だったんだし………",
	"逃げたくなる前にさっさとやらないと",
	"………よし………"
	},
	
};

Text::Text(vector<string> atexts, gameSceneChanger* changer, const int enemy = -1) :gameBaseScene(changer),texts(enemy==-1?atexts:ad[enemy]) {
	nowline = 0;
	nowtext = 0;
}
void Text::Initialize(){
}

void Text::Update(){
	static bool Zispushed=false;
	if (Keyboard_Get('Z')==1||Keyboard_Get(VK_CONTROL)){//z
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
}
void Text::Draw(vector<string> &tmpfield) {
	//string textline = detail[nowtext].text[nowline];
	tmpfield[0].replace(0, texts[nowtext].size(), texts[nowtext]);
	//if (nowline >= 1) {
	//	//string textline = detail[nowtext].text[nowline-1];
	//	//DrawString(TEXTLEFT, TEXTUP-TEXTUPSUKIMA, textline.c_str(), GetColor(255, 255, 255));
	//}
	//if (nowline >= 2) {
	//	//string textline = detail[nowtext].text[nowline-2];
	//	//DrawString(TEXTLEFT, TEXTUP - TEXTUPSUKIMA*2, textline.c_str(), GetColor(255, 255, 255));
	//}
}
