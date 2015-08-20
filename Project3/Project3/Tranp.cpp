#pragma once
#include "Tranp.h"
#include "Keyboard.h"
#include "TranpGame.h"
#include <assert.h>
#include <vector>

vector<string> d;

Tranp::Tranp(SceneChanger* changer) : BaseScene(changer) {
	d.push_back("�l�����񂾂��ǂ��c�c�c�c�c�c");
	d.push_back("�G�߂��S���Ă�");
	d.push_back("��΂ɑ��߂�����");
	d.push_back("�Ă͕��������~�͕�������");
	d.push_back("�H�́c�c�c����Ă₪�邵");
	d.push_back("�c�c�c�悵�A��낤");
	mGameScene = new Text(d,this);
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
			mGameScene = (gameBaseScene*) new Text(d, this);
			break;//�ȉ���
		case eGameScene_CardGame:    //���݂̉�ʂ����j���[�Ȃ�
			mGameScene = (gameBaseScene*) new TranpGame(0,d, this);
			break;//�ȉ���
		}
		mNextScene = eGameScene_None;    //���̃V�[�������N���A
		mGameScene->Initialize();    //�V�[����������
	}
	mGameScene->Update(); //�V�[���̍X�V
}
void Tranp::Draw() {
	assert(false);
	BaseScene::Draw();
	mGameScene->Draw();
}
void Tranp::Draw(vector<string> &tmpfield) {
	BaseScene::Draw(tmpfield);
	mGameScene->Draw(tmpfield);
}
void Tranp::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}

