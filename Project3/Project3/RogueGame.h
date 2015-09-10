#pragma once

#include "gameBaseScene.h"
#include  "BackGround.h"
#include "RogueGameTable.h"
#include "RogueGameParty.h"
#include "Common.h"
#include "BaseSaveManager.h"
#include <map>
#include <vector>
#include <array>
#include <utility>
using namespace std;
namespace  roguegame {
	struct RogueSaveData:public BaseSaveData {
		RogueSaveData(const MyParty& m, const OpParty& o, int d, int s): myparty(m) , opparty(o) {
			
			day = d;
			season = s;
		}
		MyParty myparty;
		OpParty opparty;
		int day;
		int season;
	};
	enum Ending {
		E_Dummy,//初期値
		E_Bad,//春に春死ぬ
		E_True,//夏に春死ぬ
		E_SummerDead,//夏に春死ぬ
		E_Why,//秋に春死ぬ
		E_FallKillSummer,//秋に夏死ぬ
		E_KillMeteorWithAll,//冬に春死ぬ
		E_KillMeteorWithOutAll,//冬に春死ぬ
	};
	/*struct table {
		int next_exp;
		int max_hp;
		int atk;
		int def;
	};
	static vector<array < table, 100 >> TABLES;*/

	class RogueGame :public gameBaseScene {
	public:
		RogueGame(gameSceneChanger* changer);
		void Initialize() override;
		void Update() override;        //更新処理をオーバーライド。
		void Draw() override;            //描画処理をオーバーライド。
		int Attack(Chara *from, Chara *to);
		int Attack(int fromnum, int tonum);
		int Regenerate(Chara *from, Chara *to);
		int Regenerate(const int fromnum, const int tonum);
		int Special(Chara *from, Chara *to);
		int Special(int fromnum, int tonum);
		int Act(Chara *from, Chara *to,const ActionType type);
		int SelectAction(const ActionType type);
		inline int CalculateDmg(const Chara *from, const Chara *to);
		bool ChangeActMember();//全員終了したらfalse返す
		int CheckDeadPlayer();//行動終了時に呼び出す　死亡チェックとかエンディング条件チェックとか
		Chara* GetMember(int num)const ;//上からnum番目のメンバーへのポインタを返す
		Chara* GetMember(const bool isop, const int num)const;

		MyParty myparty;
		OpParty opparty;
	private:

		

		BackGround abackground;

		Situation *situation;

		vector<string> *actionlog;

		int season = 0;
		int day = 0;

		int nowplayernum=4;

		ActionType nowaction;
		Common::Rand rand;
	};
}
