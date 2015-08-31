#include "RpgGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

using namespace rpggame;

namespace rpggame {
	const int MY_ATTACK_CENTER_X = 19;
	const int MY_ATTACK_CENTER_Y = 14;

	const int MY_ATTACK_CENTER_X_L = 14;
	const int MY_ATTACK_CENTER_X_R = 24;

	const int OP_ATTACK_CENTER_X = 19;
	const int OP_ATTACK_CENTER_Y = 5;

	const int LOG_LINE_Y = 20;

	const int PARALYZECOUNT = 10;

	static const int dx[4] = { -1,0,1,0 };
	static const int dy[4] = { 0,-1,0,1 };

	static vector<string> TO_KEY =
	{
		"Å©",
		"Å™",
		"Å®",
		"Å´",
		"Ç`",
		"Çv",
		"Çc",
		"Çr",
	};
}

bool RpgKillFrag = false;

RpgGame::RpgGame(gameSceneChanger* changer,const int aopponent) :gameBaseScene(changer), opponent(aopponent),op_hp(AllInfos[opponent].opinfo.hp), op_causeddamages(), my_causeddamages(), abackground(AllInfos[opponent].background), op_act(AllInfos[opponent].opinfo.acts), my_act(AllInfos[opponent].myinfo.acts), op_delay_waittime(),actionlog(){
	aRand.init();
	Initialize();
	situation = 0;
	my_hp = AllInfos[opponent].myinfo.hp;
	for (int i = 0; i < my_act.size();++i) {
		my_rest_waittime.push_back(my_act[i].maxwaittime);
	}
	for (int i = 0; i < op_act.size(); ++i) {
		op_delay_waittime.push_back(aRand.gen()% AllInfos[opponent].maxdelaytime);
		op_rest_waittime.push_back(op_act[i].maxwaittime);
	}
	if (opponent == 2) {
		aMusic.Play(5);
	}
}

