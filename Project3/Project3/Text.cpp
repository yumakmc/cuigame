#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include <assert.h>
#include <windows.h>
using namespace std;

const vector < vector<TextSet> >aad= {
	{
		{ "�l�����񂾂��ǂ��c�c�c�c�c�c", 0,0},
		{	"�G�߂��S���Ă�", 0,0 },
		{"��΂ɑ��߂�����", 0,0 },
		{"�~�͕�������", 0, 0},
		{"�H�͎����Ɣ���Ă₪�邵",  0, 0},
		{"�Ắc�c�c�E���Ă�肽��",  0, 0},
		{"�c�c�c�悵�A��낤", 0, 0},
	},
	{
		{ "�l�����񂾂��ǂ��c�c�c�c�c�c", 0,0 },
		{ "�G�߂��S���Ă�", 0,0 },
		{ "��΂ɑ��߂�����", 0,0 },
		{ "�~�͕�������", 0, 0 },
		{ "�H�͎����Ɣ���Ă₪�邵",  0, 0 },
		{ "�Ắc�c�c�E���Ă�肽��",  0, 0 },
		{ "�c�c�c�悵�A��낤", 0, 0 },
	},
};

const vector<vector<string>> ad = {
	{"�l�����񂾂��ǂ��c�c�c�c�c�c",
	"�G�߂��S���Ă�",
	"��΂ɑ��߂�����",
	"�~�͕�������",
	"�H�͎����Ɣ���Ă₪�邵",
	"�Ắc�c�c�E���Ă�肽��",
	"�c�c�c�悵�A��낤"
	},
	{ 
	"�悵�|�����c�c�c�����Ȃ瓖�R��",
	"�c�c�c���͂ǂ����悤��",
	"�c�c�c�c�c�c",
	"�܂��ǂ����ł�������",
	"�H�ɂ��Ƃ����@���ɗ��R�͂Ȃ�����",
	"�c�c�c�悵�A������"
	},
	{
	"�܂�����l�Ƃ��|����Ƃ́c�c�c",
	"���[�@�ŁA�c�����z���c�c�c",
	"�c�c�c�܂���邵���Ȃ����",
	"�ŏ����炠�����ړI�������񂾂��c�c�c",
	"���������Ȃ�O�ɂ������Ƃ��Ȃ���",
	"�c�c�c�悵�c�c�c"
	},
	{ "��������",
	"���E�ɂ͏t�������c��܂����Ƃ�",
	"�����",
	"�߂ł����߂ł���",
	"�c�c�c���[�Ă��ꂩ��ǂ����悤��",
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
	aDrawableConsole.draw(0, 8, "�y�ł����߂�@�b�s�q�ŃX�L�b�v");
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
