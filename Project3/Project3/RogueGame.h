#pragma once

#include "gameBaseScene.h"
#include  "BackGround.h"
#include "Common.h"
#include <map>
#include <vector>
#include <string>
#include <utility>
using namespace std;
namespace  roguegame {

	struct Action {
		int dmg;
		int maxwaittime;
	};

	struct CharaInfo {
		string name;
		int hp;
		vector<Action> acts;
	};
	struct OpInfo :CharaInfo {
		int max_delaytime;
	};

	struct MyInfo :CharaInfo {
	};
	struct AllInfo {
		CharaInfo opinfo;
		CharaInfo myinfo;
		int background;
		int maxdelaytime;
	};
	static vector<AllInfo> AllInfos = {
		{
			{ "？", 365,{ { 9,20 },{ 5,14 },{ 3,7 },{ 4,11 } } },
			{ "春", 365,{ { 9,20 },{ 5,14 },{ 3,7 },{ 4,11 } } },
		0,40
		},
		{
			{ "空", 500,{ { 7,15 },{ 4,10 },{ 2,5 },{ 3,6 } } },
			{ "春", 365,{ { 9,20 },{ 5,14 },{ 3,7 },{ 4,11 } } },
		2,20
		},
		{
			{ "無限の空", 777,{ { 15,30 },{ 10,20 },{ 2,3 },{ 8,11 } } },
			{ "春", 366,{ { 9,20 },{ 5,14 },{ 3,7 },{ 4,11 },{ 20,33 },{ 18,26 },{ 15,17 },{ 5,10 } } },
		3,15
		},
	};


	class RogueGame :public gameBaseScene {
	public:
		RogueGame(gameSceneChanger* changer);
		void Initialize() override;
		//void Finalize() override;
		void Update() override;        //更新処理をオーバーライド。
		void Draw() override;            //描画処理をオーバーライド。
	private:
		string inline To_ZenString(const int anum);

		int op_hp;


		int my_hp = 365;




		BackGround abackground;

		int situation;//0:対戦前 1:help　5:対戦中　10:勝ち　11:負け

		Common::Rand aRand;
		vector<pair<bool, Action>> actionlog;
	};
}
