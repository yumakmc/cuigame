#pragma once
#include "Keyboard.h"
#include "DrawableConsole.h"

#include "Music.h"
#include "Musicroom.h"

#include <assert.h>
#include <iostream>
using namespace std;



Musicroom::Musicroom(SceneChanger* changer) : BaseScene(changer){
	aMusic.Play(-1);
	NowSelect = 0;
}
void Musicroom::Initialize() {
}
void Musicroom::Draw() {
	//assert(false);
	
	aDrawableConsole.draw(15, 12, "�l�t�r�h�b�@�P");
	aDrawableConsole.draw(15, 13, "�l�t�r�h�b�@�Q");
	aDrawableConsole.draw(15, 14, "�l�t�r�h�b�@�R");
	aDrawableConsole.draw(15, 15, "�l�t�r�h�b�@�S");
	aDrawableConsole.draw(15, 16, "�a�`�b�j�s�n�l�d�m�t");
	aDrawableConsole.draw(13, 12+NowSelect, "��");

}

void Musicroom::Update() {
	if (Keyboard_Get(VK_DOWN) == 1) {//���L�[��������Ă�����
		NowSelect = (int(NowSelect) + 1) % int(5);//�I����Ԃ��������
	}
	else if (Keyboard_Get(VK_UP) == 1) {//��L�[��������Ă�����
		NowSelect = ((int(NowSelect) + int(5) - 1) % int(5));//�I����Ԃ���グ��
	}

	if (Keyboard_Get('Z') == 1) {//Z�L�[�������ꂽ��
		switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		
		case 4:
			mSceneChanger->ChangeScene(eScene_Menu);
			break;
		default:
			
			aMusic.Play(NowSelect + 2);
		}
	}
}