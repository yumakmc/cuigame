#pragma once
#include "Tranp.h"
#include "Keyboard.h"
#include "TranpGame.h"
#include <assert.h>
#include <vector>

vector<string> d;

Tranp::Tranp(SceneChanger* changer) : BaseScene(changer) {
	d.push_back("考えたんだけどさ………………");
	d.push_back("季節が４つってさ");
	d.push_back("絶対に多過ぎるよね");
	d.push_back("夏は糞暑いし冬は糞寒いし");
	d.push_back("秋は………被ってやがるし");
	d.push_back("………よし、やろう");
	mGameScene = new Text(d,this);
}
void Tranp::Initialize() {
}
void Tranp::Update() {
	if (Keyboard_Get(VK_ESCAPE) != 0){ //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (mNextScene != eGameScene_None) {    //次のシーンがセットされていたら
		mGameScene->Finalize();//現在のシーンの終了処理を実行
		switch (mNextScene) {       //シーンによって処理を分岐
		case eGameScene_Text:    //現在の画面がメニューなら
			mGameScene = (gameBaseScene*) new Text(d, this);
			break;//以下略
		case eGameScene_CardGame:    //現在の画面がメニューなら
			mGameScene = (gameBaseScene*) new TranpGame(0,d, this);
			break;//以下略
		}
		mNextScene = eGameScene_None;    //次のシーン情報をクリア
		mGameScene->Initialize();    //シーンを初期化
	}
	mGameScene->Update(); //シーンの更新
}
void Tranp::Draw() {
	assert(false);
	BaseScene::Draw();
	mGameScene->Draw();
}
void Tranp::Draw(vector<string> &tmpfield) {
	BaseScene::Draw(tmpfield);
	mGameScene->Draw(tmpfield);
}
void Tranp::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}

