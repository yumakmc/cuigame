#pragma once
#include "gameBaseScene.h"
#include  "BackGround.h"
#include "Common.h"
#include <map>
#include <vector>
#include <string>
#include <utility>
using namespace std;
namespace  rpggame {
	
	struct Action {
		int dmg;
		int maxwaittime;
	};

	struct CharaInfo {
		string name;
		int hp;
		vector<Action> acts;
		/*CharaInfo(const string aname, const int ahp, const vector<pair<int, int>> &aact, const int abackground) :act(aact) {
			name = aname;
			hp = ahp;

			background = abackground;
		}*/
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
			{ "無限の空", 888,{ { 25,30 },{ 20,20 },{ 2,3 },{ 15,11 } } },
			{ "春", 365,{ { 9,20 },{ 5,14 },{ 3,7 },{ 4,11 },{ 20,33 },{ 18,26 },{ 15,17 },{ 5,10 } } },
		2,10
		},
	};



	class RpgGame :public gameBaseScene {
	public:
		RpgGame(gameSceneChanger* changer, const int aopponent);
		void Initialize() override;
		//void Finalize() override;
		void Update() override;        //更新処理をオーバーライド。
		void Draw() override;            //描画処理をオーバーライド。
	private:
		string inline To_ZenString(const int anum);
		void MakeDamege(const bool playerMake, const int atkNum);

		const int opponent;
		int op_hp;
		const vector<Action> op_act;
		vector<pair<int, int>> op_causeddamages;
		vector<int> op_rest_waittime;
		vector<int> op_delay_waittime;

		int my_hp = 365;
		const vector<Action> my_act;
		vector<pair<int, int>> my_causeddamages;
		vector<int> my_rest_waittime;

		const int DAMAGE_REMAIN_FRAME = 10;

		int paralyzecount = 0;

		BackGround abackground;

		int situation;//0:対戦前 1:help　5:対戦中　10:勝ち　11:負け

		Common::Rand aRand;
		vector<pair<bool, Action>> actionlog;
	};
}