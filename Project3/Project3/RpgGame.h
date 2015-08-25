#pragma once
#include "gameBaseScene.h"
#include <map>

struct EnemyInfo {
	string name;
	int hp;
	int atk;
	int interval;//�U���̊Ԋu
	
};

static map<int, EnemyInfo> GETENEMYINFO = {
	{0,{"�H�H�H",365,5,60}},
	{ 1,{"��",500,7,50 }},
	{ 2,{"�����̋�",888,12,70} },
};

class RpgGame :public gameBaseScene {
public:
	RpgGame(gameSceneChanger* changer,const int aopponent);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
private:
	string inline To_ZenString(const int anum);

	const int opponent;
	int op_hp;
	const int op_atk;
	const int op_interval;

	int my_hp=365;

	const int my_atk[4] = { 1,2,3,5 };
	const int max_waittime[4] = { 5,8,11,17 };

	int rest_waittime[4] = { 5,8,11,17 };
	int count;
	int paralyzecount=0;
};