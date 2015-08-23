#pragma once
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gameBaseScene.h"
#include <vector>
#include <string>
#include <map>
using namespace std;


class TranpGame :public gameBaseScene {
public:
	TranpGame::TranpGame(const int aopponent,vector<string> atexts, gameSceneChanger* changer);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpfield)override;
	int inline GetWinner(const int mycard, const int opcard);//1 自分の勝ち 0　引き分け　-1 相手の勝ち
	string inline To_ZenString(const int anum);
private:
	const int opponent;

	bool mycarduseds[13];
	int  mypoint;
	bool opcarduseds[13];
	int  oppoint;
	const int targetscore;

	int undecidedpoint = 0;

	vector<int> opcardorder;
	vector<int> mycardorder;

	int turn;//開かれたカードセットの数と同義

	int serihunum;

	bool helpmode;
};