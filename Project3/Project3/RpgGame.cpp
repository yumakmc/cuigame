#include "RpgGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include <string>
#include <algorithm>

using namespace rpggame;

namespace rpggame {
	const int MY_ATTACK_CENTER_X = 19;
	const int MY_ATTACK_CENTER_Y = 19;

	const int OP_ATTACK_CENTER_X = 19;
	const int OP_ATTACK_CENTER_Y = 9;

	const int PARALYZECOUNT = 10;

	static const int dx[4] = { -1,0,1,0 };
	static const int dy[4] = { 0,-1,0,1 };
}

bool RpgKillFrag = false;

RpgGame::RpgGame(gameSceneChanger* changer,const int aopponent) :gameBaseScene(changer), opponent(aopponent),op_hp(AllInfos[opponent].opinfo.hp), op_causeddamages(), my_causeddamages(), abackground(AllInfos[opponent].background), op_act(AllInfos[opponent].opinfo.acts), my_act(AllInfos[opponent].myinfo.acts), op_delay_waittime(){
	aRand.init();
	Initialize();
	situation = 5;
	my_hp = AllInfos[opponent].myinfo.hp;
	for (int i = 0; i < my_act.size();++i) {
		my_rest_waittime.push_back(my_act[i].maxwaittime);
	}
	for (int i = 0; i < op_act.size(); ++i) {
		op_delay_waittime.push_back(aRand.gen()%10);
	}
	for (int i = 0; i < op_act.size(); ++i) {
		op_rest_waittime.push_back(op_act[i].maxwaittime);
	}
}

