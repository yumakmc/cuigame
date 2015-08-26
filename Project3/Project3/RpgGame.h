#pragma once
#include "gameBaseScene.h"
#include <map>

struct EnemyInfo {
	string name;
	int hp;
	int atk;
	int interval;//攻撃の間隔
	int background;//背景
};

static map<int, EnemyInfo> GETENEMYINFO = {
	{0,{"？",365,5,20,0}},
	{ 1,{"空",500,7,18,1 }},
	{ 2,{"無限の空",888,12,15,2} },
};

class RpgGame :public gameBaseScene {
public:
	RpgGame(gameSceneChanger* changer,const int aopponent);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
private:
	string inline To_ZenString(const int anum);

	const int opponent;
	int op_hp;
	const int op_atk;
	const int op_interval;
	vector<pair<int, int>> op_damages;

	int my_hp=365;
	vector<pair<int, int>> my_damages;

	const int DAMAGE_REMAIN_FRAME = 10;

	const int my_atk[4] = { 1,2,3,5 };
	const int MY_MAX_WAITTIME[4] = { 5,8,11,17 };

	int my_rest_waittime[4] = { 5,8,11,17 };
	int count;
	int paralyzecount=0;

	int op_rest_waittime;

	


	int situation;//0:対戦前　5:対戦中　10:対戦後
};