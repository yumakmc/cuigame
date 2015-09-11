#pragma once

#include "gameBaseScene.h"
#include  "BackGround.h"
#include "RogueGameTable.h"
#include "RogueGameParty.h"
#include "Common.h"
#include "BaseSaveManager.h"
#include <map>
#include <vector>
#include <array>
#include <utility>
#include<memory>
using namespace std;
namespace  roguegame {
	struct RogueSaveData :public BaseSaveData {
		RogueSaveData(const MyParty& m, const OpParty& o, int d, int s);
		RogueSaveData();
		~RogueSaveData();
		array<pair<int, MyChara>, 4> mymembers;
		array<pair<int, OpChara>, 4> opmembers;
		int day;
		int season;
	};
	enum Ending {
		E_Dummy,//�����l
		E_Bad,//�t�ɏt����
		E_True,//�Ăɏt����
		E_SummerDead,//�Ăɏt����
		E_Why,//�H�ɏt����
		E_FallKillSummer,//�H�ɉĎ���
		E_KillMeteorWithAll,//覐Γ|���N������łȂ�
		E_KillMeteorWithOutAll,//覐Γ|���N������ł�
	};
	/*struct table {
	int next_exp;
	int max_hp;
	int atk;
	int def;
	};
	static vector<array < table, 100 >> TABLES;*/

	class RogueGame :public gameBaseScene {
	public:
		RogueGame(gameSceneChanger* changer);
		void Initialize() override;
		void Update() override;        //�X�V�������I�[�o�[���C�h�B
		void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
		int Attack(shared_ptr<Chara> from, shared_ptr<Chara> to);
		int Attack(int fromnum, int tonum);
		int Regenerate(shared_ptr<Chara> from, shared_ptr<Chara> to);
		int Regenerate(const int fromnum, const int tonum);
		int Special(shared_ptr<Chara> from, shared_ptr<Chara> to);
		int Special(int fromnum, int tonum);
		int Act(shared_ptr<Chara> from, shared_ptr<Chara> to, const ActionType type);
		int SelectAction(const ActionType type);
		inline int CalculateDmg(const shared_ptr<Chara> from, const shared_ptr<Chara> to);
		bool ChangeActMember();//�S���I��������false�Ԃ�
		int CheckDeadPlayer();//�s���I�����ɌĂяo���@���S�`�F�b�N�Ƃ��G���f�B���O�����`�F�b�N�Ƃ�
		shared_ptr<Chara> GetMember(int num)const;//�ォ��num�Ԗڂ̃����o�[�ւ̃|�C���^��Ԃ�
		shared_ptr<Chara> GetMember(const bool isop, const int num)const;

		MyParty myparty;
		OpParty opparty;
	private:

		int Save();
		int Load();

		BackGround abackground;

		shared_ptr<Situation> situation;

		shared_ptr<vector<string>>actionlog;

		int season = 0;
		int day = 0;

		int nowplayernum = 4;

		ActionType nowaction;
		Common::Rand rand;
	};
}
