#include "RogueGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

using namespace roguegame;

int EndingNum=-1;//extern‚ÅRogueEnding‚É“n‚·

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

	array<int, 91> EnemyMap = {//0:‹ó”’@ @@4~“G
		0,4,0,4,5,4,5,0,7,0,
		0,0,0,6,0,5,0,5,0,4,
		0,0,7,0,0,5,0,0,6,0,
		0,0,0,0,0,6,0,0,0,0,
		0,0,4,0,0,0,0,5,0,0,
		0,0,5,0,4,0,6,0,0,0,
		0,0,0,6,0,0,0,5,0,0,
		0,0,7,0,0,0,5,0,0,0,
		6,0,0,7,0,4,7,0,6,0,
		0,
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
	static map<Date, name_and_descript> YOUBI_DETAIL = {//day0: Œ—j“ú day1: ‰Î—j“ú‚Æ‚È‚é
		{Thu,name_and_descript{ "‰Î",E_AtkUp,"UŒ‚—Í@‚Q”{" },   },
		{Wed,name_and_descript{ "…",E_sss,"Œ‚ªÎ‚Á‚Ä‚¢‚é" }, },
		{Tur,name_and_descript{ "–Ø",E_DefUp,"–hŒä—Í@‚Q”{" },	  },
		{Fri,name_and_descript{ "‹à",E_ExpUp,"ŒoŒ±’l@‚Q”{" },	  },
		{Sat,name_and_descript{ "“y",E_Invin,"–³“G" },			  },
		{Sun,name_and_descript{ "“ú",E_LoveUp,"ˆ¤@‚R”{" },		},
		{Mon,name_and_descript{ "Œ",E_Moon,"Œ‚ªÎ‚Á‚Ä‚¢‚é" }	 },
	};
	static map<int, name_and_descript> CHIP_DETAIL = {//day0: Œ—j“ú day1: ‰Î—j“ú‚Æ‚È‚é
		{ 0,name_and_descript{ "–³",E_AtkUp,"‰½‚à‚È‚¢@‚Å‚à‰½‚Å‚à‚Å‚«‚é" }, },
		{ 1,name_and_descript{ "‚ ",E_AtkUp,"Œ‚ªÎ‚Á‚Ä‚¢‚é" }, },
		{ 2,name_and_descript{ "‚¢",E_AtkUp,"–hŒä—Í@‚Q”{" }, },
		{ 3,name_and_descript{ "‚¤",E_AtkUp,"ŒoŒ±’l@‚Q”{" }, },
		{ 4,name_and_descript{ "‚S",E_AtkUp,"–³“G" }, },
		{ 5,name_and_descript{ "‚T",E_AtkUp,"ˆ¤@‚R”{" }, },
		{ 6,name_and_descript{ "‚U",E_AtkUp,"Œ‚ªÎ‚Á‚Ä‚¢‚é" } },
		{ 7,name_and_descript{ "‚V",E_AtkUp,"–³“G" }, },
		{ 8,name_and_descript{ "Œ",E_AtkUp,"u‰´‚à‚¨‘O‚ç‚à‚İ‚ñ‚È‚¨‚µ‚Ü‚¢‚¾v" } },
		{ 9,name_and_descript{ "t",E_AtkUp,"€‚È‚È‚¢‚Å‰º‚³‚¢" }, },
	};

}
vector<string> *b=new vector<string>();//‚±‚±‰˜‚¢’¼‚µ‚½‚¢
Situation *c = new Situation(S_Opening);

