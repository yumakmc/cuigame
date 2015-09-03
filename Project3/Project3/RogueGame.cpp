#include "RogueGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

using namespace roguegame;

namespace roguegame {
	//static const int dx[4] = { -1,0,1,0 };
	//static const int dy[4] = { 0,-1,0,1 };
	//static vector<string> TO_KEY =
	//{
	//	"©",
	//	"ª",
	//	"¨",
	//	"«",
	//	"‚`",
	//	"‚v",
	//	"‚c",
	//	"‚r",
	//};
}

RogueGame::RogueGame(gameSceneChanger* changer) :gameBaseScene(changer), abackground(2), myparty(),opparty() {
	myparty.AddMember(0);
	myparty.AddMember(1);
	opparty.AddMember(4);
	MyChara a(0);

	aRand.init();
	Initialize();
	

	int c = TABLE<0, 100>::next_exp;

	
	if (c == 5051) {
		int k=0;
		k++;
	}
	
	aMusic.Play(5);

}

void RogueGame::Initialize() {
}
void RogueGame::Update() {
	abackground.Update();
	myparty.Update();
	opparty.Update();
	switch (situation) {
	case 0://ƒXƒ^[ƒg‰æ–Ê
		if (Keyboard_Get('Z') == 1) {
			situation = 5;
		}
		break;
	case 1://ƒwƒ‹ƒv
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
	myparty.Draw();
	opparty.Draw();
	
#pragma region LOG
	/*aDrawableConsole.draw(0, LOG_LINE_Y, "--------------------------------------------------------------------------------");
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "ƒƒO");
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
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "‚y@‚ğ‰Ÿ‚µ‚ÄƒXƒ^[ƒg");
		break;
	case 1:
	case 5:
		break;

	case 10:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "‚x‚n‚t@@‚v‚h‚m");
		break;
	case 11:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "‚x‚n‚t@‚k‚n‚r‚d");
		break;
	default:
		assert(false);
		break;
	}*/
#pragma endregion
}



string RogueGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}