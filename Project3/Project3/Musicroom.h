#pragma once
#include <windows.h>
#include <iostream>
#include <map>
#include "SceneChanger.h"
#include "BaseScene.h"


class Musicroom :public BaseScene {
public:
	Musicroom(SceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
								   //void Finalize() override ;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	int NowSelect;

};