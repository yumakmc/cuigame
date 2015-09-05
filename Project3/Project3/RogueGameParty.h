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
	enum Action {
		A_Attack,
		A_Defence,
		A_Special,
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
	struct data {
		bool isenemy;
		string name;
		int fst_hp;
		int fst_level;
	};

	static const vector<data> DETAILS = {
		{ false,"春",10,1 },
		{ false,"夏",1000,50 },
		{ false,"秋",100,30 },
		{ false,"冬",100,10 },
		{ true,"嵐",10,1 },
		{ true,"小隕石",1000,50 },
		{ true,"中隕石",100,30 },
		{ true,"大隕石",10,10 },

	};
	class Chara {
	public:
		Chara(const int aid, vector<string> *aactionlog, Situation *asituation);
		bool GetDamage(const int admg);//死んだかを返す
		int GainLife(const int pluslife);
		

		//int Act(const Action type);
		//int SelectAction(const Action type);
		/*virtual bool Attack(Chara &atarget);*/
		//inline int CalculateDmg(const Chara& atarget);
		
		const int id;
		const string name;
		int atk;
		int def;
		int now_hp;
		int max_hp;
		bool isdead;
		bool defending;
		int nexttarget = 0;
		Action nextaction=A_Attack;
		bool controlable = false;
	protected:
		vector<string> *actionlog;
		Situation *situation;
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
		//int Act(const Action type);
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
