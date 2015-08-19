#pragma once
#include "FallingObject.h"
#include  "Data_Rand.h"
#include <vector>
using namespace std;

class FallingObjectCollection:public Task {
public:
	FallingObjectCollection();
	~FallingObjectCollection();
	void Initialize() override;    //初期化処理をオーバーライド。
								   //void Finalize() override ;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpfield);
private:
	vector<FallingObject> FallingObjects;
	int count;

};