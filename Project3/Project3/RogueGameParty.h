#pragma once
#include <string>
#include <vector>
#include <array>
#include "Task.h"
#include "DrawableConsole.h"
#include "Common.h"
#include "RogueGameTable.h"
using namespace std;
using namespace roguegame;
namespace  roguegame {
	class RogueGame;
	
	enum ActionType {
		A_Attack,
		A_Defence,
		A_Special,
		A_Nothing,//�ҋ@
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
		Ai_Controlable,
		Ai_AttackEnemy,
		Ai_AttackMy,
		Ai_Summer,
		Ai_AttackSummer,
		Ai_AttackFall,
		Ai_Meteor,//覐Ηp
		Ai_Moon,//���p
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

		//������p
		Myinfo myinfo;

		//�G��p
		Opinfo opinfo;
	};

	static const vector<data> DETAILS = {
		{ false,"�t"   ,Ai_Controlable ,  30,{ 1},{ 0, 0, 0, 10} },
		{ false,"��"   ,Ai_Summer,1000,{20},{ 0, 0, 0, 10} },
		{ false,"�H"   ,Ai_AttackSummer, 500,{20},{ 0, 0, 0, 10} },
		{ false,"�~"   ,Ai_AttackEnemy , 700,{20},{ 0, 0, 0, 10} },

		{ true,"�~"    ,Ai_AttackMy	   ,  12,{ 0},{ 7, 6, 0,  12 } },//�t�̉�
		{ true,"�"    ,Ai_AttackMy    ,  25,{ 0},{15, 7, 3, 25 } },
		{ true,"��"    ,Ai_AttackMy    ,  30,{ 0},{30, 13, 0, 30 } },
		{ true,"��"	   ,Ai_AttackMy    ,  40,{ 0},{50, 8, 9, 40 } },

		{ true,"��"    ,Ai_AttackMy    ,  50,{ 0},{50, 12, 3, 50} },//�Ẳ�
		{ true,"��"    ,Ai_AttackMy    ,  60,{ 0},{60,15, 1, 60} },
		{ true,"�["    ,Ai_AttackMy    ,  40,{ 0},{100,20,5, 40} },
		{ true,"�@"    ,Ai_AttackMy	   , 100,{ 0},{200,14,17,100} },

		{ true,"��"    ,Ai_AttackMy    ,  30,{ 0 },{ 100, 15,15, 30 } },//�H�̉�
		{ true,"�e"    ,Ai_AttackMy    ,  10,{ 0 },{ 150,17, 20, 10 } },
		{ true,"��"    ,Ai_AttackMy    ,  50,{ 0 },{ 200,15,17, 50 } },
		{ true,"�k"    ,Ai_AttackMy	   ,  100,{ 0 },{300,19,0,100 } },

		{ true,"�A"    ,Ai_AttackMy    ,  60,{ 0 },{ 300, 20, 5, 60 } },//�~�̉�
		{ true,"��"    ,Ai_AttackMy    ,  70,{ 0 },{ 10,20, 5, 70 } },

		{ true,"��"    ,Ai_AttackMy    ,  60,{ 0 },{ 500, 50, 5, 60 } },//覐�
		{ true,"��"    ,Ai_AttackMy    , 100,{ 0 },{ 1000,100,10, 100 } },
		{ true,"��"    ,Ai_AttackMy    , 300,{ 0 },{ 2000,300,15, 300 } },
		{ true,"�l"    ,Ai_AttackMy	   ,1000,{ 0 },{ 9999,9999,5,1000 } },

		{ true,"��"    ,Ai_AttackMy	   , 10,{ 0 },{ 1,1,9999,10 } },//��

		{ false,"�~"   ,Ai_AttackEnemy , 0,{ 40 },{ 0, 0, 0, 10 } },

	};
	struct ActionInfo {
		int targetnum;
		ActionType type;
	};
	class Chara {
	public:
		Chara(const int aid, vector<string> *aactionlog, Situation *asituation);
		bool GetDamage(const int admg);//���񂾂���Ԃ�
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
		Ai ai;
		ActionInfo DecideNextAction(const RogueGame& roguegame);

		//�֗��J�E���^
		int count = 0;
	protected:
		vector<string> *actionlog;
		Situation *situation;
		//���x���A�b�v�ɕK�v�Ȍo���l�Ƃ����x���ɂ��U���͂Ƃ�
		
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
		int GainExp(const int aexp);//�オ�������x����Ԃ�
		
		//bool Attack(Chara &atarget);
		int level;
		int next_exp;
		bool LevelUp();
	private:
		array<TableInfo, MaxLevel> infos;
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
