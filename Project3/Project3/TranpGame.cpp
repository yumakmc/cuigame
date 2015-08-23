#pragma once 
#include "TranpGame.h"
#include "Keyboard.h"
#include "Data_Rand.h"
#include <assert.h>
#include <algorithm>
#include <time.h>

using namespace std;

const int OP_UNUSEDCARDLIST_LEFT = 10;
const int OP_UNUSEDCARDLIST_UP = 1;
const int MY_UNUSEDCARDLIST_LEFT = 10;
const int MY_UNUSEDCARDLIST_UP = 17;

const int OP_CORE_LEFT = 4;
const int OP_CORE_UP = 2;
const int MY_CORE_LEFT = 4;
const int MY_CORE_UP = 17;

const int RESULT_CARDLIST_LEFT = 10;
const int RESULT_CARDLIST_UP = 5;

int flag = 0;//Ç±Ç±ÇﬂÇøÇ·Ç≠ÇøÇ·ì™à´Ç¢ÇÃÇ≈óvèCê≥

static map<int, string> WINMARK = {
	{ 1,"Åõ" },
	{ 0,"É¢" },
	{ -1,"Å~" },
};

static map<int, string> TOTRANP = {
	{ 1,"Ç`"},
	{ 2,"ÇQ" },
	{ 3,"ÇR" },
	{ 4,"ÇS" },
	{ 5,"ÇT" },
	{ 6,"ÇU" },
	{ 7,"ÇV" },
	{ 8,"ÇW" },
	{ 9,"ÇX" },
	{ 10,"10" },
	{ 11,"Çi" },
	{ 12,"Çp" },
	{ 13,"Çj" },
	{ 0,"Jo"}
};

