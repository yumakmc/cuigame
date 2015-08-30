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
				{ "�l�����񂾂��ǂ��c�c�c�c�c�c", 0,0 },
				{ "�G�߂��S���Ă�", 0,0 },
				{ "��΂ɑ��߂�����", 0,0 },
				{ "�~�͕�������", 0, 0 },
				{ "�H�͎����Ɣ���Ă₪�邵",  0, 0 },
				{ "�Ắc�c�c�E���Ă�肽��",  0, 0 },
				{ "�c�c�c�悵�A��낤", 0, 0 },
			}
		},

	},{
		{
			"",0,0,
			{
				{ "�悵�|�����c�c�c�����Ȃ瓖�R��", 0,0 },
				{ "�c�c�c���͂ǂ����悤��", 0,0 },
				{ "�c�c�c�c�c�c", 0,0 },
				{ "�܂��ǂ����ł�������", 0, 0 },
				{ "�H�ɂ��Ƃ����@���ɗ��R�͂Ȃ�����",  0, 0 },
				{ "�c�c�c�悵�A������",  0, 0 },
			}
		},
	},{
		{
			"",0,0,
			{
				{ "�܂�����l�Ƃ��|����Ƃ́c�c�c", 0,0 },
				{ "���[�@�ŁA�c�����z���c�c�c", 0,0 },
				{ "�c�c�c�܂���邵���Ȃ����", 0,0 },
				{ "�ŏ����炠�����ړI�������񂾂��c�c�c", 0, 0 },
				{ "���������Ȃ�O�ɂ������Ƃ��Ȃ���",  0, 0 },
				{ "�c�c�c�悵�c�c�c",  0, 0 },
			}
		},
	},{
		{
			"",0,0,
			{
				{ "��������", 0,0 },
				{ "���E�ɂ͏t�������c��܂����Ƃ�", 0,0 },
				{ "�����", 0,0 },
				{ "�߂ł����߂ł���", 0, 0 },
				{ "�c�c�c���[�Ă��ꂩ��ǂ����悤��",  0, 0 },
			}
		},
	},
};
#pragma endregion
#pragma region TEXT_RPG
const vector<vector<Text_Set>> TEXT_RPG = {
	{
		{
			"�t",0,3,
			{
				{ "�c�c�c�c�c�c", 0,0 },
				{ "����c�c�c", 0,0 },
				{ "�����c�c�c�ǂ���", 0,0 },
				{ "�c�c�c�c�c�c", 0,0 },
			}
		},
	},
	{
		{
			"�t",0,3,
			{
				{ "�c�c�c����������", 0,0 },
				{ "����������", 0,0 },
				{ "�v���o����", 0,0 },
			}
		},
		{
			"",1,2,
			{
				{ "", 0,0 },
			}
		},
		{
			"�t",1,2,
			{
				{ "���̐��E�͎����̂��̂�������", 0,0 },
				{ "���̑�n��", 0,0 },
				{ "���݂͂�Ȏ�ɓ��ꂽ�c�c�c", 0, 0 },
			}
		},
		{
			"�t",1,2,
			{
				{ "", 0,0 },
			}
		},
		{
			"�t",1,2,
			{
				{ "���ꂾ������Ȃ�", 0,0 },
				{ "���̖����̋�ł���", 0,0 },
				{ "�S�Ă��c�c�c", 0, 0 },
				{ "�����c�c�c", 0, 0 },
			}
		},
		{
			"��",1,2,
			{
				{ "�c�c�c", 0,0 },
				{ "����͈Ⴄ��", 0,0 },
				{ "�c�c�c", 0,0 },
				{ "��͎��R��", 0,0 },
				{ "��͉����ɂ���������Ȃ�", 0,0 },
				{ "���ꂱ�����󂪋󂽂鏊�Ȃ�", 0,0 },
				{ "�܂�", 0,0 },
				{ "�����x�z����Ȃǎv���オ����r������", 0,0 },
			}
		},
	},
	{
		{
			"�t",2,2,
			{
				{ "�ււցc�c�c", 0,0 },
				{ "����ō��x����", 0,0 },
				{ "�����������̋����ɓ��ꂿ�����", 0,0 },
				{ "���Ă��Ƃ�", 0,0 },
				{ "���[�������͂������܂����ˁH", 0,0 },
			}
		},
		{
			"�H",2,2,
			{
				{ "�c�c�c", 0,0 },
				{ "���������킯�ɂ͂����Ȃ�", 0,0 },
			}
		},
		{
			"�t",2,2,
			{
				{ "�c�c�c���[", 0,0 },
				{ "�܂���", 0,0 },
			}
		},
		{
			"����",2,2,
			{
				{ "���������������x�z����Ƃ������Ƃ�", 0,0 },
				{ "���Ȃ킿����������̓��ɂ����߂�", 0,0 },
				{ "�Ƃ������Ƃ�", 0,0 },
				{ "���ɂ͂��ꂪ�C�ɐH��Ȃ�", 0,0 },
			}
		},
		{
			"����",2,2,
			{
				{ "�����̂��̂����Ă�����", 0, 0 },
				{ "��͂��", 0, 0 },
				{ "�󂱂������𖼏��ɂӂ��킵��", 0, 0 },
				{ "", 0, 0 },
			}
		},
		{
			"����",2,2,
			{
				{ "���", 0, 0 },
				{ "", 0, 0 },
				{ "", 0, 0 },
			}
		},
		{
			"��",2,2,
			{
				{ "�����c", 0, 0 },
				{ "", 0, 0 },
				{ "", 0, 0 },
			}
		},
	},
	{
		{
			"�t",2,2,
			{
				{ "����Ŏ����������̏��L�҂���", 0,0 },
				{ "�u�����̏t�v����", 0,0 },
				{ "�����˂�", 0,0 },
				{ "�������˂�", 0,0 },
			}
		},
		{
			"����",2,2,
			{
				{ "�����̖���������x�z����Ƃ������Ƃ�", 0,0 },
				
			}
		},
		{
			"�t",2,2,
			{
				{ "���Ƃ��Ƌ�Ɏx�z����Ă���Ȃ�", 0,0 },
			}
		},
		{
			"��",2,2,
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
	aDrawableConsole.drawb(0, 0, "�y�ł����߂�@�b�s�q�ŃX�L�b�v",false);
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
