#pragma once
#include "SceneMgr.h"

SceneMgr::SceneMgr() :
	mNextScene(eScene_None) //次のシーン管理変数
{
	mScene = (BaseScene*) new Menu(this);
}
void SceneMgr::Initialize(){
	mScene->Initialize();
}
void SceneMgr::Finalize(){
	mScene->Finalize();
}
//更新
void SceneMgr::Update(){
	if (mNextScene != eScene_None){    //次のシーンがセットされていたら
		mScene->Finalize();//現在のシーンの終了処理を実行
		switch (mNextScene){       //シーンによって処理を分岐
		case eScene_Menu:    //現在の画面がメニューなら
			mScene = (BaseScene*) new Menu(this);
			break;//以下略
		case eScene_Game:
			mScene = (BaseScene*) new Game(this);
			break;
		case eScene_Tranp:
			mScene = (BaseScene*) new Tranp(this);
			break;
		}
		mNextScene = eScene_None;    //次のシーン情報をクリア
		mScene->Initialize();    //シーンを初期化
	}
	mScene->Update(); //シーンの更新
}

//描画
void SceneMgr:: Draw(){
	mScene->Draw();

}
void SceneMgr::Draw(vector<string> &tmpField) {
	mScene->Draw(tmpField);
}
// 引数 nextScene にシーンを変更する
void SceneMgr::ChangeScene(eScene NextScene){
	mNextScene = NextScene;
}