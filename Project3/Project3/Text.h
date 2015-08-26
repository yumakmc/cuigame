#pragma once 
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gameBaseScene.h"
#include "BackGround.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Text_Detail {//�e�L�X�g��s��
	string text;
	int color;
	int speed;//����鑬�x
};
struct Text_Set {//�e�L�X�g���s���@����ɃA�N�V�����₵��ׂ�l�̏�񂪉����
	string name;
	int background;
	vector<Text_Detail> text_details;
};


class Text:public gameBaseScene{
public:
	//Text::Text(gameSceneChanger* changer);

	Text::Text( gameSceneChanger* changer,const int story,const int enemy);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpfield)override;

private:
	BackGround abackground;

	vector<Text_Set>texts;

	int nowline;
	int nowtext;

	static const int TEXTNUM = 3;//�����ɕ\�������e�L�X�g�̍s
	static const int NAMEUP = 19;
	static const int NAMELEFT = 2;

	int count;
};