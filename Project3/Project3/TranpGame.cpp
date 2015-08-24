#pragma once 
#include "TranpGame.h"
#include "Keyboard.h"
#include "Data_Rand.h"
#include <Windows.h>
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
const int RESULT_CARDLIST_UP = 6;

int flag = 0;//ここめちゃくちゃ頭悪いので要修正

static map<int, string> WINMARK = {
	{ 1,"○" },
	{ 0,"Δ" },
	{ -1,"×" },
};

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
		opcardorder[1] = 0;//夏だけ2がjokerに
	}
	do {
		random_shuffle(opcardorder.begin(), opcardorder.end());
	} while (opponent == 2 && (opcardorder[5] != 0&&opcardorder[4] != 0&&opcardorder[6] != 0));//夏の時はjokerが567番目にでる
	oppoint = ((opponent == 0) ? 1 : ((opponent == 1) ? 21 : -333));
	mypoint = ((opponent == 0) ? 0 : ((opponent == 1) ? -20 : -30));
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
	if (Keyboard_Get('H')==1) {
		helpmode = !helpmode;
	}
	if (helpmode) {
		if (Keyboard_Get('Z')==1|| Keyboard_Get('H') == 1) {
			helpmode = false;
		}
	}
	else {
		if (Keyboard_Get('Z')==1 || Keyboard_Get(VK_CONTROL)) {
			if (turn == 13) {
				flag = mypoint <= oppoint;
				mgameSceneChanger->ChangeScene(eGameScene_Text);
			}
		}
		for (int i = 0; i < 9; ++i) {
			if (Keyboard_Get('1' + i)==1) {
				if (!mycarduseds[i]) {
					mycarduseds[i] = true;
					mychoosenum = i + 1;
					mycardorder.push_back(i + 1);
					break;
				}
			}
		}
		if (mychoosenum == 0) {
			if (Keyboard_Get('0') == 1) {
				if (!mycarduseds[9]) {
					mycarduseds[9] = true;
					mychoosenum = 10;
					mycardorder.push_back(10);
				}
			}
			else if (Keyboard_Get('J') == 1) {
				if (!mycarduseds[10]) {
					mycarduseds[10] = true;
					mychoosenum = 11;
					mycardorder.push_back(11);
				}
			}
			else if (Keyboard_Get('Q') == 1) {
				if (!mycarduseds[11]) {
					mycarduseds[11] = true;
					mychoosenum = 12;
					mycardorder.push_back(12);
				}
			}
			else if (Keyboard_Get('K') == 1) {
				if (!mycarduseds[12]) {
					mycarduseds[12] = true;
					mychoosenum = 13;
					mycardorder.push_back(13);
				}
			}
		}
		if (mychoosenum != 0) {
			opcarduseds[opcardorder[turn] == 0 ? 1 : opcardorder[turn] - 1] = true;
			opchoosenum = opcardorder[turn];
			if (opchoosenum == 0) {
				serihunum = 1;
			}
			turn++;
			const int winner(GetWinner(mychoosenum, opchoosenum));
			if (winner == 1) {//相手勝ち
				mypoint += mychoosenum + opchoosenum + undecidedpoint;
				undecidedpoint = 0;
			}
			else if (winner == -1) {//自分勝ち
				oppoint += mychoosenum + opchoosenum + undecidedpoint;
				undecidedpoint = 0;
			}
			else {//同点
				undecidedpoint += mychoosenum + opchoosenum;
			}
		}
	}
}
void TranpGame::Draw() {
	assert(false);
}
void TranpGame::Draw(vector<string> &tmpfield) {
	if (helpmode) {
		tmpfield[0].replace(0, 18, "ーーーヘルプーーー");
		tmpfield[1].replace(0, 6, "目的：");
		tmpfield[2].replace(0, 40, "　このゲームは、相手より”強い”カードを");
		tmpfield[3].replace(0, 40, "　出すことで「日」を得ていき、最終的に相");
		tmpfield[4].replace(0, 34, "　手より多くの「日」を獲得すること");
		tmpfield[5].replace(0, 8, "ルール：");
		tmpfield[6].replace(0, 40, "　”強い”カードを出したプレイヤーが二人");
		tmpfield[7].replace(0, 40, "　の出したカードに書かれた数の合計分の「");
		tmpfield[8].replace(0, 40, "　日」を得る。同じ”強さ”の場合は「残日");
		tmpfield[9].replace(0, 40, "　」として残り、次の勝負に勝ったプレイヤ");
		tmpfield[10].replace(0, 22, "　ーが得ることができる");
		tmpfield[11].replace(0, 8, "ヒント：");
		tmpfield[12].replace(0, 40, "　こちらは相手によってハンデを背負わされ");
		tmpfield[13].replace(0, 40, "　るが、こちらには相手の次に出すカードに");
		tmpfield[14].replace(0, 40, "　書かれた数の情報という絶対的武器がある");
		tmpfield[15].replace(0, 10, "操作方法：");
		tmpfield[16].replace(0, 40, "　１、２，３、…９、０、Ｊ、Ｑ、Ｋ　を押");
		tmpfield[17].replace(0, 28, "　すと対応したカードを出す。");
		tmpfield[18].replace(0, 18, "カードの”強さ”：");
		tmpfield[19].replace(0, 40, "　２＜３＜４＜５…10＜Ｊ＜Ｑ＜Ｋ＜Ａ＜　");
	}
	else {
		switch (opponent) {
		case 0:
			switch (serihunum) {
			case 0:
				tmpfield[0].replace(0, 32, "「たたき起こされて何かと思えば」");
				//tmpfield[SIZE_Y - 1].replace(0, 32, "「たたき起こされて何かと思えば」");
				break;
			case 2:
				tmpfield[0].replace(0, 32, "「たたき起こされて何かと思えば」");
			}

			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "冬");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "春");
			break;
		case 1:
			switch (serihunum) {
			case 0:
				tmpfield[0].replace(0, 34, "「殺されたくないのなら死ねばいい」");
				break;
			case 2:
				tmpfield[0].replace(0, 32, "「意地を張ってるのはあなただけ」");
			}
			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "秋");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "春");
			break;
		case 2:
			switch (serihunum) {
			case 0:
				tmpfield[0].replace(0, 40, "「あれれ二ケ月前に殺したはずだったのに」");
				break;
			case 1:
				tmpfield[0].replace(0, 40, "「しかたないねえもう一度殺し直してやる」");
				break;
			case 2:
				tmpfield[0].replace(0, 32, "「まさか………ありえない………」");
				break;
			}

			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "夏");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "春");
			break;
		}
		if (turn == 13) {
			
			if (mypoint > oppoint) {//自分勝ったら
				serihunum = 2;
				/*tmpfield[13].replace(2, 6, "ＷＩＮ");
				tmpfield[6].replace(0, 8, "ＬＯＳＥ");*/
				tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "死");
				tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT - 2, 2, "死");
				tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT + 2, 2, "死");
				tmpfield[OP_CORE_UP - 1].replace(OP_CORE_LEFT, 2, "死");
				tmpfield[OP_CORE_UP + 1].replace(OP_CORE_LEFT, 2, "死");
			}
			else {
				/*tmpfield[6].replace(2, 6, "ＷＩＮ");
				tmpfield[13].replace(0, 8, "ＬＯＳＥ");*/
				tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "死");
				tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT - 2, 2, "死");
				tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT + 2, 2, "死");
				tmpfield[MY_CORE_UP - 1].replace(MY_CORE_LEFT, 2, "死");
				tmpfield[MY_CORE_UP + 1].replace(MY_CORE_LEFT, 2, "死");
			}
		}

		for (int i = 0; i < 13; ++i) {
			if (!opcarduseds[i]) {
				if (i < 7) {
					if (opponent == 2 && i == 1) {//夏の場合　２のかわりのジョーカー表示
						tmpfield[OP_UNUSEDCARDLIST_UP].replace(OP_UNUSEDCARDLIST_LEFT + 4 * i, 2, TOTRANP[0]);
					}
					else {
						tmpfield[OP_UNUSEDCARDLIST_UP].replace(OP_UNUSEDCARDLIST_LEFT + 4 * i, 2, TOTRANP[i + 1]);
					}
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
		tmpfield[4].replace(2, 4 + oppost.size(), "日：" + oppost);
		string mypost = To_ZenString(mypoint);
		tmpfield[15].replace(2, 4 + mypost.size(), "日：" + mypost);
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
						amark = "＜";
					}
					else  if (opcardorder[i + 1] < opcardorder[i]) {
						amark = "＞";
					}
					else {
						amark = "＝";
					}
					if (i < 7) {
						tmpfield[RESULT_CARDLIST_UP + 1].replace(RESULT_CARDLIST_LEFT + 4 * i + 2, 2, amark);
					}
					else {
						tmpfield[RESULT_CARDLIST_UP + 5].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7) + 2, 2, amark);
					}
				}
			}
			else {
				if (i < 7) {
					tmpfield[RESULT_CARDLIST_UP + 1].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, "？");
				}
				else {
					tmpfield[RESULT_CARDLIST_UP + 5].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, "？");
				}
			}
		}
		tmpfield[6].replace(0, 8, "タイトル");
		tmpfield[7].replace(2, 6, "ＥＳＣ");
		tmpfield[9].replace(2, 4, "残日");
		string ast(To_ZenString(undecidedpoint));
		tmpfield[10].replace(2, ast.size(), ast);
		tmpfield[12].replace(2, 6, "ヘルプ");
		tmpfield[13].replace(4, 2, "Ｈ");
	}
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