#pragma once
#include <string>
#include <vector>
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
		{ false,"春",10,0 },
		{ false,"夏",1000,50 },
		{ false,"秋",100,30 },
		{ false,"冬",100,10 },
		{ true,"嵐",10,0 },
		{ true,"小隕石",1000,50 },
		{ true,"中隕石",100,30 },
		{ true,"大隕石",100,10 },

	};
	class Chara {
	public:
		Chara(const int aid);
		int GetDamage(const int admg);//死んだかを返す
		const int id;
		const string name;
		int atk;
		int def;

	protected:
		int now_hp;
		int max_hp;
	};
	class MyChara :public Chara {
	public:
		MyChara(const int aid);
		int GetExp(const int aexp);//上がったレベルを返す
	private:
		int level;
		int exp;
	};
	class Party:public Task {
	public:
		Party();
		virtual void Update(); 
		virtual void Draw();
		bool AddMember(const int aid);
	protected:
		int LEFT;
		int UP;
	private:
		vector<Chara> members ;
		static const int maxmember = 4;
	};
	class MyParty:public Party {
	public:
		MyParty();
	private:
		
	};
	class OpParty :public Party {
	public:
		OpParty();
	private:

	};
}
