#pragma once 
#include "TranpGame.h"
#include "Keyboard.h"
#include "Data_Rand.h"
#include <assert.h>

using namespace std;

const int OP_UNUSEDCARDLIST_LEFT = 4;
const int OP_UNUSEDCARDLIST_UP = 1;
const int MY_UNUSEDCARDLIST_LEFT = 4;
const int MY_UNUSEDCARDLIST_UP = 17;


static map<int, string> TOTRANP = {
	{ 1,"‚`"},
	{ 2,"‚Q" },
	{ 3,"‚R" },
	{ 4,"‚S" },
	{ 5,"‚T" },
	{ 6,"‚U" },
	{ 7,"‚V" },
	{ 8,"‚W" },
	{ 9,"‚X" },
	{ 10,"10" },
	{ 11,"‚i" },
	{ 12,"‚p" },
	{ 13,"‚j" },
	{14,"Jo"}
};

TranpGame::TranpGame(const int aopponent,vector<string> atexts, gameSceneChanger* changer) 
	:gameBaseScene(changer),opponent(aopponent), opcards(){
	for (int i = 0; i < 13; ++i) {
		mycarduseds[i] = false;
		opcarduseds[i] = false;
		opcards.push_back(i + 1);
	}
	mypoint = 0;
	oppoint = 0;
}
void TranpGame::Initialize() {

}

void TranpGame::Update() {
	int mychoosenum = 0;
	for (int i = 0; i < 9; ++i) {
		if (Keyboard_Get('1' + i)) {
			mycarduseds[i] = true;
			mychoosenum = i+1;
			break;
		}
	}
	if (mychoosenum == 0) {
		if (Keyboard_Get('0')) {
			mycarduseds[9] = true;
			mychoosenum = 10;
		}
		else if (Keyboard_Get('J')) {
			mycarduseds[10] = true;
			mychoosenum = 11;
		}
		else if (Keyboard_Get('Q')) {
			mycarduseds[11] = true;
			mychoosenum = 12;
		}
		else if (Keyboard_Get('K')) {
			mycarduseds[12] = true;
			mychoosenum = 13;
		}
	}
}
void TranpGame::Draw() {
	assert(false);
}
void TranpGame::Draw(vector<string> &tmpfield) {
	switch (opponent) {
	case 0:
		tmpfield[0].replace(0, 2, "‚à‚¤Ž€‚ñ‚¾‚Í‚¸‚¶‚á‚È‚©‚Á‚½‚Ì‚©");
		tmpfield[SIZE_Y - 1].replace(0, 2, "‚à‚¤Ž€‚ñ‚¾‚Í‚¸‚¶‚á‚È‚©‚Á‚½‚Ì‚©");
		tmpfield[OP_UNUSEDCARDLIST_UP].replace(OP_UNUSEDCARDLIST_LEFT-2, 2, "“~");
		break;
	case 1:
		break;
	case 2:
		break;
	}
	
	for (int i = 0; i < 7; ++i) {
		if(!opcarduseds[i])
			tmpfield[OP_UNUSEDCARDLIST_UP].replace(OP_UNUSEDCARDLIST_LEFT+4*i, 2, TOTRANP[i+1]);
	}
	for (int i = 7; i < 13; ++i) {
		if (!opcarduseds[i])
tmpfield[OP_UNUSEDCARDLIST_UP+1].replace(OP_UNUSEDCARDLIST_LEFT+2+4*(i-7), 2, TOTRANP[i+1]);
	}
	for (int i = 0; i < 7; ++i) {
		if (!mycarduseds[i])
tmpfield[MY_UNUSEDCARDLIST_UP].replace(MY_UNUSEDCARDLIST_LEFT+4*i, 2, TOTRANP[i+1]);
	}
	for (int i = 7; i < 13; ++i) {
		if (!mycarduseds[i])
			tmpfield[MY_UNUSEDCARDLIST_UP + 1].replace(MY_UNUSEDCARDLIST_LEFT + 2 + 4 * (i-7), 2, TOTRANP[i + 1]);
	}
	string oppost = to_string(oppoint);
	if (oppost.size() % 2) {
		oppost = " " + oppost;
	}
	tmpfield[3].replace(2, oppost.size(), oppost);
	string mypost = to_string(mypoint);
	if (mypost.size() % 2) {
		mypost = " " + mypost;
	}
	tmpfield[16].replace(2, mypost.size(), mypost);
}