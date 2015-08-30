#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <assert.h>
#include <windows.h>
using namespace std;

#pragma region TEXT_ALL
#pragma region TEXT_TRANP
const vector<vector<Text_Set>> TEXT_TRANP = {
	{
		{
			"",0,0,
			{
				{ "考えたんだけどさ………………", 0,0 },
				{ "季節が４つってさ", 0,0 },
				{ "絶対に多過ぎるよね", 0,0 },
				{ "冬は糞寒いし", 0, 0 },
				{ "秋は自分と被ってやがるし",  0, 0 },
				{ "夏は………殺してやりたい",  0, 0 },
				{ "………よし、やろう", 0, 0 },
			}
		},

	},{
		{
			"",0,0,
			{
				{ "よし倒せた………あいつなら当然か", 0,0 },
				{ "………次はどうしようか", 0,0 },
				{ "………………", 0,0 },
				{ "まあどっちでもいいし", 0, 0 },
				{ "秋にしとくか　特に理由はないけど",  0, 0 },
				{ "………よし、いこう",  0, 0 },
			}
		},
	},{
		{
			"",0,0,
			{
				{ "まさか二人とも倒せるとは………", 0,0 },
				{ "あー　で、残った奴が………", 0,0 },
				{ "………まあやるしかないよね", 0,0 },
				{ "最初からあいつが目的だったんだし………", 0, 0 },
				{ "逃げたくなる前にさっさとやらないと",  0, 0 },
				{ "………よし………",  0, 0 },
			}
		},
	},{
		{
			"",0,0,
			{
				{ "こうして", 0,0 },
				{ "世界には春だけが残りましたとさ", 0,0 },
				{ "おわり", 0,0 },
				{ "めでたしめでたし", 0, 0 },
				{ "………さーてこれからどうしようか",  0, 0 },
			}
		},
	},
};
#pragma endregion
#pragma region TEXT_RPG
const vector<vector<Text_Set>> TEXT_RPG = {
	{
		{
			"春",0,3,
			{
				{ "………………", 0,0 },
				{ "あれ………", 0,0 },
				{ "ここ………どこだ", 0,0 },
				{ "………………", 0,0 },
			}
		},
	},
	{
		{
			"春",0,3,
			{
				{ "………ああそうだ", 0,0 },
				{ "そうだった", 0,0 },
				{ "思い出した", 0,0 },
			}
		},
		{
			"",1,2,
			{
				{ "", 0,0 },
			}
		},
		{
			"春",1,2,
			{
				{ "この世界は自分のものだったんだ", 0,0 },
				{ "この大地も", 0,0 },
				{ "今はみんな手に入れた………", 0, 0 },
			}
		},
		{
			"春",1,2,
			{
				{ "", 0,0 },
			}
		},
		{
			"春",1,2,
			{
				{ "それだけじゃない", 0,0 },
				{ "この無限の空でさえ", 0,0 },
				{ "全てが………", 0, 0 },
				{ "ああ………", 0, 0 },
			}
		},
		{
			"空",1,2,
			{
				{ "………", 0,0 },
				{ "それは違うな", 0,0 },
				{ "………", 0,0 },
				{ "空は自由だ", 0,0 },
				{ "空は何物にも束縛されない", 0,0 },
				{ "それこそが空が空たる所以だ", 0,0 },
				{ "つまり", 0,0 },
				{ "俺を支配するなど思い上がりも甚だしい", 0,0 },
			}
		},
	},
	{
		{
			"春",2,2,
			{
				{ "へへへ………", 0,0 },
				{ "これで今度こそ", 0,0 },
				{ "自分が無限の空を手に入れちゃった", 0,0 },
				{ "ってことで", 0,0 },
				{ "だーれも文句はございませんよね？", 0,0 },
			}
		},
		{
			"？",2,2,
			{
				{ "………", 0,0 },
				{ "そういうわけにはいかない", 0,0 },
			}
		},
		{
			"春",2,2,
			{
				{ "………あー", 0,0 },
				{ "またか", 0,0 },
			}
		},
		{
			"無限",2,2,
			{
				{ "無限を冠する空を支配するということは", 0,0 },
				{ "すなわち無限をも手の内におさめる", 0,0 },
				{ "ということだ", 0,0 },
				{ "私にはそれが気に食わない", 0,0 },
			}
		},
		{
			"無限",2,2,
			{
				{ "多くのものを見てきたが", 0, 0 },
				{ "やはり空が", 0, 0 },
				{ "空こそが私を名乗るにふさわしい", 0, 0 },
				{ "", 0, 0 },
			}
		},
		{
			"無限",2,2,
			{
				{ "空よ", 0, 0 },
				{ "", 0, 0 },
				{ "", 0, 0 },
			}
		},
		{
			"空",2,2,
			{
				{ "ああ…", 0, 0 },
				{ "", 0, 0 },
				{ "", 0, 0 },
			}
		},
	},
	{
		{
			"春",2,2,
			{
				{ "これで自分が無限の所有者かあ", 0,0 },
				{ "「無限の春」かあ", 0,0 },
				{ "いいねえ", 0,0 },
				{ "美しいねえ", 0,0 },
			}
		},
		{
			"無限",2,2,
			{
				{ "無限の名を持つ空を支配するということは", 0,0 },
				
			}
		},
		{
			"春",2,2,
			{
				{ "もともと空に支配されてたんなら", 0,0 },
			}
		},
		{
			"空",2,2,
			{
				{ "", 0,0 },
			}
		},	
	}
};
#pragma endregion
const vector<vector<vector<Text_Set>>> TEXT_ALL = {
	TEXT_TRANP,
	TEXT_RPG,
};
#pragma endregion

Text::Text(gameSceneChanger* changer, const int story, const int enemy = -1) :gameBaseScene(changer),texts(TEXT_ALL[story][enemy]), abackground(TEXT_ALL[story][enemy][0].background) {
	nowline = 0;
	nowtext = 0;
	count = 0;
	aMusic.Play(texts[0].music);
}
void Text::Initialize(){
}

void Text::Update(){
	abackground.Update();
	count++;
	static bool Zispushed=false;
	if (Keyboard_Get('Z')==1||Keyboard_Get(VK_CONTROL)){//z
		if (nowline == texts[nowtext].text_details.size()-1){
			if (nowtext == texts.size()-1){
				mgameSceneChanger->ChangeScene(eGameScene_Main);
				return;
			}
			else{
				nowtext++;
				nowline = 0;
				aMusic.Play(texts[nowtext].music);
				if (texts[nowtext].background != texts[nowtext - 1].background) {
					abackground=*(new BackGround(texts[nowtext].background));
				}
			}
		}
		else{
			nowline++;
		}
	}
}
void Text::Draw(){
	if (texts[nowtext].background) {
		
	}
	abackground.Draw();
	aDrawableConsole.draw(NAMELEFT, NAMEUP, texts[nowtext].name.c_str());
	for (int i = 0; i < TEXTNUM; ++i) {
		if (nowline >= i) {
			aDrawableConsole.draw(NAMELEFT + 2, NAMEUP + (TEXTNUM - i), texts[nowtext].text_details[nowline - i].text.c_str());
		}
	}
	aDrawableConsole.drawb(0, 0, "Ｚですすめる　ＣＴＲでスキップ",false);
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
