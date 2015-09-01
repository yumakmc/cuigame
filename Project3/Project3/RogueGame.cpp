#include "RogueGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

using namespace roguegame;

namespace roguegame {
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



RogueGame::RogueGame(gameSceneChanger* changer) :gameBaseScene(changer), actionlog(), abackground(2){
	aRand.init();
	Initialize();

		aMusic.Play(5);

}

void RogueGame::Initialize() {
}
void RogueGame::Update() {
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
		break;
	default:
		break;
	}
#ifndef NDEBUG
		
#endif
#pragma region MY_ATTACK
		
#pragma endregion
#pragma region OP_ATTACK
		
#pragma endregion
	
}
void RogueGame::Draw() {
	abackground.Draw();



	


	

	
#pragma region LOG
	aDrawableConsole.draw(0, LOG_LINE_Y, "--------------------------------------------------------------------------------");
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "ÉçÉO");
	auto startit = actionlog.size() <= 3 ? actionlog.begin() : actionlog.end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog.end())break;
		pair<int, Action> data(*(startit + i));
		string st;

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

	case 10:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ÇxÇnÇtÅ@Å@ÇvÇhÇm");
		break;
	case 11:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ÇxÇnÇtÅ@ÇkÇnÇrÇd");
		break;
	default:
		assert(false);
		break;
	}
#pragma endregion
}



string RogueGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}