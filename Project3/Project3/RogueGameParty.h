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
		S_ChoosingAction,
		S_ChoosingTarget,
		S_ChoosingMy,
		S_OtherTurn,
		S_Reading,
		S_Ending,
	};
	struct data {
		bool isenemy;
		string name;
		int fst_hp;
		int fst_level;
	};

	static const vector<data> DATES = {
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
		bool GainLife(const int alife);

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
	protected:
		vector<string> *actionlog;
		Situation *situation;
	private:
		
		int nowfor;//0:こうげき　//2:特殊
		
	};
	class MyChara :public Chara {
	public:
		MyChara(const int aid, vector<string> *aactionlog, Situation *asituation);
		int GainExp(const int aexp);//上がったレベルを返す
		//bool Attack(Chara &atarget);
		int level;
		int next_exp;
	};
	class Party:public Task {
	public:
		Party(const int aleft,const int aup,vector<string> *aactionlog, Situation *asituation);
		virtual void Update(); 
		virtual void Draw();
		bool AddMember(const int aid);
		Chara* GetMember(const int anum);
		//int Act(const Action type);
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
