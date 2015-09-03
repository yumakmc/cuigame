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
		Chara(const int aid);
		bool GetDamage(const int admg);//€‚ρ‚Ύ‚©‚π•Τ‚·
		bool GainLife(const int alife);
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
		
	};
	class MyChara :public Chara {
	public:
		MyChara(const int aid);
		int GainExp(const int aexp);//γ‚ª‚Α‚½ƒƒxƒ‹‚π•Τ‚·

		int level;
		int next_exp;
	};
	class Party:public Task {
	public:
		Party(const int aleft,const int aup);
		virtual void Update(); 
		virtual void Draw();
		bool AddMember(const int aid);
	protected:
		int LEFT;
		int UP;
		static const int maxmember = 4;
		array<Chara*, maxmember> members;
		
	private:
		
	};
	class MyParty:public Party {
	public:
		MyParty(const int aleft, const int aup);
		void Update()override;
		void Draw()override;
		vector<int>GetAliveMemberId();
	private:
		
	};
	class OpParty :public Party {
	public:
		OpParty(const int aleft, const int aup);
		void Update()override;
		void Draw()override;

	private:

	};
}
