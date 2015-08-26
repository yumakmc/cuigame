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
	MyMusic::PlayMusic(-1);//������
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
}
void Menu::Draw(){
	//assert(false);
	afoc.Draw();
	for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
		for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
			aDrawableConsole.draw(x, y, "�@");
		}
	}
	aDrawableConsole.draw(8, 12, "�r�s�n�q�x�P");
	aDrawableConsole.draw(8, 13, "�r�s�n�q�x�Q");
	aDrawableConsole.draw(8, 14, "�r�s�n�q�x�R");
	aDrawableConsole.draw(8, 16, "�d�w�h�s");
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�@���̂������[���[�ɕύX�������@�������邻��
		aDrawableConsole.draw(5, 12, "��");
		break;
	case eMenu_Tranp://�g�����v�I�𒆂Ȃ�	
		aDrawableConsole.draw(5, 13, "��");
		break;
	case eMenu_Rpg://RPG�I�𒆂Ȃ�	
		aDrawableConsole.draw(5, 14, "��");
		break;
	case eMenu_Finish://�I���I�𒆂Ȃ�	
		aDrawableConsole.draw(5, 16, "��");
		break;
	}
}
void Menu::Draw(vector<string> &tmpfield) {
	assert(false);
	//BaseScene::Draw(tmpfield);//�e�N���X�̕`�惁�\�b�h���Ă�////////////////
	//afoc.Draw(tmpfield);
	//for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
	//	for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
	//		//tmpfield[y].replace(2*x, 2, "�@");
	//		aDrawableConsole.draw(x, y, "�@");
	//	}
	//}
	////tmpfield[BLANK_FOR_MENU_UP].replace(2 * BLANK_FOR_MENU_LEFT, (BLANK_FOR_MENU_RIGHT - BLANK_FOR_MENU_LEFT) * 2, "********************************");
	//tmpfield[12].replace(16, 12, "�r�s�n�q�x�P");
	//aDrawableConsole.draw(8, 12, "�r�s�n�q�x�P");
	//tmpfield[14].replace(16, 12, "�r�s�n�q�x�Q");
	//aDrawableConsole.draw(8, 14, "�r�s�n�q�x�Q");
	//tmpfield[16].replace(16, 8, "�d�w�h�s");
	//aDrawableConsole.draw(8, 16, "�d�w�h�s");
	//switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	//case eMenu_Game://�Q�[���I�𒆂Ȃ�@���̂������[���[�ɕύX�������@�������邻��
	//	tmpfield[12].replace(10, 2, "��");
	//	aDrawableConsole.draw(5, 12, "��");
	//	break;
	//case eMenu_Tranp://�g�����v�I�𒆂Ȃ�	
	//	tmpfield[14].replace(10, 14, "��");
	//	aDrawableConsole.draw(5, 14, "��");
	//	break;
	//case eMenu_Finish://�I���I�𒆂Ȃ�	
	//	tmpfield[16].replace(10, 16, "��");
	//	aDrawableConsole.draw(5, 16, "��");
	//	break;
	//}
}

void Menu::Update(){
	afoc.Update();
	if (Keyboard_Get(VK_DOWN) == 1){//���L�[��������Ă�����
		NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//�I����Ԃ��������
	}else if (Keyboard_Get(VK_UP) == 1) {//��L�[��������Ă�����
		NowSelect = eMenu((int(NowSelect) +int(eMenu_count) - 1) % int(eMenu_count));//�I����Ԃ���グ��
	}
	
	if (Keyboard_Get('Z') == 1){//Z�L�[�������ꂽ��
		switch (NowSelect){//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Game://�Q�[���I�𒆂Ȃ�
			//mSceneChanger->ChangeScene(eScene_Game);
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Tranp://�ݒ�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Rpg://�ݒ�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Rpg);
			break;
		case eMenu_Finish:
			exit(1);
		}
	}
}


