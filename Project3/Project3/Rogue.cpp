#include "Rogue.h"
#include "Keyboard.h"

#include "Music.h"



Rogue::Rogue(SceneChanger* changer) : BaseScene(changer) {
	mGameScene = new Text(this, 1, 0);

}
void Rogue::Initialize() {
}
void Rogue::Update() {
	if (Keyboard_Get(VK_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (mNextScene != eGameScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mGameScene->Finalize();//���݂̃V�[���̏I�����������s
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eGameScene_Text:    //���݂̉�ʂ����j���[�Ȃ�

			mGameScene = (gameBaseScene*) new Text(this, 1, 0);
			break;//�ȉ���
		case eGameScene_Main:

			mGameScene = (gameBaseScene*) new roguegame::RogueGame(this);
			
			break;//�ȉ���
		}
		mNextScene = eGameScene_None;    //���̃V�[�������N���A
		mGameScene->Initialize();    //�V�[����������
	}
	mGameScene->Update(); //�V�[���̍X�V
}
void Rogue::Draw() {
	BaseScene::Draw();
	mGameScene->Draw();
}

void Rogue::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}
