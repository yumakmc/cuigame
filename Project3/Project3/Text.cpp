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
		"�H�H�H",0,{
			{ "�l�����񂾂��ǂ��c�c�c�c�c�c", 0,0},
			{	"�G�߂��S���Ă�", 0,0 },
			{"��΂ɑ��߂�����", 0,0 },
			{"�~�͕�������", 0, 0},
			{"�H�͎����Ɣ���Ă₪�邵",  0, 0},
			{"�Ắc�c�c�E���Ă�肽��",  0, 0},
			{"�c�c�c�悵�A��낤", 0, 0},
		}
	},
	{
		"�t",1,{
			{ "�l�����񂾂��ǂ��c�c�c�c�c�c", 0,0 },
			{ "�G�߂��S���Ă�", 0,0 },
			{ "��΂ɑ��߂�����", 0,0 },
			{ "�~�͕�������", 0, 0 },
			{ "�H�͎����Ɣ���Ă₪�邵",  0, 0 },
			{ "�Ắc�c�c�E���Ă�肽��",  0, 0 },
			{ "�c�c�c�悵�A��낤", 0, 0 },
		}
	},
};
const vector < Text_Set >bad = {
	{
		"�t",0,{
			{ "�c�c�c����������", 0,0 },
			{ "����������", 0,0 },
			{ "�v���o����", 0,0 },
			{ "", 0, 0 },
			{ "",  0, 0 },
			{ "",  0, 0 },
			{ "", 0, 0 },
		}
	},
	{
		"�t",1,{
			{ "���̐��E�͎����̂��̂�������", 0,0 },
			{ "�S�Ă�", 0,0 },
			{ "���̍L��Ȓn�A", 0,0 },
			{ "�����̋�A", 0, 0 },
			{ "�����̋�A", 0, 0 },

		}
	},
	{
		"�H",1,{
			{ "����͈Ⴄ��", 0,0 },
		}
	},
	{
		"�t",1,{
			{ "�H", 0,0 },
		}
	},
	{
		"��",1,{
			{ "��͎��R��", 0,0 },
			{ "���͉����ɂ������Ȃ�", 0,0 },
			{ "��͎��R�̏ے�", 0,0 },
			{ "��͎��R�̏ے�", 0,0 },
			{ "��͎��R�̏ے�", 0,0 },
		}
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
	aDrawableConsole.draw(0, 0, "�y�ł����߂�@�b�s�q�ŃX�L�b�v");
}
void Text::Draw(vector<string> &tmpfield) {	
	assert(false);
	/*aDrawableConsole.draw(NAMELEFT, NAMEUP, textss[nowtext].name.c_str());
	for (int i = 0; i < TEXTNUM; ++i) {
		if (nowline >= i) {
			aDrawableConsole.draw(NAMELEFT+2, NAMEUP+(TEXTNUM-i), textss[nowtext].text_details[nowline-i].text.c_str());
		}
	}
	aDrawableConsole.draw(0,0, "�y�ł����߂�@�b�s�q�ŃX�L�b�v");*/
}
