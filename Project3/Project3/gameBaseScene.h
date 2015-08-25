#pragma once
#include "gameSceneChanger.h"
#include "Task.h"
#include <vector>
#include <string>
#include <map>
using namespace std;



class gameBaseScene :public Task{
public:
	gameBaseScene(gameSceneChanger* changer);
	
	virtual ~gameBaseScene(){};
	virtual void Initialize() override {}   //初期化処理をオーバーライド。
	virtual void Finalize() override;
	virtual void Update() override {}        //更新処理をオーバーライド。
	virtual void Draw() override;            //描画処理をオーバーライド
	virtual void Draw(vector<string> &tmpfield);
protected:
	int mImageHandle;                //画像ハンドル格納用変数
	gameSceneChanger* mgameSceneChanger;    //クラス所有元にシーン切り替えを伝えるインターフェイス
};