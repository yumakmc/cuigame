#pragma once
#include "SceneChanger.h"
#include "Task.h"
#include <vector>
#include <string>
using namespace std;
class BaseScene:public Task{
public:
	BaseScene(SceneChanger* changer);
	virtual ~BaseScene(){};
	virtual void Initialize() override {}   //初期化処理をオーバーライド。
	virtual void Finalize() override;
	virtual void Update() override {}        //更新処理をオーバーライド。
	virtual void Draw() override;            //描画処理をオーバーライド
	virtual void Draw(vector<string> &tmpfield);
protected:
	int mImageHandle;                //画像ハンドル格納用変数
	SceneChanger* mSceneChanger;    //クラス所有元にシーン切り替えを伝えるインターフェイス
};

