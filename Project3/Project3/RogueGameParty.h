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
	struct data {
		bool isenemy;
		string name;
		int fst_hp;
		int fst_level;
	};

	static const vector<data> DATES = {
		{ false,"t",10,1 },
		{ false,"‰Δ",1000,50 },
		{ false,"H",100,30 },
		{ false,"“~",100,10 },
		{ true,"—’",10,1 },
		{ true,"¬θ¦Ξ",1000,50 },
		{ true,"’†θ¦Ξ",100,30 },
		{ true,"‘εθ¦Ξ",10,10 },

	};
	class Chara {
	public:
		Chara(const int aid, vector<string> *aactionlog);
		bool GetDamage(const int admg);//€‚ρ‚Ύ‚©‚π•Τ‚·
		bool GainLife(const int alife);

		int Act(const Action type);
		bool Attack(Chara &atarget) {
			return atarget.GetDamage(CalculateDmg(atarget));
		}
		inline int CalculateDmg(const Chara& atarget) {
			return max(0,atk - atarget.def);
		}
		const int id;
		const string name;
		int atk;
		int def;
		int now_hp;
		int max_hp;
		bool isdead;
	protected:
		vector<string> *actionlog;
		
	};
	class MyChara :public Chara {
	public:
		MyChara(const int aid, vector<string> *aactionlog);
		int GainExp(const int aexp);//γ‚ª‚Α‚½ƒƒxƒ‹‚π•Τ‚·

		int level;
		int next_exp;
	};
	class Party:public Task {
	public:
		Party(const int aleft,const int aup,vector<string> *aactionlog);
		virtual void Update(); 
		virtual void Draw();
		bool AddMember(const int aid);
		int Act(const Action type);
		int nowselect=0;
	protected:
		int LEFT;
		int UP;
		static const int maxmember = 4;
		array<Chara*, maxmember> members;
		vector<string> *actionlog;
	private:
		
	};
	class MyParty:public Party {
	public:
		MyParty(const int aleft, const int aup, vector<string> *aactionlog);
		void Update()override;
		void Draw()override;
		vector<int>GetAliveMemberId();
	private:
		
	};
	class OpParty :public Party {
	public:
		OpParty(const int aleft, const int aup, vector<string> *aactionlog);
		void Update()override;
		void Draw()override;

	private:

	};
}
