#pragma once

enum eGameScene{

	eGameScene_Text,  //設定画面
	eGameScene_CardGame,//カードゲーム画面本編
	eGameScene_None,    //無し
} ;

//シーンを変更するためのインターフェイスクラス
class gameSceneChanger {
public:
	virtual ~gameSceneChanger() = 0;
	virtual void ChangeScene(eGameScene NextScene) = 0;//指定シーンに変更する
};