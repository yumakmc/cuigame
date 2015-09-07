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
	class RogueGame;
	
	enum ActionType {
		A_Attack,
		A_Defence,
		A_Special,
		A_Nothing,//‘Ò‹@
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
	struct Myinfo {
		int fst_level;
	};
	struct Opinfo {
		int exp;
		int atk;
		int def;
		int max_hp;
	};
	struct data {
		bool isenemy;
		string name;
		Ai fst_ai;
		int fst_hp;

		//–¡•ûê—p
		Myinfo myinfo;

		//“Gê—p
		Opinfo opinfo;
	};

	static const vector<data> DETAILS = {
		{ false,"t"   ,Ai_Controlabel ,  30,{ 1},{ 0, 0, 0, 10} },
		{ false,"‰Ä"   ,Ai_AttackSpring,1000,{50},{ 0, 0, 0, 10} },
		{ false,"H"   ,Ai_AttackSummer, 500,{30},{ 0, 0, 0, 10} },
		{ false,"“~"   ,Ai_AttackEnemy , 700,{40},{ 0, 0, 0, 10} },

		{ true,"”~"    ,Ai_AttackMy	   ,  15,{ 0},{ 7, 6, 0,  15 } },//t‚Ì‰Ô
		{ true,"ä¿"    ,Ai_AttackMy    ,  25,{ 0},{10, 7, 3, 25 } },
		{ true,"’Ö"    ,Ai_AttackMy    ,  90,{ 0},{70, 13, 0, 90 } },
		{ true,"÷"	   ,Ai_AttackMy    ,  50,{ 0},{100, 9, 9, 50 } },

		{ true,"—¨"    ,Ai_AttackMy    ,  60,{ 0},{20, 9, 9, 60} },//‰Ä‚Ì‰Ô
		{ true,"ˆ¨"    ,Ai_AttackMy    ,  70,{ 0},{10,20, 5, 70} },
		{ true,"å["    ,Ai_AttackMy    ,  80,{ 0},{30,15,30, 80} },
		{ true,"˜@"    ,Ai_AttackMy	   , 100,{ 0},{ 5,14,17,100} },

		{ true,"—–"    ,Ai_AttackMy    ,  60,{ 0 },{ 20, 9, 9, 60 } },//H‚Ì‰Ô
		{ true,"‹e"    ,Ai_AttackMy    ,  70,{ 0 },{ 10,20, 5, 70 } },
		{ true,"”‹"    ,Ai_AttackMy    ,  80,{ 0 },{ 30,15,30, 80 } },
		{ true,"‹k"    ,Ai_AttackMy	   , 100,{ 0 },{ 5,14,17,100 } },

		{ true,"•A"    ,Ai_AttackMy    ,  60,{ 0 },{ 20, 9, 9, 60 } },//“~‚Ì‰Ô
		{ true,"•“"    ,Ai_AttackMy    ,  70,{ 0 },{ 10,20, 5, 70 } },

		{ true,"¬"    ,Ai_AttackMy    ,  60,{ 0 },{ 20, 9, 9, 60 } },//è¦Î
		{ true,"’†"    ,Ai_AttackMy    ,  70,{ 0 },{ 10,20, 5, 70 } },
		{ true,"‘å"    ,Ai_AttackMy    ,  80,{ 0 },{ 30,15,30, 80 } },
		{ true,"‚l"    ,Ai_AttackMy	   , 100,{ 0 },{ 5,14,17,100 } },

		{ true,"Œ"    ,Ai_AttackMy	   , 100,{ 0 },{ 5,14,17,100 } },//Œ

	};
	struct ActionInfo {
		int targetnum;
		ActionType type;
	};
	class Chara {
	public:
		Chara(const int aid, vector<string> *aactionlog, Situation *asituation);
		bool GetDamage(const int admg);//€‚ñ‚¾‚©‚ğ•Ô‚·
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
		ActionInfo DecideNextAction(const RogueGame& roguegame);
	protected:
		vector<string> *actionlog;
		Situation *situation;
		//ƒŒƒxƒ‹ƒAƒbƒv‚É•K—v‚ÈŒoŒ±’l‚Æ‚©ƒŒƒxƒ‹‚É‚æ‚éUŒ‚—Í‚Æ‚©
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
		int GainExp(const int aexp);//ã‚ª‚Á‚½ƒŒƒxƒ‹‚ğ•Ô‚·
		
		//bool Attack(Chara &atarget);
		int level;
		int next_exp;
		int ai;
	private:
		bool LevelUp();
	};
	class Party:public Task {
	public:
		Party(const int aleft,const int aup,vector<string> *aactionlog, Situation *asituation);
		virtual void Update();
		virtual void Draw();
		bool AddMember(const int aid, const RogueGame &roguegame);
		Chara* GetMember(const int anum)const;
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
		bool AddMember(const int aid, const RogueGame &roguegame);
		vector<int>GetAliveMemberId();
		int GainExp(const int exp);
	private:
		
	};
	class OpParty :public Party {
	public:
		OpParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation);
		void Update()override;
		void Draw()override;
		bool AddMember(const int aid, const RogueGame &roguegame);

	private:

	};
}
