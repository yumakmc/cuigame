#pragma once

#include "gameBaseScene.h"
#include  "BackGround.h"
#include "RogueGameTable.h"
#include "RogueGameParty.h"
#include "Common.h"
#include <map>
#include <vector>
#include <array>
#include <string>
#include <utility>
using namespace std;
namespace  roguegame {
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
		bool Attack(Chara *from, Chara *to);
		bool Attack(int fromnum, int tonum);
		int Regenerate(Chara *from, Chara *to);
		int Regenerate(const int fromnum, const int tonum);
		bool Special(Chara *from, Chara *to);
		bool Special(int fromnum, int tonum);
		int Act(Chara *from, Chara *to,const Action type);
		int SelectAction(const Action type);
		inline int CalculateDmg(const Chara *from, const Chara *to);
		bool ChooseNextPlayer();//�S���I��������false�Ԃ�
		int CheckDeadPlayer();//�s���I�����ɌĂяo���@���S�`�F�b�N�Ƃ��G���f�B���O�����`�F�b�N�Ƃ�
	private:

		MyParty myparty;
		OpParty opparty;

		BackGround abackground;

		Situation *situation;

		vector<string> *actionlog;

		Common::Rand aRand;
		data adata;

		int day = 0;

		int nowplayernum=0;
		Action nowaction;
	};
}
