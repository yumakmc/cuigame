#pragma once
#include "Menu.h"
#include <assert.h>
#include <iostream>
using namespace std;



Menu::Menu(SceneChanger* changer) : BaseScene(changer),afoc(){
	
	NowSelect = eMenu_Game;
}
void Menu::Initialize(){
	
}
void Menu::Draw(){
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	
	
	//DrawString(280, FINISH_Y, "�����", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect){//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�
		break;
	case eMenu_Config://�ݒ�I�𒆂Ȃ�	
		break;
	case eMenu_Finish://�ݒ�I�𒆂Ȃ�	
		break;
	}
	afoc.Draw();
	//DrawString(250, y, "��", GetColor(255, 255, 255));
}
void Menu::Draw(vector<string> &tmpfield) {
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�////////////////
					  //DrawString(280, FINISH_Y, "�����", GetColor(255, 255, 255));
	int y = 0;
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�
		break;
	case eMenu_Config://�ݒ�I�𒆂Ȃ�	
		break;
	case eMenu_Finish://�ݒ�I�𒆂Ȃ�	
		break;
	}
	afoc.Draw(tmpfield);
	//DrawString(250, y, "��", GetColor(255, 255, 255));
}

void Menu::Update(){
	afoc.Update();
	//if (Keyboard_Get(KEY_INPUT_DOWN) == 1){//���L�[��������Ă�����
	//	NowSelect = eMenu((int(NowSelect) + 1) % int(eMenu_count));//�I����Ԃ��������
	//}
	//
	//if (Keyboard_Get(KEY_INPUT_RETURN) == 1){//�G���^�[�L�[�������ꂽ��
	//	switch (NowSelect){//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
	//	case eMenu_Game://�Q�[���I�𒆂Ȃ�
	//		mSceneChanger->ChangeScene(eScene_Game);
	//		break;
	//	case eMenu_Config://�ݒ�I�𒆂Ȃ�
	//		mSceneChanger->ChangeScene(eScene_Config);
	//		break;
	//	case eMenu_Finish:
	//		exit(1);
	//	}
	//}
}


