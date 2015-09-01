#include "Rogue.h"
#include "Keyboard.h"

#include "Music.h"



Rogue::Rogue(SceneChanger* changer) : BaseScene(changer) {
	mGameScene = new Text(this, 1, 0);

}
void Rogue::Initialize() {
}
void Rogue::Update() {
	if (Keyboard_Get(VK_ESCAPE) != 0) { //Escキーが押されていたら
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (mNextScene != eGameScene_None) {    //次のシーンがセットされていたら
		mGameScene->Finalize();//現在のシーンの終了処理を実行
		switch (mNextScene) {       //シーンによって処理を分岐
		case eGameScene_Text:    //現在の画面がメニューなら

			mGameScene = (gameBaseScene*) new Text(this, 1, 0);
			break;//以下略
		case eGameScene_Main:

			mGameScene = (gameBaseScene*) new roguegame::RogueGame(this);
			
			break;//以下略
		}
		mNextScene = eGameScene_None;    //次のシーン情報をクリア
		mGameScene->Initialize();    //シーンを初期化
	}
	mGameScene->Update(); //シーンの更新
}
void Rogue::Draw() {
	BaseScene::Draw();
	mGameScene->Draw();
}

void Rogue::ChangeScene(eGameScene NextScene) {
	mNextScene = NextScene;
}
