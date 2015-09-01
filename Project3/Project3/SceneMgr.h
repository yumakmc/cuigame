#pragma once
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Game.h"
#include "Rpg.h"
#include "Musicroom.h"
#include "Rogue.h"


class SceneMgr :public SceneChanger, Task{
public:
	SceneMgr();
	void Initialize() override;//������
	void Finalize() override;//�I������
	//�X�V
	void Update();
	
	//�`��
	void Draw();
	void Draw(vector<string> &tmpField);
	// ���� nextScene �ɃV�[����ύX����
	void ChangeScene(eScene nextScene)override;

private:
	BaseScene* mScene;    //�V�[���Ǘ��ϐ�
	eScene mNextScene;    //���̃V�[���Ǘ��ϐ�
};
