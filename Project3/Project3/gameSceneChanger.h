#pragma once

enum eGameScene{

	eGameScene_Text,  //�ݒ���
	eGameScene_CardGame,//�J�[�h�Q�[����ʖ{��
	eGameScene_None,    //����
} ;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class gameSceneChanger {
public:
	virtual ~gameSceneChanger() = 0;
	virtual void ChangeScene(eGameScene NextScene) = 0;//�w��V�[���ɕύX����
};