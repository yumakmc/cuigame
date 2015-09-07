#include "RogueGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

using namespace roguegame;

int EndingNum=-1;//extern��RogueEnding�ɓn��
int LoveHp = 0;
int KillNum = 0;
int SpendDay=0;

namespace roguegame {
	const int LOG_LINE_Y = 20;

	const int PARTY_LEFT = 25;
	const int MY_PARTY_UP = 13;
	const int OP_PARTY_UP = 0;
	//static const int dx[4] = { -1,0,1,0 };
	//static const int dy[4] = { 0,-1,0,1 };

	const int MAP_LEFT = 2;
	const int MAP_UP = 2;
	const int SeasonNum = 4;
	const int DayPerSeason=91;

	//�h�䂵�Ă����_��������Ŋ��������l�ɂȂ�B�i�؂�̂āj
	const int DEFENDINGCUTOFF = 5;

#pragma region ENEMYMAP
	array<int, 91> SpringEnemyMap = {
		0,4,0,0,0,5,0,0,0,4,
		0,0,0,0,4,0,0,0,0,4,
		0,0,4,0,0,5,0,0,7,0,
		0,4,0,5,0,0,0,0,4,0,
		0,0,5,0,0,0,0,5,0,0,
		0,0,5,0,4,0,0,6,5,0,
		0,0,0,5,0,0,0,5,0,0,
		0,4,7,0,0,0,5,0,4,4,
		4,0,0,0,0,4,5,0,5,0,
		0,
	};
	array<int, 91> SummerEnemyMap = {
		0,8,0,8,9,8,0,0,0,0,
		0,0,0,10,0,9,0,9,0,8,
		0,0,11,0,0,9,0,0,10,0,
		0,8,0,0,0,10,0,0,8,0,
		0,0,8,0,0,0,0,9,0,0,
		0,0,9,0,8,0,10,10,0,0,
		0,0,0,10,0,0,0,9,0,0,
		0,0,11,0,0,0,9,0,0,0,
		10,0,0,11,0,8,11,0,10,0,
		0,
	};
	array<int, 91> FallEnemyMap = {
		0,4,0,4,5,4,0,0,0,0,
		0,0,0,6,0,5,0,5,0,4,
		0,0,7,0,0,5,0,0,6,0,
		0,4,0,0,0,6,0,0,4,0,
		0,0,4,0,0,0,0,5,0,0,
		0,0,5,0,4,0,6,6,0,0,
		0,0,0,6,0,0,0,5,0,0,
		0,0,7,0,0,0,5,0,0,0,
		6,0,0,7,0,4,7,0,6,0,
		0,
	};
	array<int, 91> WinterEnemyMap = {
		0,8,0,8,9,8,0,0,0,0,
		0,0,0,10,0,9,0,9,0,8,
		0,0,11,0,0,9,0,0,10,0,
		0,8,0,0,0,10,0,0,8,0,
		0,0,8,0,0,0,0,9,0,0,
		0,0,9,0,8,0,10,10,0,0,
		0,0,0,10,0,0,0,9,0,0,
		0,0,11,0,0,0,9,0,0,0,
		10,0,0,11,0,8,11,0,10,0,
		0,
	};
	array<array<int, 91>, SeasonNum> EnemyMaps = {//0:�󔒁@ �@�@4~�G
		SpringEnemyMap,
		SummerEnemyMap,
		FallEnemyMap,
		WinterEnemyMap,
	};
#pragma endregion
	enum Date {
		Thu,
		Wed,
		Tur,
		Fri,
		Sat,
		Sun,
		Mon,
	};
	enum Effect {
		E_AtkUp,
		E_sss,
		E_DefUp,
		E_ExpUp,
		E_Invin,
		E_LoveUp,
		E_Moon,
	};
	
