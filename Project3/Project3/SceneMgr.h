#pragma once
#include <iostream>
#include <vector>
#include "Menu.h"
#include "Game.h"
#include "Rpg.h"
#include "Musicroom.h"
#include "Rogue.h"


class SceneMgr :public SceneChanger, Task{
public:
	SceneMgr();
	void Initialize() override;//初期化
	void Finalize() override;//終了処理
	//更新
	void Update();
	
	//描画
	void Draw();
	void Draw(vector<string> &tmpField);
	// 引数 nextScene にシーンを変更する
	void ChangeScene(eScene nextScene)override;

private:
	BaseScene* mScene;    //シーン管理変数
	eScene mNextScene;    //次のシーン管理変数
};
