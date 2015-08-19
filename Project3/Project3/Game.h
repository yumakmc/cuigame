#pragma once

#include <windows.h>
#include <iostream>
//#include "Shlwapi.h"
//#pragma comment(lib, "shlwapi.lib")

#include "BaseScene.h"
#include "Tranp.h"
#include "gameSceneChanger.h"
#include "gamebaseScene.h"

class Game:public gameSceneChanger,BaseScene{
public:
	Game::Game(SceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpfield)override {};
	void ChangeScene(eGameScene nextScene)override;
private:
	//BaseGameScene* mScene;    //�V�[���Ǘ��ϐ�
	gameBaseScene* mGameScene;
	eGameScene mNextScene;    //���̃V�[���Ǘ��ϐ�
};