RogueGame::RogueGame(gameSceneChanger* changer) 
	:gameBaseScene(changer), abackground(0), actionlog(b),situation(c) ,myparty(PARTY_LEFT, MY_PARTY_UP,b, c),opparty(PARTY_LEFT, OP_PARTY_UP,b, c),nowplayernum(4){
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
	case S_Opening://ƒXƒ^[ƒg‰æ–Ê
		if (Keyboard_Get('Z') == 1) {
			actionlog->push_back("t‚ª¶‚Ü‚êA“~‚Í€‚ñ‚¾");
			actionlog->push_back("‚¾‚©‚çt‚Í•à‚İn‚ß‚é");
			*situation = S_ChoosingAction;
		}
		break;
	case S_Help://ƒwƒ‹ƒv
		break;
	case S_TurnStart:
		////////////////////////////////////////////////
		if (EnemyMap[day] >= 4) {
			opparty.AddMember(EnemyMap[day]);
		}
		*situation = S_ChoosingAction;
		break;

	case S_ChoosingAction://‚±‚¿‚ç‚ÌUŒ‚‘I‘ğ’†	
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
	case S_ChoosingTarget://‘Šè‚Ì‘ÎÛ‚ğ‘I‘ğ’†
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
	case S_AllyTurn: {//‘Šè‚Ì‘ÎÛ‚ğ‘I‘ğ’†
		//‘¼‚Ìƒ^[ƒ“‚Ìs“®“ü‚ê‚éB
		MyChara* nowplayer = static_cast<MyChara*>(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			DecideNextAction(nowplayer);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		DecideNextAction(nowplayer);
	}
		break;
	case S_EnemyTurn: {//‘Šè‚Ì‘ÎÛ‚ğ‘I‘ğ’†
					//‘¼‚Ìƒ^[ƒ“‚Ìs“®“ü‚ê‚éB
		Chara* nowplayer(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			DecideNextAction(nowplayer);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		DecideNextAction(nowplayer);
	}
		break;
	case S_TurnEnd://‘Šè‚Ì‘ÎÛ‚ğ‘I‘ğ’†
		day++;
		*situation = S_TurnStart;
		break;
	default:
		break;
	}

	
}
void RogueGame::Draw() {
#pragma region BACK
	abackground.Draw();
	aDrawableConsole.draw(4, 0, "‹Gß");
	
	vector<int> AliveId(myparty.GetAliveMemberId());
	for (int i = 0; i < 4; ++i) {
		if (find(AliveId.begin(), AliveId.end(), i) != AliveId.end()) {
			aDrawableConsole.draw(1 + 2 * i, 1, DETAILS[i].name.c_str());
		}
	}
	aDrawableConsole.draw(7, 0, Common::To_ZString(day)+"“ú/365“ú");
	aDrawableConsole.draw(13, 0, YOUBI_DETAIL[Date(day%7)].name + "—j“úF"+YOUBI_DETAIL[Date(day % 7)].descript);
	
#pragma endregion
	
#pragma region MAP
	array<int, 91> My_EnemyMap(EnemyMap);
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

	myparty.Draw();
	opparty.Draw();
	
	switch (*situation)
	{
	case S_Opening:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "‚y@‚ğ‰Ÿ‚µ‚ÄƒXƒ^[ƒg");
		break;
	case S_Help:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ƒwƒ‹ƒv‰æ–Ê");
		break;
	case S_TurnStart:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ƒ^[ƒ“ƒXƒ^[ƒg");
		break;
	case S_ChoosingAction:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "s“®‚ğ‘I‘ğ‚¹‚æ");
		break;
	case S_ChoosingTarget:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "“G‚Ì’†‚©‚ç‘ÎÛ‚ğ‘I‘ğ‚¹‚æ");
		break;
	case S_AllyTurn:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "–¡•û‚Ìƒ^[ƒ“");
		break;
	case S_EnemyTurn:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "“G‚Ìƒ^[ƒ“");
		break;
	case S_TurnEnd:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "“ú‚ª•é‚ê‚½B“ú‚ª–¾‚¯‚½B");
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
	
