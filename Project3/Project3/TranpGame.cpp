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
	{ 1,"Ａ"},
	{ 2,"２" },
	{ 3,"３" },
	{ 4,"４" },
	{ 5,"５" },
	{ 6,"６" },
	{ 7,"７" },
	{ 8,"８" },
	{ 9,"９" },
	{ 10,"10" },
	{ 11,"Ｊ" },
	{ 12,"Ｑ" },
	{ 13,"Ｋ" },
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
	
}
void TranpGame::Draw() {
	assert(false);
}
void TranpGame::Draw(vector<string> &tmpfield) {
	tmpfield[0].replace(0, 2, "もう死んだはずじゃなかったのか");
	tmpfield[SIZE_Y - 1].replace(0, 2, "もう死んだはずじゃなかったのか");
	for (int i = 0; i < 7; ++i) {
		tmpfield[OP_UNUSEDCARDLIST_UP].replace(OP_UNUSEDCARDLIST_LEFT+4*i, 2, TOTRANP[i+1]);
	}
	for (int i = 7; i < 13; ++i) {
		tmpfield[OP_UNUSEDCARDLIST_UP+1].replace(OP_UNUSEDCARDLIST_LEFT+2+4*(i-7), 2, TOTRANP[i+1]);
	}
	for (int i = 0; i < 7; ++i) {
		tmpfield[MY_UNUSEDCARDLIST_UP].replace(MY_UNUSEDCARDLIST_LEFT+4*i, 2, TOTRANP[i+1]);
	}
	for (int i = 7; i < 13; ++i) {
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