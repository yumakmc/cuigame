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
		Chara(const int aid);
		bool GetDamage(const int admg);//死んだかを返す
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
		int GainExp(const int aexp);//上がったレベルを返す

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
