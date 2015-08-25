#include "Rpg.h"
#include "Keyboard.h"

Rpg::Rpg(SceneChanger* changer) : BaseScene(changer) {
	nextenemy = 0;
	mGameScene = new Text(this, nextenemy);
}
void Rpg::Initialize() {
}
void Rpg::Update() {
	if (Keyboard_Get(VK_ESCAPE) != 0) { //Esc�L�[��������Ă�����
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (mNextScene != eGameScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mGameScene->Finalize();//���݂̃V�[���̏I�����������s
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eGameScene_Text:    //���݂̉�ʂ����j���[�Ȃ�
			mGameScene = (gameBaseScene*) new Text(this, nextenemy);
			break;//�ȉ���
		case eGameScene_Main:
			if (nextenemy == 3) {
				mSceneChanger->ChangeScene(eScene_Menu);
			}
			else {
				mGameScene = (gameBaseScene*) new RpgGame(this,nextenemy);
				nextenemy++;
			}
			break;//�ȉ���
		}
		mNextScene = eGameScene_None;    //���̃V�[�������N���A
		mGameScene->Initialize();    //�V�[����������
	}
	mGameScene->Update(); //�V�[���̍X�V
}
void Rpg::Draw() {
	BaseScene::Draw();
	mGameScene->Draw();
}
void Rpg::Draw(vector<string> &tmpfield) {
	BaseScene::Draw(tmpfield);
	mGameScene->Draw(tmpfield);
}
void Rpg::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}

