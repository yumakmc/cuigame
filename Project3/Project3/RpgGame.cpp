#include "RpgGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "DrawBackGround.h"
#include <string>

const int ATTACK_CENTER_X = 19;
const int ATTACK_CENTER_Y = 19;

const int PARALYZECOUNT = 10;

static const int dx[4] = { -1,0,1,0 };
static const int dy[4] = { 0,-1,0,1 };
RpgGame::RpgGame(gameSceneChanger* changer,const int aopponent) :gameBaseScene(changer), opponent(aopponent),op_hp(GETENEMYINFO[opponent].hp), op_atk(GETENEMYINFO[opponent].atk), op_interval(GETENEMYINFO[opponent].interval){
	Initialize();
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
			if (rest_waittime[i]) {
				rest_waittime[i]--;
			}
		}
		for (int i = 0; i < 4; ++i) {
			if (Keyboard_Get(VK_LEFT + i)  == 1) {//左、上、右、下
				if (!rest_waittime[i]) {

					//ダメ与える処理
					op_hp -= my_atk[i];
					rest_waittime[i] = max_waittime[i];
				}
				else {
					paralyzecount = PARALYZECOUNT;
					//しびれる処理
				}
			}
		}
	}
	if (!(count % op_interval)) {
		my_hp -= op_atk;
	}
	if (my_hp <= 0) {

	}
	else if (op_hp <= 0) {
		//終了処理
	}
}
void RpgGame::Draw() {
	DrawBackGround(1);
	aDrawableConsole.draw(17, 2, "敵：");
	aDrawableConsole.draw(20, 2, GETENEMYINFO[opponent].name.c_str());
	aDrawableConsole.draw(ATTACK_CENTER_X-5, ATTACK_CENTER_Y + 5, To_ZenString(op_hp).c_str());
	aDrawableConsole.draw(ATTACK_CENTER_X+4, ATTACK_CENTER_Y + 5, To_ZenString(my_hp).c_str());
	aDrawableConsole.draw(ATTACK_CENTER_X+dx[0], ATTACK_CENTER_Y+dy[0], "←");
	aDrawableConsole.draw(ATTACK_CENTER_X + dx[1], ATTACK_CENTER_Y + dy[1], "↑");
	aDrawableConsole.draw(ATTACK_CENTER_X + dx[2], ATTACK_CENTER_Y + dy[2], "→");
	aDrawableConsole.draw(ATTACK_CENTER_X + dx[3], ATTACK_CENTER_Y + dy[3], "↓");

	for (int i = 0; i < 4; ++i) {
		string st = to_string(rest_waittime[i]);
		if (st.size() % 2) {
			st = " " + st;
		}
		aDrawableConsole.draw(ATTACK_CENTER_X + 2*dx[i], ATTACK_CENTER_Y + 2*dy[i], st.c_str());
		
	}
	
}

string RpgGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}