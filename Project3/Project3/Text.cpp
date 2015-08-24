#pragma once 
#include "Text.h"
#include "Keyboard.h"
#include <assert.h>
#include <windows.h>
using namespace std;

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
	tmpfield[8].replace(0, 30, "�y�ł����߂�@�b�s�q�ŃX�L�b�v");//�v�C��
	//if (nowline >= 1) {
	//	//string textline = detail[nowtext].text[nowline-1];
	//	//DrawString(TEXTLEFT, TEXTUP-TEXTUPSUKIMA, textline.c_str(), GetColor(255, 255, 255));
	//}
	//if (nowline >= 2) {
	//	//string textline = detail[nowtext].text[nowline-2];
	//	//DrawString(TEXTLEFT, TEXTUP - TEXTUPSUKIMA*2, textline.c_str(), GetColor(255, 255, 255));
	//}
}
