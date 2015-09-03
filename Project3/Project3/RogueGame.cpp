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
	//	"Å©",
	//	"Å™",
	//	"Å®",
	//	"Å´",
	//	"Ç`",
	//	"Çv",
	//	"Çc",
	//	"Çr",
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
	:gameBaseScene(changer), abackground(2), myparty(PARTY_LEFT, MY_PARTY_UP),opparty(PARTY_LEFT, OP_PARTY_UP), actionlog(){

	myparty.AddMember(0);
	myparty.AddMember(1);
	opparty.AddMember(4);
	opparty.AddMember(5);
	MyChara a(0);

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
	case 0://ÉXÉ^Å[ÉgâÊñ 
		if (Keyboard_Get('Z') == 1) {
			actionlog.push_back("ì~ÇÕéÄÇ…ÅAètÇ™ê∂Ç‹ÇÍÇΩ");
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
#pragma region BACK
	abackground.Draw();
	aDrawableConsole.draw(4, 0, "ãGêﬂ");
	
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
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ÇyÅ@ÇâüÇµÇƒÉXÉ^Å[Ég");
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
	
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "ÉçÉO");
	auto startit = actionlog.size() <= 3 ? actionlog.begin() : actionlog.end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog.end())break;
		string st= *startit;

		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, st.c_str());
	}
	switch (situation)
	{
	case 0:
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