	struct name_and_descript {
		string name;
		Effect effect;
		string descript;
	};
	static map<Date, name_and_descript> YOUBI_DETAIL = {//day0: ���j�� day1: �Ηj���ƂȂ�
		{Thu,name_and_descript{ "��",E_AtkUp,"�U���́@�Q�{" },   },
		{Wed,name_and_descript{ "��",E_sss,"���ݒ�" }, },
		{Tur,name_and_descript{ "��",E_Invin,"���G" },	  },
		{Fri,name_and_descript{ "��",E_ExpUp,"�o���l�@�Q�{" },	  },
		{Sat,name_and_descript{ "�y",E_DefUp,"�h��́@�Q�{" },			  },
		{Sun,name_and_descript{ "��",E_LoveUp,"���@�R�{" },		},
		{Mon,name_and_descript{ "��",E_Moon,"�����΂��Ă���" }	 },
	};
	static map<int, name_and_descript> CHIP_DETAIL = {//day0: ���j�� day1: �Ηj���ƂȂ�
		{ 0,name_and_descript{ "�O",E_AtkUp,"�����Ȃ��@�ł����ł��ł���" }, },
		{ 1,name_and_descript{ "��",E_AtkUp,"�����΂��Ă���" }, },
		{ 2,name_and_descript{ "��",E_AtkUp,"�h��́@�Q�{" }, },
		{ 3,name_and_descript{ "��",E_AtkUp,"�o���l�@�Q�{" }, },
		{ 4,name_and_descript{ "�~",E_AtkUp,"���G" }, },
		{ 5,name_and_descript{ "�",E_AtkUp,"���@�R�{" }, },
		{ 6,name_and_descript{ "��",E_AtkUp,"�����΂��Ă���" } },
		{ 7,name_and_descript{ "��",E_AtkUp,"���G" }, },
		{ 8,name_and_descript{ "��",E_AtkUp,"�u�������O����݂�Ȃ����܂����v" } },
		{ 9,name_and_descript{ "�t",E_AtkUp,"���ȂȂ��ŉ�����" }, },
	};
}
vector<string> *b=new vector<string>();//����������������
Situation *c = new Situation(S_Opening);

RogueGame::RogueGame(gameSceneChanger* changer) 
	:gameBaseScene(changer), abackground(0), actionlog(b),situation(c) ,myparty(PARTY_LEFT, MY_PARTY_UP,b, c),opparty(PARTY_LEFT, OP_PARTY_UP,b, c),nowplayernum(4){
	Party a(PARTY_LEFT, MY_PARTY_UP, actionlog, situation);
	myparty.AddMember(0,*this);
	opparty.AddMember(4,*this);
	

	Initialize();

	
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
	case S_TurnStart:
		////////////////////////////////////////////////
		if (EnemyMaps[season][day] >= 4) {
			
			opparty.AddMember(EnemyMaps[season][day],*this);
		}
		*situation = S_ChoosingAction;
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
	case S_ChoosingTarget://�Ώۂ�I��
		if (Keyboard_Get('X') == 1) {
			*situation = S_ChoosingAction;
			break;
		}
		for (int i = 0; i < myparty.maxmember + opparty.maxmember; ++i) {
			if (Keyboard_Get(i+48) == 1) {//
				Chara* target(GetMember(i));
				
				if (target != NULL) {
					*situation = S_ChoosingAction;//
					Act(GetMember(nowplayernum), target, nowaction);
				}
				break;
			}
		}
		break;
	case S_AllyTurn: {
		
		MyChara* nowplayer = static_cast<MyChara*>(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			nowplayer->DecideNextAction(*this);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		nowplayer->DecideNextAction(*this);
	}
		break;
	case S_EnemyTurn: {
					
		OpChara* nowplayer = static_cast<OpChara*>(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			//DecideNextAction(nowplayer);
			nowplayer->DecideNextAction(*this);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		//DecideNextAction(nowplayer);
		nowplayer->DecideNextAction(*this);
	}
		break;
	case S_TurnEnd:
		day++;
		SpendDay = day;
		if (day % DayPerSeason==0) {
			season++;
			switch (season) {
			case 0:
				assert(false);
			case 1:
				myparty.AddMember(1, *this);
			case 2:
				myparty.AddMember(2, *this);
			case 3:
				myparty.AddMember(3, *this);
			}
		}
		*situation = S_TurnStart;
		break;
	default:
		break;
	}
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
	array<int, 91> My_EnemyMap(EnemyMaps[season]);
	My_EnemyMap[day] = 9;
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 13; ++j) {
			string st = CHIP_DETAIL[My_EnemyMap[13 * i + j]].name;
			if (i % 2) {
				if (j != 12) {
					aDrawableConsole.draw(11-j + MAP_LEFT, MAP_UP + 2 * (6 - i) + 1, st);
				}
				else {
					aDrawableConsole.draw(MAP_LEFT, MAP_UP + 2 * (6 - i), st);
				}
			}
			else {
				if (j != 12) {
					aDrawableConsole.draw(j + MAP_LEFT, MAP_UP + 2 * (6 - i) + 1, st);
				}
				else {
					aDrawableConsole.draw(11 + MAP_LEFT, MAP_UP + 2 * (6 - i), st);
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
#pragma region PARTY
	myparty.Draw();
	opparty.Draw();
#pragma endregion
#pragma region COMAND

	const int ax = 14;
	const int ay = LOG_LINE_Y - 1;
	switch (*situation)
	{
		
	case S_Opening:
		aDrawableConsole.draw(ax, ay, "�y�������ăX�^�[�g");
		break;
	case S_Help:
		aDrawableConsole.draw(ax, ay, "�w���v���");
		break;
	case S_TurnStart:
		aDrawableConsole.draw(ax, ay, "�^�[���X�^�[�g");
		break;
	case S_ChoosingAction:
		aDrawableConsole.draw(ax, ay, "�s���̑I��");
		break;
	case S_ChoosingTarget:
		aDrawableConsole.draw(ax, ay, "�Ώۂ̑I��");
		break;
	case S_AllyTurn:
		aDrawableConsole.draw(ax, ay, "�����̃^�[��");
		break;
	case S_EnemyTurn:
		aDrawableConsole.draw(ax, ay, "�G�̃^�[��");
		break;
	case S_TurnEnd:
		aDrawableConsole.draw(ax, ay, "������ꂽ�B�����������B");
		break;
	default:
		assert(false);
		break;
	}
#pragma endregion	
#pragma region LOG
	
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "���O");
	auto startit = actionlog->size() <= 3 ? actionlog->begin() : actionlog->end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog->end())break;
		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, *(startit + i));
	}
	
