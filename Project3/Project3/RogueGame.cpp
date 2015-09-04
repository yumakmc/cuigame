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
	//	"��",
	//	"��",
	//	"��",
	//	"��",
	//	"�`",
	//	"�v",
	//	"�c",
	//	"�r",
	//};

	const int MAP_LEFT = 2;
	const int MAP_UP = 2;

	array<int, 91> EnemyMap = {//0:�󔒁@�@�@4~�G
		9,0,0,0,1,0,1,0,3,0,
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
	struct youbi {
		string name;
		string descript;
	};
	enum Date {
		Thu,
		Wed,
		Tur,
		Fri,
		Sat,
		Sun,
		Mon,
	};
	static map<Date,youbi> YOUBI_DETAIL = {//day0: ���j�� day1: �Ηj���ƂȂ�
		{Thu,youbi{ "��","�U���́@�Q�{" },   },
		{Wed,youbi{ "��","�����΂��Ă���" }, },
		{Tur,youbi{ "��","�h��́@�Q�{" },	  },
		{Fri,youbi{ "��","�o���l�@�Q�{" },	  },
		{Sat,youbi{ "�y","���G" },			  },
		{Sun,youbi{ "��","���@�R�{" },		},
		{Mon,youbi{ "��","�����΂��Ă���" }	 },
	};

}
vector<string> *b=new vector<string>();//����������������
Situation *c = new Situation(S_Opening);

RogueGame::RogueGame(gameSceneChanger* changer) 
	:gameBaseScene(changer), abackground(0), actionlog(b),situation(c) ,myparty(PARTY_LEFT, MY_PARTY_UP,b, c),opparty(PARTY_LEFT, OP_PARTY_UP,b, c){
	Party a(PARTY_LEFT, MY_PARTY_UP, actionlog, situation);
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
	switch (*situation) {
	case S_Opening://�X�^�[�g���
		if (Keyboard_Get('Z') == 1) {
			actionlog->push_back("�t�����܂�A�~�͎���");
			actionlog->push_back("������t�͕��ݎn�߂�");
			*situation = S_ChoosingAction;
		}
		break;
	case S_Help://�w���v
		break;
	case S_ChoosingAction://������̍U���I��	
		if (Keyboard_Get('A') == 1) {
			SelectAction(A_Attack);	
		}
		else if (Keyboard_Get('D') == 1) {
			SelectAction(A_Defence);		
		}
		else if (Keyboard_Get('S') == 1) {
			SelectAction(A_Special);
		}
		
		break;
	case S_ChoosingTarget://����̑Ώۂ�I��
		if (Keyboard_Get('X') == 1) {
			*situation = S_ChoosingAction;
			break;
		}
		for (int i = 0; i < myparty.maxmember + opparty.maxmember; ++i) {
			if (Keyboard_Get(i+48) == 1) {//
				Chara* target;
				if (opparty.maxmember > i) {
					target = opparty.GetMember(i);
				}
				else {
					target = myparty.GetMember(i - opparty.maxmember);
				}
				if (target != NULL) {
					*situation = S_ChoosingAction;//
					Act(myparty.GetMember(nowplayernum), target, nowaction);
				}
				
				break;
			}
		}
		break;
	case S_OtherTurn://����̑Ώۂ�I��
		//���̃^�[���̍s�������B
		
		*situation = S_TurnEnd;
		break;
	case S_TurnEnd://����̑Ώۂ�I��
		day++;
		*situation = S_ChoosingAction;
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
	aDrawableConsole.draw(4, 0, "�G��");
	
	vector<int> AliveId(myparty.GetAliveMemberId());
	for (int i = 0; i < 4; ++i) {
		if (find(AliveId.begin(), AliveId.end(), i) != AliveId.end()) {
			aDrawableConsole.draw(1 + 2 * i, 1, DETAILS[i].name.c_str());
		}
	}
	aDrawableConsole.draw(7, 0, Common::To_ZString(day)+"��/365��");
	aDrawableConsole.draw(13, 0, YOUBI_DETAIL[Date(day%7)].name + "�j���F"+YOUBI_DETAIL[Date(day % 7)].descript);
	
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
	
	switch (*situation)
	{
	case S_Opening:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "�y�@�������ăX�^�[�g");
		break;
	case S_Help:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "�w���v���");
		break;
	case S_ChoosingAction:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "�s����I������");
		break;
	case S_ChoosingTarget:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "�G�̒�����Ώۂ�I������");
		break;
	case S_ChoosingMy:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "�����̒�����Ώۂ�I������");
		break;
	case S_OtherTurn:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "����̃^�[��");
		break;
	case S_TurnEnd:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "������ꂽ�B�����������B");
		break;
	default:
		assert(false);
		break;
	}

#pragma region LOG
	
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "���O");
	auto startit = actionlog->size() <= 3 ? actionlog->begin() : actionlog->end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog->end())break;
		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, *(startit + i));
	}
	
