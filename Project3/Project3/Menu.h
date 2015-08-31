#pragma once
#include <windows.h>
#include <iostream>
#include <map>
#include "FallingObjectCollection.h"
#include "BaseScene.h"

enum eMenu{
	eMenu_Game,        //�Q�[��
	eMenu_Tranp,    //�g�����v
	eMenu_Rpg,//�q����
	eMenu_Musicroom,//�l�t�r�h�b�q�n�n�l
	eMenu_Finish,//�I��
	eMenu_count//�����ŗv�f�����킩��
};
class Menu:public BaseScene{
public:
	Menu(SceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override ;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpField) override;
private:
	eMenu NowSelect;
	FallingObjectCollection afoc;
};