TranpGame::TranpGame(const int aopponent,vector<string> atexts, gameSceneChanger* changer) 
	:gameBaseScene(changer),opponent(aopponent), opcardorder(), mycardorder(),targetscore(((opponent==0)?80:((opponent==1)?100:120))){
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 13; ++i) {
		mycarduseds[i] = false;
		opcarduseds[i] = false;
		opcardorder.push_back(i+1);
	}
	if (opponent == 2) {
		opcardorder[1] = 0;//âƒÇæÇØ2Ç™jokerÇ…
	}
	do {
		random_shuffle(opcardorder.begin(), opcardorder.end());
	} while (opponent == 2 && (opcardorder[5] != 0&&opcardorder[4] != 0&&opcardorder[6] != 0));//âƒÇÃéûÇÕjokerÇ™567î’ñ⁄Ç…Ç≈ÇÈ
	
	oppoint = ((opponent == 0) ? 0 : ((opponent == 1) ? 20 : 30));
	mypoint = ((opponent == 0) ? 0 : ((opponent == 1) ? -20 : -30));;
	undecidedpoint = 0;
	turn = 0;
	serihunum = 0;
	flag = 0;
}
void TranpGame::Initialize() {

}
void TranpGame::Update() {
	int mychoosenum = 0;
	int opchoosenum = 0;
	
	if (Keyboard_Get('Z')) {
		if (turn == 13) {
			flag = mypoint<=oppoint;
			mgameSceneChanger->ChangeScene(eGameScene_Text);
		}
	}
	for (int i = 0; i < 9; ++i){
		if (Keyboard_Get('1' + i)) {
			if (!mycarduseds[i]) {
				mycarduseds[i] = true;		
				mychoosenum = i + 1;	
				mycardorder.push_back(i+1);
				break;
			}
		}
	}
	if (mychoosenum == 0) {
		if (Keyboard_Get('0')) {
			if (!mycarduseds[9]) {
				mycarduseds[9] = true;
				mychoosenum = 10;
				mycardorder.push_back(10);
			}
		}
		else if (Keyboard_Get('J')) {
			if (!mycarduseds[10]) {
				mycarduseds[10] = true;
				mychoosenum = 11;
				mycardorder.push_back(11);
			}
		}
		else if (Keyboard_Get('Q')) {
			if (!mycarduseds[11]) {
				mycarduseds[11] = true;
				mychoosenum = 12;
				mycardorder.push_back(12);
			}
		}
		else if (Keyboard_Get('K')) {
			if (!mycarduseds[12]) {
				mycarduseds[12] = true;
				mychoosenum = 13;
				mycardorder.push_back(13);			
			}
		}
	}
	if (mychoosenum != 0) {
		opcarduseds[opcardorder[turn]==0?1:opcardorder[turn] - 1] = true;
		opchoosenum = opcardorder[turn];
		if (opchoosenum == 0) {
			serihunum = 1;
		}
		turn++;
		const int winner(GetWinner(mychoosenum, opchoosenum));
		if (winner==1) {//ëäéËèüÇø
			mypoint += mychoosenum + opchoosenum+ undecidedpoint;
			undecidedpoint = 0;
		}
		else if (winner==-1) {//é©ï™èüÇø
			oppoint += mychoosenum + opchoosenum+ undecidedpoint;
			undecidedpoint = 0;
		}
		else {//ìØì_
			undecidedpoint += mychoosenum + opchoosenum;
		}
	}
}
void TranpGame::Draw() {
	assert(false);
}
void TranpGame::Draw(vector<string> &tmpfield) {
	switch (opponent) {
	case 0:
		switch (serihunum) {
		case 0:
			tmpfield[0].replace(0, 32, "ÅuÇΩÇΩÇ´ãNÇ±Ç≥ÇÍÇƒâΩÇ©Ç∆évÇ¶ÇŒÅv");
			tmpfield[SIZE_Y - 1].replace(0, 32, "ÅuÇΩÇΩÇ´ãNÇ±Ç≥ÇÍÇƒâΩÇ©Ç∆évÇ¶ÇŒÅv");
		case 2:
			tmpfield[0].replace(0, 32, "ÅuÇΩÇΩÇ´ãNÇ±Ç≥ÇÍÇƒâΩÇ©Ç∆évÇ¶ÇŒÅv");
			tmpfield[SIZE_Y - 1].replace(0, 32, "ÅuÇΩÇΩÇ´ãNÇ±Ç≥ÇÍÇƒâΩÇ©Ç∆évÇ¶ÇŒÅv");
		
		}

		tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "ì~");
		tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "èt");
		break;
	case 1:
		switch (serihunum) {
		case 0:
			tmpfield[0].replace(0, 32, "ÅuÇΩÇΩÇ´ãNÇ±Ç≥ÇÍÇƒâΩÇ©Ç∆évÇ¶ÇŒÅv");
			tmpfield[SIZE_Y - 1].replace(0, 32, "ÅuÇΩÇΩÇ´ãNÇ±Ç≥ÇÍÇƒâΩÇ©Ç∆évÇ¶ÇŒÅv");
		case 2:
			tmpfield[0].replace(0, 38, "ÅuéEÇ≥ÇÍÇΩÇ≠Ç»Ç¢ÇÃÇ»ÇÁéÄÇÀÇŒÇ¢Ç¢ÇÃÇ…Åv");
			tmpfield[SIZE_Y - 1].replace(0, 38, "ÅuéEÇ≥ÇÍÇΩÇ≠Ç»Ç¢ÇÃÇ»ÇÁéÄÇÀÇŒÇ¢Ç¢ÇÃÇ…Åv");
		}
		tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "èH");
		tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "èt");
		break;
	case 2:
		switch (serihunum) {
		case 0:
			tmpfield[0].replace(0, 40, "ÅuÇ†ÇÍÇÍìÒÉPåéëOÇ…éEÇµÇΩÇÕÇ∏ÇæÇ¡ÇΩÇÃÇ…Åv");
			tmpfield[SIZE_Y - 1].replace(0, 40, "ÅuÇ†ÇÍÇÍìÒÉPåéëOÇ…éEÇµÇΩÇÕÇ∏ÇæÇ¡ÇΩÇÃÇ…Åv");
			break;
		case 1:
			tmpfield[0].replace(0, 38, "ÅuÇµÇ©ÇΩÇ»Ç¢Ç‡Ç§àÍìxéEÇµíºÇµÇƒÇ‚ÇÈÇ©Åv");
			tmpfield[SIZE_Y - 1].replace(0, 38, "ÅuÇµÇ©ÇΩÇ»Ç¢Ç‡Ç§àÍìxéEÇµíºÇµÇƒÇ‚ÇÈÇ©Åv");
			break;
		}

		tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "âƒ");
		tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "èt");
		break;	
	}
	if (turn == 13) {
		if (mypoint > oppoint) {//é©ï™èüÇ¡ÇΩÇÁ
			tmpfield[13].replace(2, 6, "ÇvÇhÇm");
			tmpfield[6].replace(0, 8, "ÇkÇnÇrÇd");	
			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "éÄ");
			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT - 2, 2, "éÄ");
			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT + 2, 2, "éÄ");
			tmpfield[OP_CORE_UP - 1].replace(OP_CORE_LEFT, 2, "éÄ");
			tmpfield[OP_CORE_UP + 1].replace(OP_CORE_LEFT, 2, "éÄ");
		}
		else {
			tmpfield[6].replace(2, 6, "ÇvÇhÇm");
			tmpfield[13].replace(0, 8, "ÇkÇnÇrÇd");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "éÄ");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT - 2, 2, "éÄ");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT + 2, 2, "éÄ");
			tmpfield[MY_CORE_UP - 1].replace(MY_CORE_LEFT, 2, "éÄ");
			tmpfield[MY_CORE_UP + 1].replace(MY_CORE_LEFT, 2, "éÄ");
		}
	}
	
	for (int i = 0; i < 13; ++i) {
		if (!opcarduseds[i]) {
			if (i < 7) {
				tmpfield[OP_UNUSEDCARDLIST_UP].replace(OP_UNUSEDCARDLIST_LEFT + 4 * i, 2, TOTRANP[i + 1]);
			}
			else {
				tmpfield[OP_UNUSEDCARDLIST_UP + 1].replace(OP_UNUSEDCARDLIST_LEFT + 2 + 4 * (i - 7), 2, TOTRANP[i + 1]);
			}
		}
	}
	for (int i = 0; i < 13; ++i) {
		if (!mycarduseds[i]) {
			if (i < 7) {
				tmpfield[MY_UNUSEDCARDLIST_UP].replace(MY_UNUSEDCARDLIST_LEFT + 4 * i, 2, TOTRANP[i + 1]);
			}
			else {
				tmpfield[MY_UNUSEDCARDLIST_UP + 1].replace(MY_UNUSEDCARDLIST_LEFT + 2 + 4 * (i - 7), 2, TOTRANP[i + 1]);
			}
		}
	}
	string oppost = To_ZenString(oppoint);
	tmpfield[ 4].replace(2, 4+oppost.size(), "ì˙ÅF" + oppost);
	string mypost = To_ZenString(mypoint);
	tmpfield[15].replace(2, 4+mypost.size(), "ì˙ÅF"+mypost);
	for (int i = 0; i < 13; ++i) {
		if (i < turn) {
			const int winner(GetWinner(mycardorder[i], opcardorder[i]));
			if (i < 7) {
				tmpfield[RESULT_CARDLIST_UP + 0].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, WINMARK[-winner]);
				tmpfield[RESULT_CARDLIST_UP + 1].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, TOTRANP[opcardorder[i]]);
				tmpfield[RESULT_CARDLIST_UP + 2].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, TOTRANP[mycardorder[i]]);
				tmpfield[RESULT_CARDLIST_UP + 3].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, WINMARK[winner]);
			}
			else {
				tmpfield[RESULT_CARDLIST_UP + 4].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, WINMARK[-winner]);
				tmpfield[RESULT_CARDLIST_UP + 5].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, TOTRANP[opcardorder[i]]);
				tmpfield[RESULT_CARDLIST_UP + 6].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, TOTRANP[mycardorder[i]]);
				tmpfield[RESULT_CARDLIST_UP + 7].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, WINMARK[winner]);
			}
			if (i != 12) {
				string amark;
				if (opcardorder[i + 1]>opcardorder[i]) {
					amark = "ÅÉ";
				}
				else  if (opcardorder[i + 1] < opcardorder[i]) {
					amark = "ÅÑ";
				}
				else {
					amark = "ÅÅ";
				}
				if (i < 7) {
					tmpfield[RESULT_CARDLIST_UP + 1].replace(RESULT_CARDLIST_LEFT + 4 * i+2, 2, amark);
				}
				else {
					tmpfield[RESULT_CARDLIST_UP + 5].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7)+2, 2, amark);
				}
			}
		}
		else {
			if (i < 7) {
				tmpfield[RESULT_CARDLIST_UP + 1].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, "ÅH");
			}
			else {
				tmpfield[RESULT_CARDLIST_UP + 5].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, "ÅH");
			}
		}
	}
	tmpfield[9].replace(2, 4, "écì˙");
	string ast(To_ZenString(undecidedpoint));
	tmpfield[10].replace(2, ast.size(), ast);
	
}
int inline TranpGame::GetWinner(int mynum,int opnum) {
	if (mynum == 0) {
		mynum =100;
	}
	if (opnum == 0) {
		opnum = 100;
	}
	if (mynum == 1) {
		mynum = 14;
	}
	if (opnum == 1) {
		opnum = 14;
	}
	if (mynum > opnum) {
		return 1;
	}
	else if (mynum == opnum) {
		return 0;
	}
	else {
		return -1;
	}
}
string TranpGame::To_ZenString(const int anum) {
	string st = to_string(anum);
	if (st.size() % 2) {
		st = " " + st;
	}
	return st;
}