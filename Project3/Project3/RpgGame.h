#pragma once
#include "gameBaseScene.h"

class RpgGame :public gameBaseScene {
public:
	RpgGame(gameSceneChanger* changer,const int aopponent);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
private:
	const int opponent;
};