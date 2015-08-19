#pragma once
#include "SceneMgr.h"

SceneMgr::SceneMgr() :
	mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Menu(this);
}
void SceneMgr::Initialize(){
	mScene->Initialize();
}
void SceneMgr::Finalize(){
	mScene->Finalize();
}
//�X�V
void SceneMgr::Update(){
	if (mNextScene != eScene_None){    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		switch (mNextScene){       //�V�[���ɂ���ď����𕪊�
		case eScene_Menu:    //���݂̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Menu(this);
			break;//�ȉ���
		case eScene_Game:
			mScene = (BaseScene*) new Game(this);
			break;
		case eScene_Tranp:
			mScene = (BaseScene*) new Tranp(this);
			break;
		}
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize();    //�V�[����������
	}
	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMgr:: Draw(){
	mScene->Draw();

}
void SceneMgr::Draw(vector<string> &tmpField) {
	mScene->Draw(tmpField);
}
// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(eScene NextScene){
	mNextScene = NextScene;
}