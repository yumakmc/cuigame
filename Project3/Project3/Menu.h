#pragma once
#include <windows.h>
#include <iostream>
#include <map>
#include "FallingObjectCollection.h"
#include "BaseScene.h"

enum eMenu{
	eMenu_Game,        //ゲーム
	eMenu_Tranp,    //トランプ
	eMenu_Rpg,//Ｒｐｇ
	eMenu_Musicroom,//ＭＵＳＩＣＲＯＯＭ
	eMenu_Finish,//終了
	eMenu_count//ここで要素数がわかる
};
class Menu:public BaseScene{
public:
	Menu(SceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	//void Finalize() override ;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpField) override;
private:
	eMenu NowSelect;
	FallingObjectCollection afoc;
};