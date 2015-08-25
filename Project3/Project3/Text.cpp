#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include <assert.h>
#include <windows.h>
using namespace std;

const vector < vector<TextSet> >aad= {
	{
		{ "考えたんだけどさ………………", 0,0},
		{	"季節が４つってさ", 0,0 },
		{"絶対に多過ぎるよね", 0,0 },
		{"冬は糞寒いし", 0, 0},
		{"秋は自分と被ってやがるし",  0, 0},
		{"夏は………殺してやりたい",  0, 0},
		{"………よし、やろう", 0, 0},
	},
	{
		{ "考えたんだけどさ………………", 0,0 },
		{ "季節が４つってさ", 0,0 },
		{ "絶対に多過ぎるよね", 0,0 },
		{ "冬は糞寒いし", 0, 0 },
		{ "秋は自分と被ってやがるし",  0, 0 },
		{ "夏は………殺してやりたい",  0, 0 },
		{ "………よし、やろう", 0, 0 },
	},
};

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
	"よし倒せた………あいつなら当然か",
	"………次はどうしようか",
	"………………",
	"まあどっちでもいいし",
	"秋にしとくか　特に理由はないけど",
	"………よし、いこう"
	},
	{
	"まさか二人とも倒せるとは………",
	"あー　で、残った奴が………",
	"………まあやるしかないよね",
	"最初からあいつが目的だったんだし………",
	"逃げたくなる前にさっさとやらないと",
	"………よし………"
	},
	{ "こうして",
	"世界には春だけが残りましたとさ",
	"おわり",
	"めでたしめでたし",
	"………さーてこれからどうしようか",
	},
	
};

Text::Text(vector<string> atexts, gameSceneChanger* changer, const int enemy = -1) :gameBaseScene(changer),texts(enemy==-1?atexts:ad[enemy]),textss(aad) {
	nowline = 0;
	nowtext = 0;
}
void Text::Initialize(){
}

void Text::Update(){
	static bool Zispushed=false;
	if (Keyboard_Get('Z')==1||Keyboard_Get(VK_CONTROL)){//z
		if (nowline == textss[nowtext].size()-1){
			if (nowtext == textss.size()-1){
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
		}
	}
}
void Text::Draw(){
	assert(false);
}
void Text::Draw(vector<string> &tmpfield) {
	//string textline = detail[nowtext].text[nowline];
	aDrawableConsole.draw(0, 0, texts[nowtext].c_str());
	//aDrawableConsole.draw(0, 1, textss[nowtext][nowline].text.c_str());
	aDrawableConsole.draw(0, 8, "Ｚですすめる　ＣＴＲでスキップ");
	for (int i = 0; i < TEXTNUM; ++i) {
		if (nowline >= i) {
			aDrawableConsole.draw(0, (TEXTNUM-i), textss[nowtext][nowline-i].text.c_str());
		}
	}
	//if (nowline >= 1) {
	//	//string textline = detail[nowtext].text[nowline-1];
	//	//DrawString(TEXTLEFT, TEXTUP-TEXTUPSUKIMA, textline.c_str(), GetColor(255, 255, 255));
	//}
	//if (nowline >= 2) {
	//	//string textline = detail[nowtext].text[nowline-2];
	//	//DrawString(TEXTLEFT, TEXTUP - TEXTUPSUKIMA*2, textline.c_str(), GetColor(255, 255, 255));
	//}
}
