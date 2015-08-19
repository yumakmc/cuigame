#pragma once
#include "SceneChanger.h"
#include "Task.h"
#include <vector>
#include <string>
using namespace std;
class BaseScene:public Task{
public:
	BaseScene(SceneChanger* changer);
	virtual ~BaseScene(){};
	virtual void Initialize() override {}   //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;
	virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;            //�`�揈�����I�[�o�[���C�h
	virtual void Draw(vector<string> &tmpfield);
protected:
	int mImageHandle;                //�摜�n���h���i�[�p�ϐ�
	SceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X
};

