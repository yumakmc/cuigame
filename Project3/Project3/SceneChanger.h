#pragma once

typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面
	eScene_Tranp,   //トランプ画面
	eScene_Rpg,     //RPG画面
	eScene_Rogue,   //ローグ画面
	eScene_Musicroom,//音楽室
	eScene_Config,  //設定画面

	eScene_None,    //無し
} eScene;

//シーンを変更するためのインターフェイスクラス
class SceneChanger {
public:
	virtual ~SceneChanger() = 0;
	virtual void ChangeScene(eScene NextScene) = 0;//指定シーンに変更する
};