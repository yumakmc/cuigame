#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "DrawBackGround.h"
#include <assert.h>
#include <windows.h>
using namespace std;

const vector < Text_Set >aad= {
	{
		"？？？",0,{
			{ "考えたんだけどさ………………", 0,0},
			{	"季節が４つってさ", 0,0 },
			{"絶対に多過ぎるよね", 0,0 },
			{"冬は糞寒いし", 0, 0},
			{"秋は自分と被ってやがるし",  0, 0},
			{"夏は………殺してやりたい",  0, 0},
			{"………よし、やろう", 0, 0},
		}
	},
	{
		"春",1,{
			{ "考えたんだけどさ………………", 0,0 },
			{ "季節が４つってさ", 0,0 },
			{ "絶対に多過ぎるよね", 0,0 },
			{ "冬は糞寒いし", 0, 0 },
			{ "秋は自分と被ってやがるし",  0, 0 },
			{ "夏は………殺してやりたい",  0, 0 },
			{ "………よし、やろう", 0, 0 },
		}
	},
};
const vector < Text_Set >bad = {
	{
		"春",0,{
			{ "………ああそうだ", 0,0 },
			{ "そうだった", 0,0 },
			{ "思い出した", 0,0 },
			{ "", 0, 0 },
			{ "",  0, 0 },
			{ "",  0, 0 },
			{ "", 0, 0 },
		}
	},
	{
		"春",1,{
			{ "この世界は自分のものだったんだ", 0,0 },
			{ "全てが", 0,0 },
			{ "この広大な地、", 0,0 },
			{ "無限の空、", 0, 0 },
			{ "無限の空、", 0, 0 },

		}
	},
	{
		"？",1,{
			{ "それは違うな", 0,0 },
		}
	},
	{
		"春",1,{
			{ "？", 0,0 },
		}
	},
	{
		"空",1,{
			{ "空は自由だ", 0,0 },
			{ "俺は何物にも囚われない", 0,0 },
			{ "空は自由の象徴", 0,0 },
			{ "空は自由の象徴", 0,0 },
			{ "空は自由の象徴", 0,0 },
		}
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

Text::Text(gameSceneChanger* changer, const int enemy = -1) :gameBaseScene(changer),textss(aad) {
	nowline = 0;
	nowtext = 0;
	count = 0;
}
void Text::Initialize(){
}

void Text::Update(){
	count++;
	static bool Zispushed=false;
	if (Keyboard_Get('Z')==1||Keyboard_Get(VK_CONTROL)){//z
		if (nowline == textss[nowtext].text_details.size()-1){
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
	if (textss[nowtext].background) {
		DrawBackGround(1);
	}
	aDrawableConsole.draw(NAMELEFT, NAMEUP, textss[nowtext].name.c_str());
	for (int i = 0; i < TEXTNUM; ++i) {
		if (nowline >= i) {
			aDrawableConsole.draw(NAMELEFT + 2, NAMEUP + (TEXTNUM - i), textss[nowtext].text_details[nowline - i].text.c_str());
		}
	}
	aDrawableConsole.draw(0, 0, "Ｚですすめる　ＣＴＲでスキップ");
}
void Text::Draw(vector<string> &tmpfield) {	
	assert(false);
	/*aDrawableConsole.draw(NAMELEFT, NAMEUP, textss[nowtext].name.c_str());
	for (int i = 0; i < TEXTNUM; ++i) {
		if (nowline >= i) {
			aDrawableConsole.draw(NAMELEFT+2, NAMEUP+(TEXTNUM-i), textss[nowtext].text_details[nowline-i].text.c_str());
		}
	}
	aDrawableConsole.draw(0,0, "Ｚですすめる　ＣＴＲでスキップ");*/
}