#pragma endregion
}
int RogueGame::Regenerate(Chara *from, Chara *to) {
	const int pluslife = max(0,min(to->max_hp-to->now_hp,(day % 7 == Sun) ? from->max_hp / 2 * 3 : (from->max_hp / 2)));
	if (from->id == 0&& DETAILS[to->id].isenemy) {//�t��from,�G��to�Ȃ�
		to->GainLife(pluslife);
		//to����Ƃ��o���l������
	}else {
		to->GainLife(pluslife);
	}
	return pluslife;
}
int RogueGame::Regenerate(const int fromnum, const int tonum) {
	Chara* from = fromnum >= 4 ? myparty.GetMember(fromnum - 4) : opparty.GetMember(fromnum);
	Chara* to = tonum >= 4 ? myparty.GetMember(tonum - 4) : opparty.GetMember(tonum);
	return Regenerate(from, to);
}
bool RogueGame::Attack(Chara *from, Chara *to) {
	if (to->GetDamage(CalculateDmg(from,to))) {
		if (!DETAILS[from->id].isenemy) {
			MyChara *a = static_cast<MyChara*>(from);
			a->GainExp(777);
		}
		return true;//////////////
	}
	return false;
}
bool RogueGame::Attack(const int fromnum, const int tonum) {
	Chara* from = fromnum >= 4 ? myparty.GetMember(fromnum - 4) : opparty.GetMember(fromnum);
	Chara* to = tonum >= 4 ? myparty.GetMember(tonum - 4) : opparty.GetMember(tonum);
	return Attack(from,to);
}
bool RogueGame::Special(Chara *from, Chara *to) {
	//from�ɂ���ĕ���
	switch (from->id) {
	case 0://�t
		Regenerate(from, to);//�t��

		break;
	default:
		;
	}
	return false;
}
bool RogueGame::Special(const int fromnum, const int tonum) {
	Chara* from = fromnum >= 4 ? myparty.GetMember(fromnum - 4) : opparty.GetMember(fromnum);
	Chara* to = tonum >= 4 ? myparty.GetMember(tonum - 4) : opparty.GetMember(tonum);
	return Special(from, to);
}
int RogueGame::Act(Chara *from,Chara *to,const Action type) {
	switch (type) {
		case A_Attack:
			Attack(from, to);
			actionlog->push_back(from->name + "�̍U��"+ to->name);
			break;
		case A_Defence:
			from->defending = true;
			actionlog->push_back(from->name + "�̖h��" + to->name);
			break;
		case A_Special:
			Special(from, to);
			actionlog->push_back(from->name + "�̓���" + to->name);
			break;
		default:
			assert(false);
		}


	//���S�`�F�b�N
	CheckDeadPlayer();

	//��l��������ł��Ȃ��Ƃ����O�񂠂�
	
	if (ChooseNextPlayer()) {//�S���I���Ȃ�������
		assert(false);//���̂Ƃ�����͂��Ȃ�
		*situation = S_ChoosingAction;
	}
	else {
		*situation = S_OtherTurn;
	}
	return true;
}
int RogueGame::SelectAction(const Action type) {
	myparty.GetMember(nowplayernum)->defending = false;//������ʉ���
	switch (type) {
	case A_Attack:
		nowaction = A_Attack;
		*situation = S_ChoosingTarget;
		break;

	case A_Defence:
		Act(myparty.GetMember(nowplayernum), myparty.GetMember(nowplayernum),A_Defence);
		break;

	case A_Special:
		nowaction = A_Special;
		*situation = S_ChoosingTarget;
		break;

	default:
		assert(false);
	}
	return true;
}
inline int RogueGame::CalculateDmg(const Chara *from,const Chara *to) {
	if ((Date(day % 7) == (Sat))) {
		return 0;
	}
	else {
		int realatk = (Date(day % 7) == (Thu)) ? from->atk * 2 : from->atk;
		int realdef = (Date(day % 7) == (Tur)) ? to->def * 2 : to->def;
		const int diff = max(0, realatk - realdef);
		return to->defending ? diff / 4 : diff;
	}
}
bool RogueGame::ChooseNextPlayer() {
	bool flag = false;
	for (int i = nowplayernum + 1; i < myparty.maxmember; ++i) {
		if (myparty.GetMember(i) == NULL) { break; }
		if (!DETAILS[myparty.GetMember(i)->id].isenemy && (static_cast<MyChara*> (myparty.GetMember(i)))->controlable) {
			nowplayernum = i;
			flag = true;
		}
	}
	return flag;
}
int RogueGame::CheckDeadPlayer() {
	for (int i = 0; i < opparty.maxmember; ++i) {
		Chara* aopchara = opparty.GetMember(i);
		if (aopchara != NULL&&aopchara->isdead) {
			opparty.DeleteMember(i);
		}
	}
	for (int i = 0; i < myparty.maxmember; ++i) {
		Chara* amychara = myparty.GetMember(i);
		if (amychara != NULL&&amychara->isdead) {
			//�G���f�B���O���肵����
		}
	}
	return 0;
}
