#pragma once
#include "Tranp.h"
#include "Keyboard.h"
#include <vector>

//ゲーム画面

Tranp::Tranp(SceneChanger* changer) : BaseScene(changer) {
	//mGameScene = new Text(d,this);
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
								 //mGameScene = (gameBaseScene*) new Text(d,this);
			break;//以下略
		}
		mNextScene = eGameScene_None;    //次のシーン情報をクリア
		mGameScene->Initialize();    //シーンを初期化
	}
	mGameScene->Update(); //シーンの更新
}
void Tranp::Draw() {
	//DrawString(0, 0, "ゲーム画面", GetColor(255, 255, 255));
	BaseScene::Draw();
	mGameScene->Draw();
}
void Tranp::Draw(vector<string> &tmpfield) {
	//DrawString(0, 0, "ゲーム画面", GetColor(255, 255, 255));
	BaseScene::Draw();
	mGameScene->Draw();
}
void Tranp::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}

