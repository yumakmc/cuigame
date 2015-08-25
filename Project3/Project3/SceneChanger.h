#pragma once

typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����
	eScene_Tranp,   //�g�����v���
	eScene_Rpg,     //RPG���
	eScene_Config,  //�ݒ���

	eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class SceneChanger {
public:
	virtual ~SceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//�w��V�[���ɕύX����
};