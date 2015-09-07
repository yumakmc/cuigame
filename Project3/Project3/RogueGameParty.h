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
		int fst_hp;
		int fst_level;
		Ai fst_ai;
	};

	static const vector<data> DETAILS = {
		{ false,"春",10,1,Ai_Controlabel },
		{ false,"夏",1000,50,Ai_AttackSpring },
		{ false,"秋",100,30,Ai_AttackSummer },
		{ false,"冬",100,10,Ai_AttackEnemy },
		{ true,"嵐",10,1,Ai_AttackMy },
		{ true,"小隕石",1000,50 ,Ai_AttackMy },
		{ true,"中隕石",100,30,Ai_AttackMy },
		{ true,"大隕石",10,10,Ai_AttackMy },

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
	class MyChara :public Chara {
	public:
		MyChara(const int aid, vector<string> *aactionlog, Situation *asituation);
		int GainExp(const int aexp);//上がったレベルを返す
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
		
	protected:
		int LEFT;
		int UP;
		array<Chara*, maxmember> members;
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
		vector<int>GetAliveMemberId();
	private:
		
	};
	class OpParty :public Party {
	public:
		OpParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation);
		void Update()override;
		void Draw()override;

	private:

	};
}
