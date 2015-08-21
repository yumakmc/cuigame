#pragma once
#include "Menu.h"
#include "Keyboard.h"
#include <assert.h>
#include <iostream>
using namespace std;

const int BLANK_FOR_MENU_UP = 10;
const int BLANK_FOR_MENU_DOWN = 18;
const int BLANK_FOR_MENU_LEFT = 2;
const int BLANK_FOR_MENU_RIGHT = 18;

Menu::Menu(SceneChanger* changer) : BaseScene(changer),afoc(){
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
	
}
void Menu::Draw(){
	assert(false);
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	
	
	//DrawString(280, FINISH_Y, "�����", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect){//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�
		break;
	case eMenu_Tranp://�g�����v�I�𒆂Ȃ�	
		break;
	case eMenu_Finish://�ݒ�I�𒆂Ȃ�	
		break;
	}
	afoc.Draw();
}
void Menu::Draw(vector<string> &tmpfield) {
	BaseScene::Draw(tmpfield);//�e�N���X�̕`�惁�\�b�h���Ă�////////////////
	afoc.Draw(tmpfield);
	for (int y = BLANK_FOR_MENU_UP; y < BLANK_FOR_MENU_DOWN; ++y) {
		for (int x = BLANK_FOR_MENU_LEFT; x < BLANK_FOR_MENU_RIGHT; ++x) {
			tmpfield[y].replace(2*x, 2, "�@");
		}
	}
	//tmpfield[BLANK_FOR_MENU_UP].replace(2 * BLANK_FOR_MENU_LEFT, (BLANK_FOR_MENU_RIGHT - BLANK_FOR_MENU_LEFT) * 2, "********************************");
	tmpfield[12].replace(16, 12, "�r�s�n�q�x�P");
	tmpfield[14].replace(16, 12, "�r�s�n�q�x�Q");
	tmpfield[16].replace(16, 8, "�d�w�h�s");
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�@���̂������[���[�ɕύX�������@�������邻��
		tmpfield[12].replace(10, 2, "��");
		break;
	case eMenu_Tranp://�g�����v�I�𒆂Ȃ�	
		tmpfield[14].replace(10, 2, "��");
		break;
	case eMenu_Finish://�I���I�𒆂Ȃ�	
		tmpfield[16].replace(10, 2, "��");
		break;
	}
}

void Menu::Update(){
	afoc.Update();
	if (Keyboard_Get(VK_DOWN) == 1){//���L�[��������Ă�����
		NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//�I����Ԃ��������
	}else if (Keyboard_Get(VK_UP) == 1) {//��L�[��������Ă�����
		NowSelect = eMenu((int(NowSelect) +int(eMenu_count) - 1) % int(eMenu_count));//�I����Ԃ���グ��
	}
	
	if (Keyboard_Get(VK_RETURN) == 1){//�G���^�[�L�[�������ꂽ��
		switch (NowSelect){//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Game://�Q�[���I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Game);
			break;
		case eMenu_Tranp://�ݒ�I�𒆂Ȃ�
			mSceneChanger->ChangeScene(eScene_Tranp);
			break;
		case eMenu_Finish:
			exit(1);
		}
	}
}