void RpgGame::Initialize() {
}
void RpgGame::Update() {
	
#ifndef NDEBUG
		if (Keyboard_Get('C') == 1) {//�|��
			//�_���^���鏈��
			op_hp -= 1000;
			//op_damages.push_back(make_pair(my_atk[i], DAMAGE_REMAIN_FRAME));
			auto place = find_if(op_causeddamages.begin(), op_causeddamages.end(), [](const pair<int, int> a) {return a.second <= 0; });
			if (place == op_causeddamages.end()) {
				op_causeddamages.push_back(make_pair(1000, DAMAGE_REMAIN_FRAME));
			}
			else {
				*place = make_pair(1000, DAMAGE_REMAIN_FRAME);
			}
		
		}
		if (Keyboard_Get('D') == 1) {//���E
									 //�_���^���鏈��
			my_hp -= 1000;
			//op_damages.push_back(make_pair(my_atk[i], DAMAGE_REMAIN_FRAME));
			auto place = find_if(my_causeddamages.begin(), my_causeddamages.end(), [](const pair<int, int> a) {return a.second <= 0; });
			if (place == my_causeddamages.end()) {
				my_causeddamages.push_back(make_pair(1000, DAMAGE_REMAIN_FRAME));
			}
			else {
				*place = make_pair(1000, DAMAGE_REMAIN_FRAME);
			}

		}
#endif
#pragma region MY_ATTACK
	if (paralyzecount) {
		paralyzecount--;
	}
	else 
	{
		for (int i = 0; i < 4; ++i) {
			if (my_rest_waittime[i]) {
				my_rest_waittime[i]--;
			}else if (Keyboard_Get(VK_LEFT + i)  == 1) {//���A��A�E�A��
				if (!my_rest_waittime[i]) {
					//�_���^���鏈��
					MakeDamege(true, i);
				}
				else {
					paralyzecount = PARALYZECOUNT;
					//���т�鏈��
				}
			}
		}
			//if (opponent==2)
			//{
			//	for (int i = 0; i < 4; ++i) {
			//		if (Keyboard_Get(VK_LEFT + i) == 1) {//���A��A�E�A��
			//			if (!my_rest_waittime[i]) {
			//				//�_���^���鏈��
			//				op_hp -= my_atk[i];
			//				my_rest_waittime[i] = MY_MAX_WAITTIME[i];
			//				//op_damages.push_back(make_pair(my_atk[i], DAMAGE_REMAIN_FRAME));
			//				auto place = find_if(op_causeddamages.begin(), op_causeddamages.end(), [](const pair<int, int> a) {return a.second <= 0; });
			//				if (place == op_causeddamages.end()) {
			//					op_causeddamages.push_back(make_pair(my_atk[i], DAMAGE_REMAIN_FRAME));
			//				}
			//				else {
			//					*place = make_pair(my_atk[i], DAMAGE_REMAIN_FRAME);
			//				}
			//			}
			//			else {
			//				paralyzecount = PARALYZECOUNT;
			//				//���т�鏈��
			//			}
			//		}
			//	}
			//}
	}
#pragma endregion
#pragma region OP_ATTACK
	for (int i = 0; i < op_rest_waittime.size(); ++i) {
		if (op_rest_waittime[i]) {
			op_rest_waittime[i]--;
		}else{
			if (op_delay_waittime[i]) {
				op_delay_waittime[i]--;
			}
			else {
				MakeDamege(false, i);
				op_delay_waittime[i] = aRand.gen() % 10;
			}
			//�_���^���鏈��
		}
	}
#pragma endregion
	for_each(op_causeddamages.begin(), op_causeddamages.end(), [](pair<int, int> &a) {a.second --; });
	for_each(my_causeddamages.begin(), my_causeddamages.end(), [](pair<int, int> &a) {a.second --; });
	if (my_hp <= 0) {
		mgameSceneChanger->ChangeScene(eGameScene_Text);
		RpgKillFrag = false;
		//�I������
	}
	else if (op_hp <= 0) {
		mgameSceneChanger->ChangeScene(eGameScene_Text);
		RpgKillFrag = true;
		//�I������
	}

}
void RpgGame::Draw() {
	abackground.Draw();
	aDrawableConsole.draw(17, 2, "�G�F");
	aDrawableConsole.draw(20, 2, AllInfos[opponent].opinfo.name.c_str());

	for (int i = 0; i < op_causeddamages.size(); ++i) {
		if (op_causeddamages[i].second >= 0) {
			aDrawableConsole.draw(MY_ATTACK_CENTER_X - 5, MY_ATTACK_CENTER_Y + 5-i-2, (" -"+To_ZenString(op_causeddamages[i].first)).c_str());//�G�̗�
		}
	}
	aDrawableConsole.draw(MY_ATTACK_CENTER_X - 10, MY_ATTACK_CENTER_Y + 4, (AllInfos[opponent].opinfo.name+"�̖�").c_str());
	aDrawableConsole.draw(MY_ATTACK_CENTER_X - 5, MY_ATTACK_CENTER_Y + 5, To_ZenString(op_hp).c_str());
	
	for (int i = 0; i < my_causeddamages.size(); ++i) {
		if (my_causeddamages[i].second >= 0) {
			aDrawableConsole.draw(MY_ATTACK_CENTER_X +4, MY_ATTACK_CENTER_Y + 5 - i - 1, (" -" + To_ZenString(my_causeddamages[i].first)).c_str());//�������̗̑�
		}
	}
	aDrawableConsole.draw(MY_ATTACK_CENTER_X + 7, MY_ATTACK_CENTER_Y + 4, AllInfos[opponent].myinfo.name+"�̖�");
	aDrawableConsole.draw(MY_ATTACK_CENTER_X + 4, MY_ATTACK_CENTER_Y + 5, To_ZenString(my_hp).c_str());//���̗�

	switch (opponent) {
	default:
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + dx[0], MY_ATTACK_CENTER_Y + dy[0], "��");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + dx[1], MY_ATTACK_CENTER_Y + dy[1], "��");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + dx[2], MY_ATTACK_CENTER_Y + dy[2], "��");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + dx[3], MY_ATTACK_CENTER_Y + dy[3], "��");
	}

	for (int i = 0; i < 4; ++i) {
		string st = to_string(my_rest_waittime[i]);
		if (st.size() % 2) {
			st = " " + st;
		}
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + 2 * dx[i], MY_ATTACK_CENTER_Y + 2 * dy[i], st.c_str());
	}
	'1' + 1;
	switch (opponent) {
	default:
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + dx[0], OP_ATTACK_CENTER_Y + dy[0], "��");
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + dx[1], OP_ATTACK_CENTER_Y + dy[1], "��");
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + dx[2], OP_ATTACK_CENTER_Y + dy[2], "��");
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + dx[3], OP_ATTACK_CENTER_Y + dy[3], "��");
	}

	for (int i = 0; i < 4; ++i) {
		string st = to_string(op_rest_waittime[i]);
		if (st.size() % 2) {
			st = " " + st;
		}
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + 2 * dx[i], OP_ATTACK_CENTER_Y + 2 * dy[i], st.c_str());
	}

}
	
void RpgGame::MakeDamege(const bool  playerMake, const int atkNum) {
	int damage;
	int interval;
	if (!playerMake) {
		damage = op_act[atkNum].dmg;
		interval = op_act[atkNum].maxwaittime;
		my_hp -= damage;
		op_rest_waittime[atkNum] = interval;
		auto place = find_if(my_causeddamages.begin(), my_causeddamages.end(), [](const pair<int, int> a) {return a.second <= 0; });
		if (place == my_causeddamages.end()) {
			my_causeddamages.push_back(make_pair(damage, DAMAGE_REMAIN_FRAME));
		}
		else {
			*place = make_pair(damage, DAMAGE_REMAIN_FRAME);
		}
	}
	else {
		damage = my_act[atkNum].dmg;
		interval = my_act[atkNum].maxwaittime;
		op_hp -= damage;
		my_rest_waittime[atkNum] = interval;
		auto place = find_if(op_causeddamages.begin(), op_causeddamages.end(), [](const pair<int, int> a) {return a.second <= 0; });
		if (place == op_causeddamages.end()) {
			op_causeddamages.push_back(make_pair(damage, DAMAGE_REMAIN_FRAME));
		}
		else {
			*place = make_pair(damage, DAMAGE_REMAIN_FRAME);
		}
	}
}

string RpgGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}