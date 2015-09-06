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
	//	"←",
	//	"↑",
	//	"→",
	//	"↓",
	//	"Ａ",
	//	"Ｗ",
	//	"Ｄ",
	//	"Ｓ",
	//};

	const int MAP_LEFT = 2;
	const int MAP_UP = 2;

	array<int, 91> EnemyMap = {//0:空白　 　　4~敵
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
	static map<Date, name_and_descript> YOUBI_DETAIL = {//day0: 月曜日 day1: 火曜日となる
		{Thu,name_and_descript{ "火",E_AtkUp,"攻撃力　２倍" },   },
		{Wed,name_and_descript{ "水",E_sss,"月が笑っている" }, },
		{Tur,name_and_descript{ "木",E_DefUp,"防御力　２倍" },	  },
		{Fri,name_and_descript{ "金",E_ExpUp,"経験値　２倍" },	  },
		{Sat,name_and_descript{ "土",E_Invin,"無敵" },			  },
		{Sun,name_and_descript{ "日",E_LoveUp,"愛　３倍" },		},
		{Mon,name_and_descript{ "月",E_Moon,"月が笑っている" }	 },
	};
	static map<int, name_and_descript> CHIP_DETAIL = {//day0: 月曜日 day1: 火曜日となる
		{ 0,name_and_descript{ "無",E_AtkUp,"何もない　でも何でもできる" }, },
		{ 1,name_and_descript{ "あ",E_AtkUp,"月が笑っている" }, },
		{ 2,name_and_descript{ "い",E_AtkUp,"防御力　２倍" }, },
		{ 3,name_and_descript{ "う",E_AtkUp,"経験値　２倍" }, },
		{ 4,name_and_descript{ "４",E_AtkUp,"無敵" }, },
		{ 5,name_and_descript{ "５",E_AtkUp,"愛　３倍" }, },
		{ 6,name_and_descript{ "６",E_AtkUp,"月が笑っている" } },
		{ 7,name_and_descript{ "７",E_AtkUp,"無敵" }, },
		{ 8,name_and_descript{ "月",E_AtkUp,"「俺もお前らもみんなおしまいだ」" } },
		{ 9,name_and_descript{ "春",E_AtkUp,"死なないで下さい" }, },
	};

}
vector<string> *b=new vector<string>();//ここ汚い直したい
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
	case S_Opening://スタート画面
		if (Keyboard_Get('Z') == 1) {
			actionlog->push_back("春が生まれ、冬は死んだ");
			actionlog->push_back("だから春は歩み始める");
			*situation = S_ChoosingAction;
		}
		break;
	case S_Help://ヘルプ
		break;
	case S_TurnStart:
		////////////////////////////////////////////////
		if (EnemyMap[day] >= 4) {
			opparty.AddMember(EnemyMap[day]);
		}
		*situation = S_ChoosingAction;
		break;

	case S_ChoosingAction://こちらの攻撃選択中	
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
	case S_ChoosingTarget://相手の対象を選択中
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
	case S_AllyTurn: {//相手の対象を選択中
		//他のターンの行動入れる。
		MyChara* nowplayer = static_cast<MyChara*>(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			DecideNextAction(nowplayer);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		DecideNextAction(nowplayer);
	}
		break;
	case S_EnemyTurn: {//相手の対象を選択中
					//他のターンの行動入れる。
		Chara* nowplayer(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			DecideNextAction(nowplayer);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		DecideNextAction(nowplayer);
	}
		break;
	case S_TurnEnd://相手の対象を選択中
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
	aDrawableConsole.draw(4, 0, "季節");
	
	vector<int> AliveId(myparty.GetAliveMemberId());
	for (int i = 0; i < 4; ++i) {
		if (find(AliveId.begin(), AliveId.end(), i) != AliveId.end()) {
			aDrawableConsole.draw(1 + 2 * i, 1, DETAILS[i].name.c_str());
		}
	}
	aDrawableConsole.draw(7, 0, Common::To_ZString(day)+"日/365日");
	aDrawableConsole.draw(13, 0, YOUBI_DETAIL[Date(day%7)].name + "曜日："+YOUBI_DETAIL[Date(day % 7)].descript);
	
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
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "Ｚ　を押してスタート");
		break;
	case S_Help:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ヘルプ画面");
		break;
	case S_TurnStart:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "ターンスタート");
		break;
	case S_ChoosingAction:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "行動を選択せよ");
		break;
	case S_ChoosingTarget:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "敵の中から対象を選択せよ");
		break;
	case S_AllyTurn:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "味方のターン");
		break;
	case S_EnemyTurn:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "敵のターン");
		break;
	case S_TurnEnd:
		aDrawableConsole.draw(16, LOG_LINE_Y + 2, "日が暮れた。日が明けた。");
		break;
	default:
		assert(false);
		break;
	}