#pragma endregion
}
int RogueGame::Regenerate(Chara *from, Chara *to) {
	const int pluslife = max(0,min(to->max_hp-to->now_hp,(day % 7 == Sun) ? from->max_hp / 2 * 3 : (from->max_hp / 2)));
	if (from->id == 0&& DETAILS[to->id].isenemy) {//t‚ªfrom,“G‚ªto‚È‚ç
		to->GainLife(pluslife);
		//to‚©‚ç‚Æ‚ê‚éŒoŒ±’l‘‚¦‚é
	}else {
		to->GainLife(pluslife);
	}
	return pluslife;
}
int RogueGame::Regenerate(const int fromnum, const int tonum) {
	Chara* from =GetMember(fromnum);
	Chara* to =GetMember(tonum);
	return Regenerate(from, to);
}

//ƒ_ƒ[ƒW‚ğ•Ô‚·
int RogueGame::Attack(Chara *from, Chara *to) {
	const int dmg = CalculateDmg(from, to);
	to->GetDamage(dmg);
	if (dmg) {
		if (!DETAILS[from->id].isenemy) {
			MyChara *a = static_cast<MyChara*>(from);
			a->GainExp(777);
		}
		return dmg;//////////////
	}
	return dmg;
}
//ƒ_ƒ[ƒW‚ğ•Ô‚·
int RogueGame::Attack(const int fromnum, const int tonum) {
	Chara* from = GetMember(fromnum);
	Chara* to = GetMember(tonum);
	return Attack(from,to);
}
//‰ñ•œ—Ê‚ğ•Ô‚·
int RogueGame::Special(Chara *from, Chara *to) {
	//from‚É‚æ‚Á‚Ä•ªŠò
	switch (from->id) {
	case 0://t
		return Regenerate(from, to);//t‚Í

	default:
		;
	}
	return 0;
}
//‰ñ•œ—Ê‚ğ•Ô‚·
int RogueGame::Special(const int fromnum, const int tonum) {
	Chara* from = GetMember(fromnum);
	Chara* to = GetMember(tonum);
	return Special(from, to);
}
int RogueGame::Act(Chara *from,Chara *to,const ActionType type) {
	switch (type) {
		case A_Attack:
			actionlog->push_back(from->name + "‚ÌUŒ‚@" + to->name + "‚É" + Common::To_ZString(Attack(from, to)));
			break;
		case A_Defence:
			from->defending = true;
			actionlog->push_back(from->name + "‚Ì–hŒä@" + to->name);
			break;
		case A_Special:
			Special(from, to);
			actionlog->push_back(from->name + "‚Ì“Áê@" + to->name + "‚É" + Common::To_ZString(Special(from, to)));
			break;
		case A_Nothing:
			actionlog->push_back(from->name + "‚Í‰½‚à‚µ‚È‚¢");
			break;
		default:
			assert(false);
		}


	//€–Sƒ`ƒFƒbƒN
	CheckDeadPlayer();

	//ˆêl‚µ‚©‘€ì‚Å‚«‚È‚¢‚Æ‚¢‚¤‘O’ñ‚ ‚è
	
	ChangeActMember(); //‘SˆõI‚í‚ç‚È‚©‚Á‚½‚ç
	
	return true;
}
int RogueGame::SelectAction(const ActionType type) {
	GetMember(nowplayernum)->defending = false;//“ÁêŒø‰Ê‰ğœ
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
		return to->defending ? diff / 4 : diff;
	}
}
bool RogueGame::ChangeActMember() {
	bool turnendflag = false;
	while (1) {
		nowplayernum++;
		if (nowplayernum == myparty.maxmember + opparty.maxmember) {
			nowplayernum = 0;
		}

		if (nowplayernum == opparty.maxmember) {//‚·‚×‚Ä‚Ì“G‚Ìs“®‚ªI—¹‚µ‚½‚ç
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
			//ƒGƒ“ƒfƒBƒ“ƒO”»’è‚µ‚½‚¢
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

//Null‚ª‹A‚Á‚Ä‚­‚é‚±‚Æ‚à‚ ‚é‚Ì‚Å’ˆÓ
Chara* RogueGame::GetMember(int num) {
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
ActionInfo RogueGame::DecideNextAction(Chara* chara) {//‰½‚à‚µ‚È‚¢‚È‚ç‚O‚ğ•Ô‚·
	bool flag = false;
	int nexttargetnum = chara->nextActionInfo.targetnum;
	ActionType nextaction = A_Attack;
	switch (chara->ai) {
	case Ai_AttackEnemy: 
	{
		if (nexttargetnum >= opparty.maxmember) {//ai•Ï‚í‚Á‚½‚Æ‚«‚æ‚¤@ã‚©‚çUŒ‚
			nexttargetnum = -1;
		}
		for (int i = 0; i < opparty.maxmember; ++i) {
			nexttargetnum++;
			if (nexttargetnum == opparty.maxmember) {
				nexttargetnum = 0;
			}
			if (GetMember(nexttargetnum) == NULL) {
				continue;
			}
			else {
				chara->nextActionInfo = {
					nexttargetnum,nextaction
				};
				return{ chara->nextActionInfo };
			}
			
		}
		chara->nextActionInfo = {
			-1,A_Nothing
		};
		return{ chara->nextActionInfo };//UŒ‚‚µ‚È‚¢
	}
			break;
	case Ai_AttackMy:
	{
		if (nexttargetnum < opparty.maxmember) {//ai•Ï‚í‚Á‚½‚Æ‚«‚æ‚¤@ã‚©‚çUŒ‚
			nexttargetnum = opparty.maxmember-1;
		}
		for (int i = 0; i < 4; ++i) {
			nexttargetnum++;
			if (nexttargetnum == opparty.maxmember+myparty.maxmember) {
				nexttargetnum = 4;
			}
			if (GetMember(nexttargetnum) == NULL) {
				continue;
			}
			else {
				chara->nextActionInfo = {
					nexttargetnum,nextaction
				};
				return{ chara->nextActionInfo };
			}
		}
		chara->nextActionInfo = {
			-1,A_Nothing
		};
		return{ chara->nextActionInfo };//UŒ‚‚µ‚È‚¢
	}
		break;
	case Ai_AttackSpring: //id0‚ªt‚Æ‚¢‚¤‘O’ñ
	{
		for (int i = 0; i < myparty.maxmember; ++i) {
			
			if (GetMember(opparty.maxmember + i) != NULL&&GetMember(opparty.maxmember + i)->id==0) {
				chara->nextActionInfo = {
					opparty.maxmember + i,nextaction
				};
				return{ chara->nextActionInfo };
			}
		}
		chara->nextActionInfo = {
			-1,A_Nothing
		};
		return{ chara->nextActionInfo };//UŒ‚‚µ‚È‚¢
	}

		break;
	case Ai_AttackSummer:
	{
		for (int i = 0; i < myparty.maxmember; ++i) {
			if (GetMember(opparty.maxmember + i) != NULL&&GetMember(opparty.maxmember + i)->id == 1) {
				chara->nextActionInfo = {
					opparty.maxmember + i,nextaction
				};
				return{ chara->nextActionInfo };
			}
		}
		chara->nextActionInfo = {
			-1,A_Nothing
		};
		return{ chara->nextActionInfo };//UŒ‚‚µ‚È‚¢
	}
		break;
	case Ai_AttackFall:
	{
		for (int i = 0; i < myparty.maxmember; ++i) {

			if (GetMember(opparty.maxmember + i) != NULL&&GetMember(opparty.maxmember + i)->id == 2) {
				chara->nextActionInfo = {
					opparty.maxmember + i,nextaction
				};
				return{ chara->nextActionInfo };
			}
		}
		chara->nextActionInfo = {
			-1,A_Nothing
		};
		return{ chara->nextActionInfo };//UŒ‚‚µ‚È‚¢
	}
	}
	chara->nextActionInfo = {
		-1,A_Nothing
	};
	return{ chara->nextActionInfo };//UŒ‚‚µ‚È‚¢
}
ActionInfo RogueGame::DecideNextAction(const int num) {
	Chara* chara(GetMember(num));
	return DecideNextAction(chara);
}
