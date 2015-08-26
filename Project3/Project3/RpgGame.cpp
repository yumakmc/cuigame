#include "RpgGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "DrawBackGround.h"
#include <string>
#include <algorithm>

const int ATTACK_CENTER_X = 19;
const int ATTACK_CENTER_Y = 19;

const int PARALYZECOUNT = 10;

static const int dx[4] = { -1,0,1,0 };
static const int dy[4] = { 0,-1,0,1 };
RpgGame::RpgGame(gameSceneChanger* changer,const int aopponent) :gameBaseScene(changer), opponent(aopponent),op_hp(GETENEMYINFO[opponent].hp), op_atk(GETENEMYINFO[opponent].atk), op_interval(GETENEMYINFO[opponent].interval), op_damages(), my_damages(){
	Initialize();
	situation = 5;
	op_rest_waittime = op_interval;
}

void RpgGame::Initialize() {
}
void RpgGame::Update() {
	count++;
	if (paralyzecount) {
		paralyzecount--;
	}
	else {
		for (int i = 0; i < 4; ++i) {
			if (my_rest_waittime[i]) {
				my_rest_waittime[i]--;
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (Keyboard_Get(VK_LEFT + i)  == 1) {//ç∂ÅAè„ÅAâEÅAâ∫
				if (!my_rest_waittime[i]) {
					//É_ÉÅó^Ç¶ÇÈèàóù
					op_hp -= my_atk[i];
					my_rest_waittime[i] = MY_MAX_WAITTIME[i];
					//op_damages.push_back(make_pair(my_atk[i], DAMAGE_REMAIN_FRAME));
					auto place = find_if(op_damages.begin(), op_damages.end(), [](const pair<int, int> a) {return a.second <= 0; });
					if (place == op_damages.end()) {
						op_damages.push_back(make_pair(my_atk[i], DAMAGE_REMAIN_FRAME));
					}
					else {
						*place = make_pair(my_atk[i], DAMAGE_REMAIN_FRAME);
					}
				}
				else {
					paralyzecount = PARALYZECOUNT;
					//ÇµÇ—ÇÍÇÈèàóù
				}
			}
		}
	}
	if (op_rest_waittime) {
		op_rest_waittime--;
	}else{
		my_hp -= op_atk;
		op_rest_waittime =op_interval ;
		//my_damages.push_back(make_pair(op_atk, DAMAGE_REMAIN_FRAME));
		auto place=find_if(my_damages.begin(), my_damages.end(), [](const pair<int, int> a) {return a.second <= 0; });
		if (place == my_damages.end()) {
			my_damages.push_back(make_pair(op_atk, DAMAGE_REMAIN_FRAME));
		}
		else {
			*place= make_pair(op_atk, DAMAGE_REMAIN_FRAME);
		}
	}
	for_each(op_damages.begin(), op_damages.end(), [](pair<int, int> &a) {a.second --; });
	for_each(my_damages.begin(), my_damages.end(), [](pair<int, int> &a) {a.second --; });
	/*op_damages.erase(remove_if(op_damages.begin(), op_damages.end(), [](const pair<int, int> &a) {return !a.second; }),op_damages.end());
	my_damages.erase(remove_if(my_damages.begin(), my_damages.end(), [](const pair<int, int> &a) {return !a.second; }), my_damages.end());
	*/
	if (my_hp <= 0) {
		mgameSceneChanger->ChangeScene(eGameScene_Text);
		//èIóπèàóù
	}
	else if (op_hp <= 0) {
		mgameSceneChanger->ChangeScene(eGameScene_Text);
		//èIóπèàóù
	}
}
void RpgGame::Draw() {
	DrawBackGround(GETENEMYINFO[opponent].background);
	aDrawableConsole.draw(17, 2, "ìGÅF");
	aDrawableConsole.draw(20, 2, GETENEMYINFO[opponent].name.c_str());

	for (int i = 0; i < op_damages.size(); ++i) {
		if (op_damages[i].second >= 0) {
			aDrawableConsole.draw(ATTACK_CENTER_X - 4, ATTACK_CENTER_Y + 5-i-1, To_ZenString(-op_damages[i].first).c_str());//ìGëÃóÕ
		}
	}
	aDrawableConsole.draw(ATTACK_CENTER_X - 5, ATTACK_CENTER_Y + 5, To_ZenString(op_hp).c_str());//ìGëÃóÕ
	
	for (int i = 0; i < my_damages.size(); ++i) {
		if (my_damages[i].second >= 0) {
			aDrawableConsole.draw(ATTACK_CENTER_X +5, ATTACK_CENTER_Y + 5 - i - 1, To_ZenString(-my_damages[i].first).c_str());//ìGëÃóÕ
		}
	}
	aDrawableConsole.draw(ATTACK_CENTER_X + 4, ATTACK_CENTER_Y + 5, To_ZenString(my_hp).c_str());//é©ëÃóÕ


	aDrawableConsole.draw(ATTACK_CENTER_X + dx[0], ATTACK_CENTER_Y + dy[0], "Å©");
	aDrawableConsole.draw(ATTACK_CENTER_X + dx[1], ATTACK_CENTER_Y + dy[1], "Å™");
	aDrawableConsole.draw(ATTACK_CENTER_X + dx[2], ATTACK_CENTER_Y + dy[2], "Å®");
	aDrawableConsole.draw(ATTACK_CENTER_X + dx[3], ATTACK_CENTER_Y + dy[3], "Å´");

	for (int i = 0; i < 4; ++i) {
		string st = to_string(my_rest_waittime[i]);
		if (st.size() % 2) {
			st = " " + st;
		}
		aDrawableConsole.draw(ATTACK_CENTER_X + 2 * dx[i], ATTACK_CENTER_Y + 2 * dy[i], st.c_str());
	}
}
	


string RpgGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}