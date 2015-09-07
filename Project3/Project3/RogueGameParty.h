#pragma once
#include <string>
#include <vector>
#include <array>
#include "Task.h"
#include "RogueGameTable.h"

#include "DrawableConsole.h"
#include "Common.h"
using namespace std;
using namespace roguegame;
namespace  roguegame {
	
	enum ActionType {
		A_Attack,
		A_Defence,
		A_Special,
		A_Nothing,//待機
	};
	enum Situation {
		S_Opening,
		S_Help,
		S_TurnStart,
		S_ChoosingAction,
		S_ChoosingTarget,
		S_AllyTurn,
		S_EnemyTurn,
		S_TurnEnd,
		S_Reading,
		S_Ending,
	};
	enum Ai {
		Ai_Controlabel,
		Ai_AttackEnemy,
		Ai_AttackMy,
		Ai_AttackSpring,
		Ai_AttackSummer,
		Ai_AttackFall,
	};
	struct data {
		bool isenemy;
		string name;
		Ai fst_ai;
		int fst_hp;

		//味方専用
		int fst_level;
		int fst_exp;

		//敵専用
		int exp;
		int atk;
		int def;
		int max_hp;
	};

	static const vector<data> DETAILS = {
		{ false,"春"   ,Ai_Controlabel ,10  ,5 ,0,0,0,0,10 },
		{ false,"夏"   ,Ai_AttackSpring,1000,50,0,0,0,0,10 },
		{ false,"秋"   ,Ai_AttackSummer,100 ,30,0,0,0,0,10 },
		{ false,"冬"   ,Ai_AttackEnemy ,100 ,10,0,0,0,0,10 },
		{ true,"嵐"    ,Ai_AttackMy	  ,10  ,1 ,5,5,5,3,10 },
		{ true,"小隕石",Ai_AttackMy    ,1000,50,10,10,6,5,20 },
		{ true,"中隕石",Ai_AttackMy    ,100 ,30,20,20,7,8,30 },
		{ true,"大隕石",Ai_AttackMy    ,10  ,10,50,30,10,10,50 },

	};
	struct ActionInfo {
		int targetnum;
		ActionType type;
	};
	class Chara {
	public:
		Chara(const int aid, vector<string> *aactionlog, Situation *asituation);
		bool GetDamage(const int admg);//死んだかを返す
		int GainLife(const int pluslife);


		const int id;
		const string name;
		int atk;
		int def;
		int now_hp;
		int max_hp;
		bool isdead;
		bool defending;
		ActionInfo nextActionInfo = {
			-1,A_Attack
		};
		bool controlable = false;
		Ai ai;
	protected:
		vector<string> *actionlog;
		Situation *situation;
		//レベルアップに必要な経験値とかレベルによる攻撃力とか
		array<TableInfo,MaxLevel> infos;
	private:
	};
	class OpChara :public Chara {
	public:
		OpChara(const int aid, vector<string> *aactionlog, Situation *asituation);
		int exp;

	};
	class MyChara :public Chara {
	public:
		MyChara(const int aid, vector<string> *aactionlog, Situation *asituation);
		int GainExp(const int aexp);//上がったレベルを返す
		bool LevelUp();
		//bool Attack(Chara &atarget);
		int level;
		int next_exp;
		int ai=0;
		
	};
	class Party:public Task {
	public:
		Party(const int aleft,const int aup,vector<string> *aactionlog, Situation *asituation);
		virtual void Update(); 
		virtual void Draw();
		bool AddMember(const int aid);
		Chara* GetMember(const int anum);
		void DeleteMember(const int anum);
		//int Act(const ActionType type);
		int nowselect=0;
		static const int maxmember = 4;
		array<Chara*, maxmember> members;
	protected:
		int LEFT;
		int UP;
		
		vector<string> *actionlog;
		Situation *situation;
	private:
		
		int nowchara;
	};
	class MyParty:public Party {
	public:
		MyParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation);
		void Update()override;
		void Draw()override;
		bool AddMember(const int aid);
		vector<int>GetAliveMemberId();
		int GainExp(const int exp);
	private:
		
	};
	class OpParty :public Party {
	public:
		OpParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation);
		void Update()override;
		void Draw()override;
		bool AddMember(const int aid);

	private:

	};
}
