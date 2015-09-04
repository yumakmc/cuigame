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
		{ false,"�t",10,1 },
		{ false,"��",1000,50 },
		{ false,"�H",100,30 },
		{ false,"�~",100,10 },
		{ true,"��",10,1 },
		{ true,"��覐�",1000,50 },
		{ true,"��覐�",100,30 },
		{ true,"��覐�",10,10 },

	};
	class Chara {
	public:
		Chara(const int aid, vector<string> *aactionlog, Situation *asituation);
		bool GetDamage(const int admg);//���񂾂���Ԃ�
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
	protected:
		vector<string> *actionlog;
		Situation *situation;
	private:

	};
	class MyChara :public Chara {
	public:
		MyChara(const int aid, vector<string> *aactionlog, Situation *asituation);
		int GainExp(const int aexp);//�オ�������x����Ԃ�
		//bool Attack(Chara &atarget);
		int level;
		int next_exp;
		int ai=0;
		bool controlable = false;
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
