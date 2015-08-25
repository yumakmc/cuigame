#include "RpgGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include <string>

const int ATTACK_CENTER_X = 19;
const int ATTACK_CENTER_Y = 19;

static const int dx[4] = { -1,0,1,0 };
static const int dy[4] = { 0,-1,0,1 };
RpgGame::RpgGame(gameSceneChanger* changer,const int aopponent) :gameBaseScene(changer), opponent(aopponent),op_hp(aopponent==0?50:(aopponent==1?70:100)){
	Initialize();
	;
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

					rest_waittime[i] = max_waittime[i];
				}
				else {
					//paralyzecount = 10;
					//しびれる処理
				}
			}
		}
		if (my_hp <= 0) {

		}
		else if (op_hp <= 0) {
			//終了処理
		}
	}
	
}
void RpgGame::Draw() {
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