void RpgGame::Initialize() {
}
void RpgGame::Update() {
	abackground.Update();
	switch (situation) {
	case 0://ÉXÉ^Å[ÉgâÊñ 
		if (Keyboard_Get('Z') == 1) {
			situation = 5;
		}
		break;
	case 1://ÉwÉãÉv
		break;
	case 5:
#ifndef NDEBUG
		if (Keyboard_Get('C') == 1) {//ì|Ç∑
									 //É_ÉÅó^Ç¶ÇÈèàóù
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
		if (Keyboard_Get('Q') == 1) {//é©éE
									 //É_ÉÅó^Ç¶ÇÈèàóù
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
			for (int i = 0; i < my_act.size(); ++i) {
				if (my_rest_waittime[i]) {
					my_rest_waittime[i]--;
				}
				int keynum;
				if (i < 4) {
					keynum = VK_LEFT + i;
				}
				else if (i == 4) {
					keynum = 'A';
				}
				else if (i == 5) {
					keynum = 'W';
				}
				else if (i == 6) {
					keynum = 'D';
				}
				else if (i == 7) {
					keynum = 'S';
				}
				if (Keyboard_Get(keynum) == 1) {//ç∂ÅAè„ÅAâEÅAâ∫
					if (!my_rest_waittime[i]) {
						MakeDamege(true, i);
					}
					else {
						paralyzecount = PARALYZECOUNT;
					}
				}
			}
			//if (opponent==2)
			//{
			//	for (int i = 0; i < 4; ++i) {
			//		if (Keyboard_Get(VK_LEFT + i) == 1) {//ç∂ÅAè„ÅAâEÅAâ∫
			//			if (!my_rest_waittime[i]) {
			//				//É_ÉÅó^Ç¶ÇÈèàóù
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
			//				//ÇµÇ—ÇÍÇÈèàóù
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
			}
			else {
				if (op_delay_waittime[i]) {
					op_delay_waittime[i]--;
				}
				else {
					MakeDamege(false, i);
					op_delay_waittime[i] = aRand.gen() % AllInfos[opponent].maxdelaytime;
				}
				//É_ÉÅó^Ç¶ÇÈèàóù
			}
		}
#pragma endregion
		for_each(op_causeddamages.begin(), op_causeddamages.end(), [](pair<int, int> &a) {a.second--; });
		for_each(my_causeddamages.begin(), my_causeddamages.end(), [](pair<int, int> &a) {a.second--; });
		if (my_hp <= 0) {
			situation = 11;
			RpgKillFrag = false;
			//èIóπèàóù
		}
		else if (op_hp <= 0) {
			situation = 10;
			RpgKillFrag = true;
			//èIóπèàóù
		}
		break;
	case 10://èüÇø
		if (Keyboard_Get('Z') == 1) {
			mgameSceneChanger->ChangeScene(eGameScene_Text);
		}
		break;
	case 11://ïâÇØ
		if (Keyboard_Get('Z') == 1) {
			mgameSceneChanger->ChangeScene(eGameScene_Text);
		}
		break;

	default:
		assert(false);
	}
}
void RpgGame::Draw() {
	abackground.Draw();
	if (opponent == 2){
		aDrawableConsole.draw(18, 0, AllInfos[opponent].opinfo.name.c_str());
	}
	else {
		aDrawableConsole.draw(19, 0, AllInfos[opponent].opinfo.name.c_str());
	}
	aDrawableConsole.draw(19, 19, AllInfos[opponent].myinfo.name.c_str());

	for (int i = 0; i < min(6, op_causeddamages.size()); ++i) {
		if (op_causeddamages[i].second >= 0) {
			aDrawableConsole.draw(3, 6-i, (" -"+To_ZenString(op_causeddamages[i].first)).c_str());//ìGëÃóÕ
		}
	}
	aDrawableConsole.draw(2, 8, (AllInfos[opponent].opinfo.name+"ÇÃÇgÇo").c_str());
	aDrawableConsole.draw(3, 7, To_ZenString(op_hp).c_str());
	
	for (int i = 0; i <min(6, my_causeddamages.size()); ++i) {
		if (my_causeddamages[i].second >= 0) {
			aDrawableConsole.draw(3, 13+i, (" -" + To_ZenString(my_causeddamages[i].first)).c_str());//Ç±Ç¡ÇøÇÃëÃóÕ
		}
	}
	aDrawableConsole.draw(2, 11, (AllInfos[opponent].myinfo.name+"ÇÃÇgÇo").c_str());
	aDrawableConsole.draw(3, 12, To_ZenString(my_hp).c_str());//é©ëÃóÕ

	/*switch (opponent) {
	case 2:
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_L + 2 * dx[0], MY_ATTACK_CENTER_Y + dy[0], TO_KEY[4]);
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_L + 2 * dx[1], MY_ATTACK_CENTER_Y + dy[1], "Çv");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_L + 2 * dx[2], MY_ATTACK_CENTER_Y + dy[2], "Çc");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_L + 2 * dx[3], MY_ATTACK_CENTER_Y + dy[3], "Çr");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_R + 2 * dx[0], MY_ATTACK_CENTER_Y + dy[0], "Å©");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_R + 2 * dx[1], MY_ATTACK_CENTER_Y + dy[1], "Å™");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_R + 2 * dx[2], MY_ATTACK_CENTER_Y + dy[2], "Å®");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X_R + 2 * dx[3], MY_ATTACK_CENTER_Y + dy[3], "Å´");
		break;
	default:
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + 2 * dx[0], MY_ATTACK_CENTER_Y + dy[0], "Å©");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + 2 * dx[1], MY_ATTACK_CENTER_Y + dy[1], "Å™");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + 2 * dx[2], MY_ATTACK_CENTER_Y + dy[2], "Å®");
		aDrawableConsole.draw(MY_ATTACK_CENTER_X + 2 * dx[3], MY_ATTACK_CENTER_Y + dy[3], "Å´");
	}*/
	
	for (int i = 0; i < my_act.size(); ++i) {
		
		string stt = to_string(my_rest_waittime[i]);
		if (stt.size() % 2) {
			stt = " " + stt;
		}
		string std = to_string(my_act[i].dmg);
		if (std.size() % 2) {
			std = " " + std;
		}
		int ax;
		if (my_act.size() == 4) {
			ax = MY_ATTACK_CENTER_X;
		}
		else if (i<4) {
			ax = MY_ATTACK_CENTER_X_R;
		}
		else {	
			ax = MY_ATTACK_CENTER_X_L;
		}
		//if (i == 0||i==4) {
		//	aDrawableConsole.draw(ax, MY_ATTACK_CENTER_Y,"çU");
		//}
		//aDrawableConsole.draw(ax + 1 * dx[i % 4], MY_ATTACK_CENTER_Y + 1 * dy[i % 4], std.c_str());
		aDrawableConsole.draw(ax + 2 * dx[i % 4], MY_ATTACK_CENTER_Y + 2 * dy[i % 4], TO_KEY[i].c_str());
		if (my_rest_waittime[i]) {
			aDrawableConsole.draw(ax + 3 * dx[i % 4], MY_ATTACK_CENTER_Y + 3 * dy[i % 4], stt.c_str());
		}
		else {
			aDrawableConsole.setColor(DrawableConsole::COLOR::C_BLACK, DrawableConsole::COLOR::C_LYELLOW);
			aDrawableConsole.draw(ax + 3 * dx[i % 4], MY_ATTACK_CENTER_Y + 3 * dy[i % 4], stt.c_str());
			aDrawableConsole.loadDefaultColor();
		}

	}

	for (int i = 0; i < 4; ++i) {
		string stt = to_string(op_rest_waittime[i]);
		if (stt.size() % 2) {
			stt = " " + stt;
		}
		string std = to_string(op_act[i].dmg);
		if (std.size() % 2) {
			std = " " + std;
		}
		//aDrawableConsole.draw(OP_ATTACK_CENTER_X + 1 * dx[i], OP_ATTACK_CENTER_Y + 1 * dy[i], std.c_str());
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + 2 * dx[i], OP_ATTACK_CENTER_Y + 2 * dy[i], TO_KEY[i].c_str());
		aDrawableConsole.draw(OP_ATTACK_CENTER_X + 3 * dx[i], OP_ATTACK_CENTER_Y + 3 * dy[i], stt.c_str());
	}
