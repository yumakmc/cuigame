#pragma once
#include "gameSceneChanger.h"
#include "Task.h"
#include <vector>
#include <string>
#include <map>
using namespace std;



class gameBaseScene :public Task{
public:
	gameBaseScene(gameSceneChanger* changer);
	
	virtual ~gameBaseScene(){};
	virtual void Initialize() override {}   //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;
	virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;            //�`�揈�����I�[�o�[���C�h
	virtual void Draw(vector<string> &tmpfield);
protected:
	int mImageHandle;                //�摜�n���h���i�[�p�ϐ�
	gameSceneChanger* mgameSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X
};