#pragma once
#include "gameBaseScene.h"
#include  "BackGround.h"
#include "Common.h"
#include <map>
#include <vector>
#include <string>
#include <utility>
using namespace std;
namespace  rpggame {
	
	struct Action {
		int dmg;
		int maxwaittime;
	};

	struct CharaInfo {
		string name;
		int hp;
		vector<Action> acts;
		/*CharaInfo(const string aname, const int ahp, const vector<pair<int, int>> &aact, const int abackground) :act(aact) {
			name = aname;
			hp = ahp;

			background = abackground;
		}*/
	};
	struct OpInfo :CharaInfo {
		int max_delaytime;
	};

	struct MyInfo :CharaInfo {
	};
	struct AllInfo {
		CharaInfo opinfo;
		CharaInfo myinfo;
		int background;
		int maxdelaytime;
	};
	static vector<AllInfo> AllInfos = {
		{
			{ "�H", 365,{ { 5,20 },{ 4,13 },{ 2,8 },{ 3,11 } } },
			{ "�t", 365,{ { 5,20 },{ 4,13 },{ 2,8 },{ 3,11 } } },
		0,30
		},
		{
			{ "��", 500,{ { 5,20 },{ 4,13 },{ 2,8 },{ 3,11 } } },
			{ "�t", 365,{ { 5,20 },{ 4,13 },{ 2,8 },{ 3,11 } } },
		2,15
		},
		{
			{ "�����̋�", 365,{ { 5,20 },{ 1,3 },{ 8,30 },{ 7,11 } } },
			{ "�t", 365,{ { 5,20 },{ 4,13 },{ 2,8 },{ 3,11 } } },
		2,10
		},
	};



	class RpgGame :public gameBaseScene {
	public:
		RpgGame(gameSceneChanger* changer, const int aopponent);
		void Initialize() override;
		//void Finalize() override;
		void Update() override;        //�X�V�������I�[�o�[���C�h�B
		void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	private:
		string inline To_ZenString(const int anum);
		void MakeDamege(const bool playerMake, const int atkNum);

		const int opponent;
		int op_hp;
		const vector<Action> op_act;
		vector<pair<int, int>> op_causeddamages;
		vector<int> op_rest_waittime;
		vector<int> op_delay_waittime;

		int my_hp = 365;
		const vector<Action> my_act;
		vector<pair<int, int>> my_causeddamages;
		vector<int> my_rest_waittime;

		const int DAMAGE_REMAIN_FRAME = 10;

		int paralyzecount = 0;

		BackGround abackground;

		int situation;//0:�ΐ�O 1:help�@5:�ΐ풆�@10:�����@11:����

		Common::Rand aRand;
		vector<pair<bool, Action>> actionlog;
	};
}