#pragma endregion

#pragma region MANUAL

	aDrawableConsole.draw(1, LOG_LINE_Y-1, "A:�U���@D:�h��@S:��");

#pragma endregion

}
int RogueGame::Regenerate(Chara *from, Chara *to) {
	const int pluslife = max(0,min(to->max_hp-to->now_hp,(YOUBI_DETAIL[Date(day % 7)].effect==E_LoveUp) ? from->max_hp : (from->max_hp / 3)));

	to->GainLife(pluslife);
	if (from->id == 0&& DETAILS[to->id].isenemy) {//�t��from,�G��to�Ȃ�
		
		//to����Ƃ��o���l������
		static_cast<OpChara*>(to)->exp += pluslife;
		
	}
	return pluslife;
}
int RogueGame::Regenerate(const int fromnum, const int tonum) {
	Chara* from =GetMember(fromnum);
	Chara* to =GetMember(tonum);
	return Regenerate(from, to);
}

//�_���[�W��Ԃ�
int RogueGame::Attack(Chara *from, Chara *to) {
	const int dmg = CalculateDmg(from, to);
	actionlog->push_back(from->name + "�̍U���@" + to->name + "��" + Common::To_ZString(dmg)+"�̃_���[�W");
	to->GetDamage(dmg);
	if (dmg) {
		if (to->isdead&&DETAILS[to->id].isenemy) {
			KillNum++;
			int getexp = static_cast<OpChara*>(to)->exp;
			if (YOUBI_DETAIL[Date(day % 7)].effect == E_ExpUp) {
				getexp *= 2;
			}
			myparty.GainExp(getexp);
		}
	}
	return dmg;
}
//�_���[�W��Ԃ�
int RogueGame::Attack(const int fromnum, const int tonum) {
	Chara* from = GetMember(fromnum);
	Chara* to = GetMember(tonum);
	return Attack(from,to);
}
//�񕜗ʂ�Ԃ�
int RogueGame::Special(Chara *from, Chara *to) {
	//from�ɂ���ĕ���
	switch (from->id) {
	case 0: {//�t
		const int regenehp = Regenerate(from, to);
		LoveHp += regenehp;
		return regenehp;
	}
	default:
		;
	}
	return 0;
}
//�񕜗ʂ�Ԃ�
int RogueGame::Special(const int fromnum, const int tonum) {
	Chara* from = GetMember(fromnum);
	Chara* to = GetMember(tonum);
	return Special(from, to);
}
int RogueGame::Act(Chara *from,Chara *to,const ActionType type) {
	switch (type) {
		case A_Attack:
			Attack(from, to);
			break;
		case A_Defence:
			from->defending = true;
			actionlog->push_back(from->name + "�̖h��");
			break;
		case A_Special:
			actionlog->push_back(from->name + "�̓���@" + to->name + "��" + Common::To_ZString(Special(from, to)));
			break;
		case A_Nothing:
			actionlog->push_back(from->name + "�͉������Ȃ�");
			break;
		default:
			assert(false);
		}


	//���S�`�F�b�N
	CheckDeadPlayer();

	
	ChangeActMember(); //�S���I���Ȃ�������
	
	return true;
}
int RogueGame::SelectAction(const ActionType type) {
	GetMember(nowplayernum)->defending = false;//������ʉ���
	switch (type) {
	case A_Attack:
		nowaction = A_Attack;
		*situation = S_ChoosingTarget;
		break;

	case A_Defence:
		Act(GetMember(nowplayernum), GetMember(nowplayernum),A_Defence);
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
	if (YOUBI_DETAIL[Date(day % 7)].effect == (E_Invin)) {
		return 0;
	}
	else {
		int realatk = (YOUBI_DETAIL[Date(day % 7)].effect == (E_AtkUp)) ? from->atk * 2 : from->atk;
		int realdef = (YOUBI_DETAIL[Date(day % 7)].effect == (E_DefUp)) ? to->def * 2 : to->def;
		const int diff = max(0, realatk - realdef);
		return to->defending ? diff / DEFENDINGCUTOFF : diff;
	}
}
bool RogueGame::ChangeActMember() {
	bool turnendflag = false;
	while (1) {
		nowplayernum++;
		if (nowplayernum == myparty.maxmember + opparty.maxmember) {
			nowplayernum = 0;
		}

		if (nowplayernum == opparty.maxmember) {//���ׂĂ̓G�̍s�����I��������
			turnendflag = true;
			*situation = S_TurnEnd;
			return true;
		}
		if (GetMember(nowplayernum) == NULL) {
			continue;
		}
		else {
			break;
		}
	}

	if (nowplayernum < opparty.maxmember) {
		*situation = S_EnemyTurn;
	}
	else {
		if ((GetMember(nowplayernum))->controlable) {
			*situation = S_ChoosingTarget;

		}
		else {
			*situation = S_AllyTurn;
		}
	}
	
	
	return turnendflag;
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
			switch (season) {
			case 0:
				switch (amychara->id) {
				case 0:
					EndingNum = 0;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					break;
				}
			case 1:
				switch (amychara->id) {
				case 0:
					EndingNum = 1;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					EndingNum = 2;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 2:
					break;

				case 3:
					break;
				}
			case 2:
				switch (amychara->id) {
				case 0:
					EndingNum = 3;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					EndingNum = 4;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 2:
					break;

				case 3:
					break;
				}
			case 3:
				switch (amychara->id) {
				case 0:
					EndingNum = 5;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					break;
				case 2:
					break;

				case 3:
					break;
				}
			}
		}
	}
	return 0;
}

//Null���A���Ă��邱�Ƃ�����̂Œ���
Chara* RogueGame::GetMember(int num)const {
	if (num < opparty.maxmember) {
		return opparty.GetMember(num);
	}
	else if (num < opparty.maxmember + myparty.maxmember) {
		return myparty.GetMember(num - opparty.maxmember);
	}
	else {
		assert(false);
		return NULL;
	}
}

