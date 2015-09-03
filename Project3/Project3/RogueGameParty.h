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
		Chara(const int aid, vector<string> *aactionlog);
		bool GetDamage(const int admg);//死んだかを返す
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
		int GainExp(const int aexp);//上がったレベルを返す

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