#pragma region LOG
	
	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "ログ");
	auto startit = actionlog->size() <= 3 ? actionlog->begin() : actionlog->end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog->end())break;
		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, *(startit + i));
	}
	
#pragma endregion
}
int RogueGame::Regenerate(Chara *from, Chara *to) {
	const int pluslife = max(0,min(to->max_hp-to->now_hp,(day % 7 == Sun) ? from->max_hp / 2 * 3 : (from->max_hp / 2)));
	if (from->id == 0&& DETAILS[to->id].isenemy) {//春がfrom,敵がtoなら
		to->GainLife(pluslife);
		//toからとれる経験値増える
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

//ダメージを返す
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
//ダメージを返す
int RogueGame::Attack(const int fromnum, const int tonum) {
	Chara* from = GetMember(fromnum);
	Chara* to = GetMember(tonum);
	return Attack(from,to);
}
//回復量を返す
int RogueGame::Special(Chara *from, Chara *to) {
	//fromによって分岐
	switch (from->id) {
	case 0://春
		return Regenerate(from, to);//春は

	default:
		;
	}
	return 0;
}
//回復量を返す
int RogueGame::Special(const int fromnum, const int tonum) {
	Chara* from = GetMember(fromnum);
	Chara* to = GetMember(tonum);
	return Special(from, to);
}
int RogueGame::Act(Chara *from,Chara *to,const ActionType type) {
	switch (type) {
		case A_Attack:
			actionlog->push_back(from->name + "の攻撃　" + to->name + "に" + Common::To_ZString(Attack(from, to)));
			break;
		case A_Defence:
			from->defending = true;
			actionlog->push_back(from->name + "の防御　" + to->name);
			break;
		case A_Special:
			Special(from, to);
			actionlog->push_back(from->name + "の特殊　" + to->name + "に" + Common::To_ZString(Special(from, to)));
			break;
		case A_Nothing:
			actionlog->push_back(from->name + "は何もしない");
			break;
		default:
			assert(false);
		}


	//死亡チェック
	CheckDeadPlayer();

	//一人しか操作できないという前提あり
	
	ChangeActMember(); //全員終わらなかったら
	
	return true;
}
int RogueGame::SelectAction(const ActionType type) {
	GetMember(nowplayernum)->defending = false;//特殊効果解除
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

		if (nowplayernum == opparty.maxmember) {//すべての敵の行動が終了したら
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
			//エンディング判定したい
		}
	}
	return 0;
}

//Nullが帰ってくることもあるので注意
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
ActionInfo RogueGame::DecideNextAction(Chara* chara) {//何もしないなら０を返す
	bool flag = false;
	int nexttargetnum = chara->nextActionInfo.targetnum;
	ActionType nextaction = A_Attack;
	switch (chara->ai) {
	case Ai_AttackEnemy: 
	{
		if (nexttargetnum >= opparty.maxmember) {//ai変わったときよう　上から攻撃
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
		return{ chara->nextActionInfo };//攻撃しない
	}
			break;
	case Ai_AttackMy:
	{
		if (nexttargetnum < opparty.maxmember) {//ai変わったときよう　上から攻撃
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
		return{ chara->nextActionInfo };//攻撃しない
	}
		break;
	case Ai_AttackSpring: //id0が春という前提
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
		return{ chara->nextActionInfo };//攻撃しない
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
		return{ chara->nextActionInfo };//攻撃しない
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
		return{ chara->nextActionInfo };//攻撃しない
	}
	}
	chara->nextActionInfo = {
		-1,A_Nothing
	};
	return{ chara->nextActionInfo };//攻撃しない
}
ActionInfo RogueGame::DecideNextAction(const int num) {
	Chara* chara(GetMember(num));
	return DecideNextAction(chara);
}
