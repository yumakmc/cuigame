#pragma once
#include "Tranp.h"
#include "Keyboard.h"
#include <vector>

//�Q�[�����

Tranp::Tranp(SceneChanger* changer) : BaseScene(changer) {
	//mGameScene = new Text(d,this);
}
void Tranp::Initialize() {
}
void Tranp::Update() {
	if (Keyboard_Get(VK_ESCAPE) != 0){ //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (mNextScene != eGameScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mGameScene->Finalize();//���݂̃V�[���̏I�����������s
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eGameScene_Text:    //���݂̉�ʂ����j���[�Ȃ�
								 //mGameScene = (gameBaseScene*) new Text(d,this);
			break;//�ȉ���
		}
		mNextScene = eGameScene_None;    //���̃V�[�������N���A
		mGameScene->Initialize();    //�V�[����������
	}
	mGameScene->Update(); //�V�[���̍X�V
}
void Tranp::Draw() {
	//DrawString(0, 0, "�Q�[�����", GetColor(255, 255, 255));
	BaseScene::Draw();
	mGameScene->Draw();
}
void Tranp::Draw(vector<string> &tmpfield) {
	//DrawString(0, 0, "�Q�[�����", GetColor(255, 255, 255));
	BaseScene::Draw();
	mGameScene->Draw();
}
void Tranp::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}

