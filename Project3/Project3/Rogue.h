#pragma once
#include <windows.h>
#include <iostream>
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gamebaseScene.h"
#include "Text.h"
#include "RogueGame.h"


class Rogue :public gameSceneChanger, BaseScene {
public:
	Rogue::Rogue(SceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B

	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void ChangeScene(eGameScene nextScene)override;
private:
	gameBaseScene* mGameScene;
	eGameScene mNextScene;    //���̃V�[���Ǘ��ϐ�
};
