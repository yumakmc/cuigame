#pragma once
#include "gameBaseScene.h"

class RpgGame :public gameBaseScene {
public:
	RpgGame(gameSceneChanger* changer,const int aopponent);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
private:
	const int opponent;
	const int op_hp;

	int my_hp=50;

	const int atk[4] = { 1,2,3,5 };
	const int max_waittime[4] = { 5,8,11,17 };

	int rest_waittime[4] = { 5,8,11,17 };
	int count;
	int paralyzecount=0;
};