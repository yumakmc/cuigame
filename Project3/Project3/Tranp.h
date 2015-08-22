#pragma once
#include <windows.h>
#include <iostream>
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gamebaseScene.h"
#include "Text.h"

class Tranp :public gameSceneChanger, BaseScene {
public:
	Tranp::Tranp(SceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
								   //void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpfield)override ;
	void ChangeScene(eGameScene nextScene)override;
private:
	//BaseGameScene* mScene;    //�V�[���Ǘ��ϐ�
	gameBaseScene* mGameScene;
	eGameScene mNextScene;    //���̃V�[���Ǘ��ϐ�
	int nextenemy;
	int nexttext;
};