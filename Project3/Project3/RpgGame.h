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
};