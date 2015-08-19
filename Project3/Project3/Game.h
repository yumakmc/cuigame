#pragma once

#include <windows.h>
#include <iostream>
//#include "Shlwapi.h"
//#pragma comment(lib, "shlwapi.lib")

#include "BaseScene.h"
#include "Tranp.h"
#include "gameSceneChanger.h"
#include "gamebaseScene.h"

class Game:public gameSceneChanger,BaseScene{
public:
	Game::Game(SceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	//void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpfield)override {};
	void ChangeScene(eGameScene nextScene)override;
private:
	//BaseGameScene* mScene;    //シーン管理変数
	gameBaseScene* mGameScene;
	eGameScene mNextScene;    //次のシーン管理変数
};