#pragma region LOG
	aDrawableConsole.draw(0, LOG_LINE_Y, "--------------------------------------------------------------------------------");
	aDrawableConsole.draw(1, LOG_LINE_Y+1, "ÉçÉO");
	auto startit = actionlog.size() <= 3?actionlog.begin():actionlog.end()-4;
	for (int i = 0; i < 4; ++i) {
		if (startit+i == actionlog.end())break;
		pair<int, Action> data(*(startit+i));
		string st;
		if (data.first) {
			st = (AllInfos[opponent].opinfo.name + "Ç…" + To_ZenString(data.second.dmg) + "ÇÃÉ_ÉÅÅ[ÉW");
			
		}
		else {		
			st = (AllInfos[opponent].myinfo.name + "Ç…" + To_ZenString(data.second.dmg) + "ÇÃÉ_ÉÅÅ[ÉW");
		}
		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, st.c_str());
	}
	switch (situation)
	{
	case 0:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ÇyÅ@ÇâüÇµÇƒÉXÉ^Å[Ég");
		break;
	case 1:
	case 5:
		break;

	case 10 :
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ÇxÇnÇtÅ@Å@ÇvÇhÇm");
		break;
	case 11 :
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ÇxÇnÇtÅ@ÇkÇnÇrÇd");
		break;
	default:
		assert(false);
		break;
	}
#pragma endregion
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
		actionlog.push_back(make_pair(playerMake, op_act[atkNum]));;
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
		actionlog.push_back(make_pair(playerMake, my_act[atkNum]));
	}
}

string RpgGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}