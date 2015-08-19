#pragma once
#include "Game.h"
#include <vector>

//ゲーム画面

Game::Game(SceneChanger* changer) : BaseScene(changer) {
	//mGameScene = new Text(d,this);
}
void Game::Initialize(){
	//mImageHandle = LoadGraph("画像//haikei");
}
void Game::Update(){
	//if (CheckHitKey(KEY_INPUT_ESCAPE) != 0){ //Escキーが押されていたら
	//	mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	//}
	if (mNextScene != eGameScene_None){    //次のシーンがセットされていたら
		mGameScene->Finalize();//現在のシーンの終了処理を実行
		switch (mNextScene){       //シーンによって処理を分岐
		case eGameScene_Text:    //現在の画面がメニューなら
			//mGameScene = (gameBaseScene*) new Text(d,this);
			break;//以下略
		
		}
		mNextScene = eGameScene_None;    //次のシーン情報をクリア
		mGameScene->Initialize();    //シーンを初期化
	}

	mGameScene->Update(); //シーンの更新
}
void Game::Draw(){
	//DrawString(0, 0, "ゲーム画面", GetColor(255, 255, 255));
	BaseScene::Draw();
	mGameScene->Draw();
}

void Game::ChangeScene(eGameScene NextScene){
	mNextScene = NextScene;
}