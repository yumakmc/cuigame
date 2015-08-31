#pragma once
#include "FallingObject.h"
#include  "Data_Rand.h"
#include "ConsoleBuffer.h"
#include <vector>
using namespace std;

class FallingObjectCollection:public Task {
public:
	FallingObjectCollection(int atype, const bool havecolor);
	FallingObjectCollection(const bool havecolor=false);
	~FallingObjectCollection();
	void Initialize() override;    //初期化処理をオーバーライド。
								   //void Finalize() override ;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpfield);
private:
	vector<FallingObject> FallingObjects;
	int count;

	const bool color;
	const int type;

};