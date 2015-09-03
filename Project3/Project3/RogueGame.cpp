#include "RogueGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

using namespace roguegame;

namespace roguegame {
	const int LOG_LINE_Y = 20;

	const int PARTY_LEFT = 25;
	const int MY_PARTY_UP = 13;
	const int OP_PARTY_UP = 0;
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

	const int MAP_LEFT = 2;
	const int MAP_UP = 2;

	array<int, 91> EnemyMap = {
		0,0,0,0,1,0,1,0,3,0,
		0,0,0,2,0,1,0,1,0,0,
		0,0,3,0,0,1,0,0,2,0,
		0,0,0,0,0,2,0,0,0,0,
		0,0,4,0,0,0,0,1,0,0,
		0,0,1,0,4,0,2,0,0,0,
		0,0,0,2,0,0,0,1,0,0,
		0,0,3,0,0,0,1,0,0,0,
		2,0,0,0,0,4,0,0,2,0,
		0,
	};
}

RogueGame::RogueGame(gameSceneChanger* changer) 
	:gameBaseScene(changer), abackground(2), actionlog(new vector<string>), myparty(PARTY_LEFT, MY_PARTY_UP,actionlog),opparty(PARTY_LEFT, OP_PARTY_UP,actionlog){
	actionlog->push_back("s");

	myparty.AddMember(0);
	myparty.AddMember(1);
	opparty.AddMember(4);
	opparty.AddMember(5);

	aRand.init();
	Initialize();
	

	//int c = TABLE<0, 100>::next_exp;
	//
	//if (c == 5051) {
	//	int k=0;
	//	k++;
	//}
	
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
			actionlog->push_back("t‚ª¶‚Ü‚êA“~‚Í€‚É‚½");
			situation = 5;
		}
		break;
	case 1://ƒwƒ‹ƒv
		break;
	case 5://‚±‚¿‚ç‚ÌUŒ‚‘I‘ğ’†
		if (Keyboard_Get('A') == 1) {
			myparty.Act(A_Attack);
		}
		else if (Keyboard_Get('D') == 1) {
			myparty.Act(A_Defence);
		}
		else if (Keyboard_Get('S') == 1) {
			myparty.Act(A_Special);
		}
		break;
	case 6://‘Šè‚Ì‘ÎÛ‚ğ‘I‘ğ’†
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
#pragma region BACK
	abackground.Draw();
	aDrawableConsole.draw(4, 0, "‹Gß");
	
	vector<int> AliveId(myparty.GetAliveMemberId());
	for (int i = 0; i < 4; ++i) {
		if (find(AliveId.begin(), AliveId.end(), i) != AliveId.end()) {
			aDrawableConsole.draw(1 + 2 * i, 1, DATES[i].name.c_str());
		}
	}
	
#pragma endregion 
	
#pragma region MAP
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 13; ++j) {
			if (i % 2) {
				if (j != 12) {
					aDrawableConsole.draw(11-j + MAP_LEFT, MAP_UP + 2 * (6 - i) + 1, Common::To_ZString(EnemyMap[9 * i + j]).c_str());
				}
				else {
					aDrawableConsole.draw(MAP_LEFT, MAP_UP + 2 * (6 - i), Common::To_ZString(EnemyMap[9 * i + j]).c_str());
				}
			}
			else {
				if (j != 12) {
					aDrawableConsole.draw(j + MAP_LEFT, MAP_UP + 2 * (6 - i) + 1, Common::To_ZString(EnemyMap[9 * i + j]).c_str());
				}
				else {
					aDrawableConsole.draw(11 + MAP_LEFT, MAP_UP + 2 * (6 - i), Common::To_ZString(EnemyMap[9 * i + j]).c_str());
				}
			}
		}
	}
#pragma endregion

#pragma region LINE
	for (int i = 0; i < 25; ++i) {
		aDrawableConsole.draw(PARTY_LEFT - 1, i, " |");
	}
	for (int i = PARTY_LEFT; i < 40; ++i) {
		aDrawableConsole.draw(i, MY_PARTY_UP - 1, "--");
	}
	aDrawableConsole.draw(0, LOG_LINE_Y, "--------------------------------------------------");
#pragma endregion

	myparty.Draw();
	opparty.Draw();
	
	switch (situation)
	{
	case 0:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "‚y@‚ğ‰Ÿ‚µ‚ÄƒXƒ^[ƒg");
		break;
	case 1:
	case 5:
		break;

	case 10:
		break;
	case 11:
		break;
	default:
		assert(false);
		break;
	}

#pragma region LOG
	
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "ƒƒO");
	auto startit = actionlog->size() <= 3 ? actionlog->begin() : actionlog->end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog->end())break;
		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, *(startit + i));
	}
	switch (situation)
	{
	case 0:
		break;
	case 1:
		break;
	case 5:
		break;

	case 10:
		break;
	case 11:
		break;
	default:
		assert(false);
		break;
	}
#pragma endregion
}
