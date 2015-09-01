#pragma once
#include <windows.h>
#include <iostream>
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gamebaseScene.h"
#include "Text.h"
#include "RogueGame.h"


class Rogue :public gameSceneChanger, BaseScene {
public:
	Rogue::Rogue(SceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。

	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void ChangeScene(eGameScene nextScene)override;
private:
	gameBaseScene* mGameScene;
	eGameScene mNextScene;    //次のシーン管理変数
};
