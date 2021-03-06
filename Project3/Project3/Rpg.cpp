#include "Rpg.h"
#include "Keyboard.h"

#include "Music.h"

extern bool RpgKillFrag;//RpgGameよりextern

Rpg::Rpg(SceneChanger* changer) : BaseScene(changer) {
	nextenemy = 0;
	mGameScene = new Text(this,1, nextenemy);
	
}
void Rpg::Initialize() {
}
void Rpg::Update() {
	if (Keyboard_Get(VK_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (mNextScene != eGameScene_None) {    //次のシーンがセットされていたら
		mGameScene->Finalize();//現在のシーンの終了処理を実行
		switch (mNextScene) {       //シーンによって処理を分岐
		case eGameScene_Text:    //現在の画面がメニューなら
			if (RpgKillFrag) {
				nextenemy++;
				RpgKillFrag = false;
			}
			mGameScene = (gameBaseScene*) new Text(this,1, nextenemy);
			break;//以下略
		case eGameScene_Main:
			
			if (nextenemy == 3) {
				mSceneChanger->ChangeScene(eScene_Menu);
			}
			else {
				mGameScene = (gameBaseScene*) new rpggame::RpgGame(this,nextenemy);
			}
			break;//以下略
		}
		mNextScene = eGameScene_None;    //次のシーン情報をクリア
		mGameScene->Initialize();    //シーンを初期化
	}
	mGameScene->Update(); //シーンの更新
}
void Rpg::Draw() {
	BaseScene::Draw();
	mGameScene->Draw();
}
void Rpg::Draw(vector<string> &tmpfield) {
	BaseScene::Draw(tmpfield);
	mGameScene->Draw(tmpfield);
}
void Rpg::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}

