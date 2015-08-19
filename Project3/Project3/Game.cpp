#pragma once
#include "Game.h"
#include <vector>

//�Q�[�����

Game::Game(SceneChanger* changer) : BaseScene(changer) {
	//mGameScene = new Text(d,this);
}
void Game::Initialize(){
	//mImageHandle = LoadGraph("�摜//haikei");
}
void Game::Update(){
	//if (CheckHitKey(KEY_INPUT_ESCAPE) != 0){ //Esc�L�[��������Ă�����
	//	mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	//}
	if (mNextScene != eGameScene_None){    //���̃V�[�����Z�b�g����Ă�����
		mGameScene->Finalize();//���݂̃V�[���̏I�����������s
		switch (mNextScene){       //�V�[���ɂ���ď����𕪊�
		case eGameScene_Text:    //���݂̉�ʂ����j���[�Ȃ�
			//mGameScene = (gameBaseScene*) new Text(d,this);
			break;//�ȉ���
		
		}
		mNextScene = eGameScene_None;    //���̃V�[�������N���A
		mGameScene->Initialize();    //�V�[����������
	}

	mGameScene->Update(); //�V�[���̍X�V
}
void Game::Draw(){
	//DrawString(0, 0, "�Q�[�����", GetColor(255, 255, 255));
	BaseScene::Draw();
	mGameScene->Draw();
}

void Game::ChangeScene(eGameScene NextScene){
	mNextScene = NextScene;
}