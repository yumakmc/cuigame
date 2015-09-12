
#pragma once
#include <string>
#include <vector>
#include <array>
#include <memory>
#include "Task.h"
#include "DrawableConsole.h"
#include "Common.h"
#include "RogueGameTable.h"
using namespace std;
using namespace roguegame;
namespace  roguegame {
	class RogueGame;
	struct RogueSaveData;

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
		S_Save,
		S_Load,
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
		{ false,"�t"   ,Ai_Controlable ,  30,{ 1 },{ 0, 0, 0, 10 } },
		{ false,"��"   ,Ai_Summer,500,{ 20 },{ 0, 0, 0, 10 } },
		{ false,"�H"   ,Ai_AttackSummer, 250,{ 20 },{ 0, 0, 0, 10 } },
		{ false,"�~"   ,Ai_AttackEnemy , 700,{ 40 },{ 0, 0, 0, 10 } },

		{ true,"�~"    ,Ai_AttackMy	   ,  12,{ 0 },{ 7, 6, 0,  12 } },//�t�̉�
		{ true,"�"    ,Ai_AttackMy    ,  25,{ 0 },{ 15, 7, 3, 25 } },
		{ true,"��"    ,Ai_AttackMy    ,  30,{ 0 },{ 30, 13, 0, 30 } },
		{ true,"��"	   ,Ai_AttackMy    ,  40,{ 0 },{ 50, 8, 9, 40 } },

		{ true,"��"    ,Ai_AttackMy    ,  50,{ 0 },{ 50, 12, 3, 50 } },//�Ẳ�
		{ true,"��"    ,Ai_AttackMy    ,  60,{ 0 },{ 60,15, 1, 60 } },
		{ true,"�["    ,Ai_AttackMy    ,  40,{ 0 },{ 100,20,5, 40 } },
		{ true,"�@"    ,Ai_AttackMy	   , 100,{ 0 },{ 200,14,17,100 } },

		{ true,"��"    ,Ai_AttackMy    ,  30,{ 0 },{ 300, 15,6, 30 } },//�H�̉�
		{ true,"�e"    ,Ai_AttackMy    ,  10,{ 0 },{ 500,17, 20, 10 } },
		{ true,"��"    ,Ai_AttackMy    ,  50,{ 0 },{ 700,10,10, 50 } },
		{ true,"�k"    ,Ai_AttackMy	   ,  100,{ 0 },{1000,19,0,100 } },

		{ true,"�A"    ,Ai_AttackMy    ,  60,{ 0 },{ 300, 20, 5, 60 } },//�~�̉�
		{ true,"��"    ,Ai_AttackMy    ,  70,{ 0 },{ 10,20, 5, 70 } },

		{ true,"��"    ,Ai_Meteor    ,  10,{ 0 },{ 500, 10, 10, 10 } },//覐�
		{ true,"��"    ,Ai_Meteor    , 100,{ 0 },{ 1000,100,10, 100 } },
		{ true,"��"    ,Ai_Meteor    , 300,{ 0 },{ 2000,1000,15, 300 } },
		{ true,"�l"    ,Ai_Meteor	   ,1000,{ 0 },{ 9999,9999,0,1000 } },

		{ true,"��"    ,Ai_AttackMy	   , 10,{ 0 },{ 1,1,9999,10 } },//��

		{ false,"�~"   ,Ai_AttackEnemy , 0,{ 40 },{ 0, 0, 0, 10 } },

	};
	struct ActionInfo {
		int targetnum;
		ActionType type;
	};
	class Chara {
	public:
		Chara(const int aid, shared_ptr<vector<string>> aactionlog, shared_ptr<Situation>asituation);

		Chara() {

		}
		~Chara() {

		}

		bool GetDamage(const int admg);//���񂾂���Ԃ�
		int GainLife(const int pluslife);

		int id;
		string name;
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
		shared_ptr<vector<string>> actionlog;
		shared_ptr<Situation> situation;
	protected:

		bool Load(const Chara &c);
	protected:

		//���x���A�b�v�ɕK�v�Ȍo���l�Ƃ����x���ɂ��U���͂Ƃ�

	private:
	};
	class OpChara :public Chara {
	public:
		OpChara(const int aid, shared_ptr<vector<string>> aactionlog, shared_ptr<Situation>asituation);

		OpChara() {

		}
		bool Load(const OpChara &c);
		int exp;

	};

	class MyChara :public Chara {
	public:

		MyChara(const int aid, shared_ptr<vector<string>> aactionlog, shared_ptr<Situation>asituation);

		MyChara() {

		}

		int GainExp(const int aexp);//�オ�������x����Ԃ�

									//bool Attack(Chara &atarget);
		int level;
		int next_exp;
		bool LevelUp();
		bool Load(const MyChara &c);
		/*bool operator =(const MyChara &m) {


		}*/
	private:
		array<TableInfo, MaxLevel> infos;
	};
	class Party :public Task {
	public:
		Party(const int aleft, const int aup, shared_ptr<vector<string>> aactionlog, shared_ptr<Situation>asituation);
		Party(const Party &aparty);
		virtual void Update();
		virtual void Draw();
		bool AddMember(const int aid, const RogueGame &roguegame);
		bool AddMember(const int aid, const int place, const RogueGame &roguegame);
		shared_ptr<Chara> GetMember(const int anum)const;
		void DeleteMember(const int anum);
		//int Act(const ActionType type);
		int nowselect = 0;
		static const int maxmember = 4;
		array<shared_ptr<Chara>, maxmember> members;
	protected:
		int LEFT;
		int UP;

		shared_ptr<vector<string>> actionlog;
		shared_ptr<Situation> situation;
	private:

		int nowchara;
	};
	class MyParty :public Party {
	public:
		MyParty(const int aleft, const int aup, shared_ptr<vector<string>> aactionlog, shared_ptr<Situation>asituation);
		MyParty(const MyParty &amyparty);
		void Update()override;
		void Draw()override;
		bool AddMember(const int aid, const RogueGame &roguegame);
		bool AddMember(const int aid, const int place, const RogueGame &roguegame);
		vector<int>GetAliveMemberId();
		int GainExp(const int exp);
		bool Load(const RogueSaveData& data);
	private:

	};
	class OpParty :public Party {
	public:
		OpParty(const int aleft, const int aup, shared_ptr<vector<string>> aactionlog, shared_ptr<Situation>asituation);
		OpParty(const OpParty &aopparty);
		void Update()override;
		void Draw()override;
		bool AddMember(const int aid, const RogueGame &roguegame);
		bool AddMember(const int aid, const int place, const RogueGame &roguegame);
		bool Load(const RogueSaveData& data);
	private:

	};
}


