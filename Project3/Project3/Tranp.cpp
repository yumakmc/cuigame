#pragma once
#include "Tranp.h"
#include "Keyboard.h"
#include "TranpGame.h"
#include <assert.h>
#include <vector>

vector<string> d;

extern int flag;//めっちゃ頭悪い

Tranp::Tranp(SceneChanger* changer) : BaseScene(changer) {
	nextenemy = 0;
	d.push_back("考えたんだけどさ………………");
	d.push_back("季節が４つってさ");
	d.push_back("絶対に多過ぎるよね");
	d.push_back("冬は糞寒いし");
	d.push_back("秋は自分と被ってやがるし");
	d.push_back("夏は………ぶち殺してやりたい");
	d.push_back("………よし、やろう");
	mGameScene = new Text(this,0,nextenemy);
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
			if (flag)nextenemy--;
			mGameScene = (gameBaseScene*) new Text( this, 0,nextenemy);
			break;//以下略
		case eGameScene_Main:
			if (nextenemy == 3) {
				mSceneChanger->ChangeScene(eScene_Menu);
			}
			else {
				mGameScene = (gameBaseScene*) new TranpGame(nextenemy, d, this);
				nextenemy++;
			}
			break;//以下略
		}
		mNextScene = eGameScene_None;    //次のシーン情報をクリア
		mGameScene->Initialize();    //シーンを初期化
	}
	mGameScene->Update(); //シーンの更新
}
void Tranp::Draw() {
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

