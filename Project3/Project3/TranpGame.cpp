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

int flag = 0;//�����߂��Ⴍ���ᓪ�����̂ŗv�C��

static map<int, string> WINMARK = {
	{ 1,"��" },
	{ 0,"��" },
	{ -1,"�~" },
};

static map<int, string> TOTRANP = {
	{ 1,"�`"},
	{ 2,"�Q" },
	{ 3,"�R" },
	{ 4,"�S" },
	{ 5,"�T" },
	{ 6,"�U" },
	{ 7,"�V" },
	{ 8,"�W" },
	{ 9,"�X" },
	{ 10,"10" },
	{ 11,"�i" },
	{ 12,"�p" },
	{ 13,"�j" },
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
		opcardorder[1] = 0;//�Ă���2��joker��
	}
	do {
		random_shuffle(opcardorder.begin(), opcardorder.end());
	} while (opponent == 2 && (opcardorder[5] != 0&&opcardorder[4] != 0&&opcardorder[6] != 0));//�Ă̎���joker��567�Ԗڂɂł�
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
			if (winner == 1) {//���菟��
				mypoint += mychoosenum + opchoosenum + undecidedpoint;
				undecidedpoint = 0;
			}
			else if (winner == -1) {//��������
				oppoint += mychoosenum + opchoosenum + undecidedpoint;
				undecidedpoint = 0;
			}
			else {//���_
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
		tmpfield[0].replace(0, 18, "�[�[�[�w���v�[�[�[");
		tmpfield[1].replace(0, 6, "�ړI�F");
		tmpfield[2].replace(0, 40, "�@���̃Q�[���́A������h�����h�J�[�h��");
		tmpfield[3].replace(0, 40, "�@�o�����ƂŁu���v�𓾂Ă����A�ŏI�I�ɑ�");
		tmpfield[4].replace(0, 34, "�@���葽���́u���v���l�����邱��");
		tmpfield[5].replace(0, 8, "���[���F");
		tmpfield[6].replace(0, 40, "�@�h�����h�J�[�h���o�����v���C���[����l");
		tmpfield[7].replace(0, 40, "�@�̏o�����J�[�h�ɏ����ꂽ���̍��v���́u");
		tmpfield[8].replace(0, 40, "�@���v�𓾂�B�����h�����h�̏ꍇ�́u�c��");
		tmpfield[9].replace(0, 40, "�@�v�Ƃ��Ďc��A���̏����ɏ������v���C��");
		tmpfield[10].replace(0, 22, "�@�[�����邱�Ƃ��ł���");
		tmpfield[11].replace(0, 8, "�q���g�F");
		tmpfield[12].replace(0, 40, "�@������͑���ɂ���ăn���f��w���킳��");
		tmpfield[13].replace(0, 40, "�@�邪�A������ɂ͑���̎��ɏo���J�[�h��");
		tmpfield[14].replace(0, 40, "�@�����ꂽ���̏��Ƃ�����ΓI���킪����");
		tmpfield[15].replace(0, 10, "������@�F");
		tmpfield[16].replace(0, 40, "�@�P�A�Q�C�R�A�c�X�A�O�A�i�A�p�A�j�@����");
		tmpfield[17].replace(0, 28, "�@���ƑΉ������J�[�h���o���B");
		tmpfield[18].replace(0, 18, "�J�[�h�́h�����h�F");
		tmpfield[19].replace(0, 40, "�@�Q���R���S���T�c10���i���p���j���`���@");
	}
	else {
		switch (opponent) {
		case 0:
			switch (serihunum) {
			case 0:
				tmpfield[0].replace(0, 32, "�u�������N������ĉ����Ǝv���΁v");
				//tmpfield[SIZE_Y - 1].replace(0, 32, "�u�������N������ĉ����Ǝv���΁v");
				break;
			case 2:
				tmpfield[0].replace(0, 32, "�u�������N������ĉ����Ǝv���΁v");
			}

			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "�~");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "�t");
			break;
		case 1:
			switch (serihunum) {
			case 0:
				tmpfield[0].replace(0, 34, "�u�E���ꂽ���Ȃ��̂Ȃ玀�˂΂����v");
				break;
			case 2:
				tmpfield[0].replace(0, 32, "�u�Ӓn�𒣂��Ă�̂͂��Ȃ������v");
			}
			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "�H");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "�t");
			break;
		case 2:
			switch (serihunum) {
			case 0:
				tmpfield[0].replace(0, 40, "�u������P���O�ɎE�����͂��������̂Ɂv");
				break;
			case 1:
				tmpfield[0].replace(0, 40, "�u�������Ȃ��˂�������x�E�������Ă��v");
				break;
			case 2:
				tmpfield[0].replace(0, 32, "�u�܂����c�c�c���肦�Ȃ��c�c�c�v");
				break;
			}

			tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "��");
			tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "�t");
			break;
		}
		if (turn == 13) {
			
			if (mypoint > oppoint) {//������������
				serihunum = 2;
				/*tmpfield[13].replace(2, 6, "�v�h�m");
				tmpfield[6].replace(0, 8, "�k�n�r�d");*/
				tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT, 2, "��");
				tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT - 2, 2, "��");
				tmpfield[OP_CORE_UP].replace(OP_CORE_LEFT + 2, 2, "��");
				tmpfield[OP_CORE_UP - 1].replace(OP_CORE_LEFT, 2, "��");
				tmpfield[OP_CORE_UP + 1].replace(OP_CORE_LEFT, 2, "��");
			}
			else {
				/*tmpfield[6].replace(2, 6, "�v�h�m");
				tmpfield[13].replace(0, 8, "�k�n�r�d");*/
				tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT, 2, "��");
				tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT - 2, 2, "��");
				tmpfield[MY_CORE_UP].replace(MY_CORE_LEFT + 2, 2, "��");
				tmpfield[MY_CORE_UP - 1].replace(MY_CORE_LEFT, 2, "��");
				tmpfield[MY_CORE_UP + 1].replace(MY_CORE_LEFT, 2, "��");
			}
		}

		for (int i = 0; i < 13; ++i) {
			if (!opcarduseds[i]) {
				if (i < 7) {
					if (opponent == 2 && i == 1) {//�Ă̏ꍇ�@�Q�̂����̃W���[�J�[�\��
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
		tmpfield[4].replace(2, 4 + oppost.size(), "���F" + oppost);
		string mypost = To_ZenString(mypoint);
		tmpfield[15].replace(2, 4 + mypost.size(), "���F" + mypost);
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
						amark = "��";
					}
					else  if (opcardorder[i + 1] < opcardorder[i]) {
						amark = "��";
					}
					else {
						amark = "��";
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
					tmpfield[RESULT_CARDLIST_UP + 1].replace(RESULT_CARDLIST_LEFT + 4 * i, 2, "�H");
				}
				else {
					tmpfield[RESULT_CARDLIST_UP + 5].replace(RESULT_CARDLIST_LEFT + 2 + 4 * (i - 7), 2, "�H");
				}
			}
		}
		tmpfield[6].replace(0, 8, "�^�C�g��");
		tmpfield[7].replace(2, 6, "�d�r�b");
		tmpfield[9].replace(2, 4, "�c��");
		string ast(To_ZenString(undecidedpoint));
		tmpfield[10].replace(2, ast.size(), ast);
		tmpfield[12].replace(2, 6, "�w���v");
		tmpfield[13].replace(4, 2, "�g");
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