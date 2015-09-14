#include "RogueGame.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include "RogueSaveManager.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <assert.h>

using namespace roguegame;

bool MoonKillFlag = false;

namespace roguegame {

	RogueSaveData::RogueSaveData(const MyParty& m, const OpParty& o, int d, int s)
	{
		shared_ptr<MyChara> dd = (static_pointer_cast<MyChara>(m.GetMember(0)));
		for (int i = 0; i < 4; ++i) {
			shared_ptr<MyChara> pmc = (static_pointer_cast<MyChara>(m.GetMember(i)));
			if (pmc == NULL) {
				
			}
			else {
				mymembers[i] = (make_pair(1+i, *pmc));
			}

			shared_ptr<OpChara> omc = (static_pointer_cast<OpChara>(o.GetMember(i)));
			if (omc == NULL) {
				
			}
			else {
				opmembers[i] = (make_pair(1 + i, *omc));
			}

		}

		day = d;
		season = s;
	}
	RogueSaveData::RogueSaveData()
	{}
	RogueSaveData::~RogueSaveData() {

	}

	const int LOG_LINE_Y = 20;

	const int PARTY_LEFT = 25;
	const int MY_PARTY_UP = 13;
	const int OP_PARTY_UP = 0;
	//static const int dx[4] = { -1,0,1,0 };
	//static const int dy[4] = { 0,-1,0,1 };

	const int MAP_LEFT = 2;
	const int MAP_UP = 2;
	const int SEASON_NUM = 4;
	

	//防御してた時ダメがこれで割った数値になる。（切り捨て）
	const int DEFENDINGCUTOFF = 5;

#pragma region ENEMYMAP
	const int SPRING_DAY = 91;
	const int SUMMER_DAY = 91;
	const int FALL_DAY = 91;
	const int WINTER_DAY = 92;
	const int DAY_PER_SEASON = 91;
	static vector<int> SpringEnemyMap = {
		4,4,0,0,0,5,0,0,0,4,
		0,0,0,0,4,0,0,0,0,4,
		0,0,4,0,0,5,0,0,7,0,
		0,4,0,4,0,0,5,0,4,0,
		0,0,4,0,0,0,0,5,0,0,
		0,0,5,0,4,0,4,0,0,6,
		0,0,0,5,0,0,0,4,0,0,
		0,4,7,0,0,0,5,0,4,4,
		4,0,0,0,0,4,5,0,5,0,
		0,
	};
	static vector<int> SummerEnemyMap = {
		0,8,0,0,9,8,0,0,0,0,
		0,0,0,8,0,0,8,0,0,8,
		0,0,0,0,0,0,9,0,10,0,
		0,8,0,0,0,10,0,0,8,0,
		0,0,8,0,0,0,0,9,0,0,
		0,0,9,8,0,0,10,10,0,0,
		0,0,0,10,0,0,0,9,0,0,
		0,0,11,0,0,0,9,0,0,0,
		10,0,0,11,0,0,0,0,18,0,
		0,
	};
	static vector<int> FallEnemyMap = {
		0,12,0,0,0,0,18,0,0,0,
		0,0,0,13,0,0,0,12,0,12,
		0,0,18,0,0,12,0,0,13,0,
		0,0,0,0,0,14,0,0,0,0,
		0,0,0,0,0,0,0,14,0,0,
		0,0,12,0,22,0,13,14,0,0,
		0,0,0,15,0,18,18,18,0,0,
		0,0,12,0,0,0,0,0,18,19,
		12,0,0,13,0,0,0,0,0,0,
		0,
	};
	/*static array<int, DAY_PER_SEASON> WinterEnemyMap = {
		0,20,0,0,0,19,0,0,17,19,
		0,19,0,19,0,18,0,19,0,18,
		0,0,17,0,19,18,0,16,19,0,
		0,18,0,19,0,19,0,0,20,0,
		0,0,18,0,0,16,0,19,0,0,
		0,0,19,0,18,0,16,16,17,0,
		0,19,0,19,0,0,0,19,0,0,
		0,0,19,19,18,19,19,19,0,18,
		18,19,0,0,19,0,0,0,0,0,
		0,
	};*/
	static vector<int> WinterEnemyMap = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,2,
	};
	static array<vector<int>, SEASON_NUM> EnemyMaps = {//0:空白　 　　4~敵
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
		Date date;
		string name;
		Effect effect;
		name_and_descript(Date adate, string aname, Effect aeffect, vector<string> adescripts) :name(aname), descripts(adescripts) {
			date = adate;
			effect = aeffect;
		}
		name_and_descript() :name(), descripts() {
			int a=0;
			a++;
			assert(false);
		}
	private:
		vector<string> descripts;

	public:
		string GetDescript() {
			if (date == Mon) {
				assert(descripts.size() >= 2);
				if (MoonKillFlag) {
					return descripts[1];
				}
				else {
					return descripts[0];
				}
			}
			else {
				assert(descripts.size());
				return descripts[0];
			}
		}
	};
	name_and_descript a(Thu, "火", E_AtkUp, { "攻撃力　２倍" });
	static map<Date, name_and_descript> YOUBI_DETAIL = {//day0: 月曜日 day1: 火曜日となる
		{ Thu,name_and_descript{ Thu,"火",E_AtkUp ,{ "攻撃力　２倍" } }, },
		{ Wed,name_and_descript{ Wed,"水",E_sss   ,{ "" } }, },
		{ Tur,name_and_descript{ Tur,"木",E_Invin ,{ "無敵" } }, },
		{ Fri,name_and_descript{ Fri,"金",E_ExpUp ,{ "経験値　２倍" } }, },
		{ Sat,name_and_descript{ Sat,"土",E_DefUp ,{ "防御力　２倍" } }, },
		{ Sun,name_and_descript{ Sun,"日",E_LoveUp,{ "愛　３倍" } }, },
		{ Mon,name_and_descript{ Mon,"月",E_Moon  ,{ "月が笑っている","味方攻守３倍" } } },
	};
	//static map<Date, name_and_descript> YOUBI_DETAIL;
	struct chip_descript {
		string shortname;
		string fullname;
		vector<string> descript;
	};
	static map<int, chip_descript> CHIP_DETAIL = {//day0: 月曜日 day1: 火曜日となる
		{ 0 ,chip_descript{ "０","０",{ "死なないで下さい" } } },
		{ 1 ,chip_descript{ "春","０",{ "月が笑っている" } } },
		{ 2 ,chip_descript{ "終","終",{ "防御力　２倍" } } },
		{ 3 ,chip_descript{ "う","０",{ "経験値　２倍" } } },
		{ 4 ,chip_descript{ DETAILS[4].name,"０",{"無敵" } } },
		{ 5 ,chip_descript{ DETAILS[5].name,"０",{"愛　３倍" } } },
		{ 6 ,chip_descript{ DETAILS[6].name,"０",{"月が笑っている" } } },
		{ 7 ,chip_descript{ DETAILS[7].name,"０",{"無敵" } } },
		{ 8 ,chip_descript{ DETAILS[8].name,"０",{"「俺もお前らもみんなおしまいだ」" } } },
		{ 9 ,chip_descript{ DETAILS[9].name,"０",{"死なないで下さい" } } },
		{ 10,chip_descript{ DETAILS[10].name,"０",{"死なないで下さい" } } },
		{ 11,chip_descript{ DETAILS[11].name,"０",{"死なないで下さい" } } },
		{ 12,chip_descript{ DETAILS[12].name,"０",{"死なないで下さい" } } },
		{ 13,chip_descript{ DETAILS[13].name,"０",{"死なないで下さい" } } },
		{ 14,chip_descript{ DETAILS[14].name,"０",{"無敵" } } },
		{ 15,chip_descript{ DETAILS[15].name,"０",{"愛　３倍" } } },
		{ 16,chip_descript{ DETAILS[16].name,"０",{"月が笑っている" }} },
		{ 17,chip_descript{ DETAILS[17].name,"０",{"無敵"} } },
		{ 18,chip_descript{ DETAILS[18].name,"０",{"「俺もお前らもみんなおしまいだ」" } } },
		{ 19,chip_descript{ DETAILS[19].name,"０",{"死なないで下さい" } } },
		{ 20,chip_descript{ DETAILS[20].name,"０",{"死なないで下さい" } } },
		{ 21,chip_descript{ DETAILS[21].name,"０",{"死なないで下さい" } } },
		{ 22,chip_descript{ DETAILS[22].name,"０",{"死なないで下さい" } } },
		{ 23,chip_descript{ DETAILS[23].name,"０",{"死なないで下さい" } } },
	};
}
Ending EndingNum = E_Dummy;//externでRogueEndingに渡す
int LoveHp = 0;
int KillNum = 0;
int SpendDay = 0;
shared_ptr <vector<string>> b(make_shared<vector<string>>());//ここ汚い直したい
shared_ptr <Situation>c(make_shared<Situation>(S_Opening));

RogueGame::RogueGame(gameSceneChanger* changer)
	:gameBaseScene(changer), abackground(0), actionlog(b), situation(c), myparty(PARTY_LEFT, MY_PARTY_UP, b, c), opparty(PARTY_LEFT, OP_PARTY_UP, b, c), nowplayernum(4) {
	Party a(PARTY_LEFT, MY_PARTY_UP, actionlog, situation);
	myparty.AddMember(0, *this);


	//デバッグ用
	if (Keyboard_Get('K')) {
		for (int i = 0; i < 70; ++i) {
			shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));
			a->LevelUp();
			a->GainLife(10000);
		}
	}
	else if (Keyboard_Get('C')) {
		season = 1;
		day = 91;

		shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));

		a->GainExp(350);//これが稼がないプレイの下限か？
		a->GainLife(10000);
		myparty.AddMember(1, *this);
	}
	else if (Keyboard_Get('P')) {
		season = 1;
		day = 91;

		shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));

		a->GainExp(600);//稼ぐプレイ
		a->GainLife(10000);
		myparty.AddMember(1, *this);

	}
	else if (Keyboard_Get('V')) {
		season = 2;
		day = 182;

		shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));
		a->GainExp(2500);//稼がないプレイ
		a->GainLife(10000);

		myparty.AddMember(1, *this);
		myparty.AddMember(2, *this);
		actionlog->push_back("夏の攻撃対象が変更された");
		GetMember(false, 1)->count = 2;
		GetMember(false, 1)->now_hp=200;
		GetMember(false, 1)->DecideNextAction(*this);
	}
	else if (Keyboard_Get('F')) {
		season = 2;
		day = 182;

		shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));
		a->GainExp(3000);//稼ぐプレイ
		a->GainLife(10000);

		myparty.AddMember(1, *this);
		myparty.AddMember(2, *this);
		actionlog->push_back("夏の攻撃対象が変更された");
		GetMember(false, 1)->count = 2;
		GetMember(false, 1)->now_hp = 200;
		GetMember(false, 1)->DecideNextAction(*this);
	}
	else if (Keyboard_Get('U')) {
		season = 3;
		day = 273;
		shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));
		a->GainExp(10000);//稼がないプレイ
		a->GainLife(10000);

		myparty.AddMember(1, *this);
		GetMember(false, 1)->ai = Ai_AttackEnemy;
		GetMember(false, 1)->now_hp = 100;
		GetMember(false, 1)->DecideNextAction(*this);
		static_pointer_cast<MyChara>(GetMember(false, 1))->GainExp(7000);//稼ぐプレイ
		myparty.AddMember(2, *this);
		GetMember(false, 2)->ai = Ai_AttackEnemy;
		GetMember(false, 2)->now_hp = 100;
		GetMember(false, 2)->DecideNextAction(*this);
		static_pointer_cast<MyChara>(GetMember(false, 2))->GainExp(7000);
		myparty.AddMember(3, *this);
		opparty.AddMember(21, 0, *this);
	}
	else if (Keyboard_Get('I')) {
		season = 3;
		day = 273;
		shared_ptr<MyChara> a = static_pointer_cast<MyChara>(GetMember(false, 0));
		a->GainExp(15000);//稼ぐプレイ
		a->GainLife(10000);

		myparty.AddMember(1, *this);
		GetMember(false, 1)->ai = Ai_AttackEnemy;
		GetMember(false, 1)->now_hp = 100;
		GetMember(false, 1)->DecideNextAction(*this);
		static_pointer_cast<MyChara>(GetMember(false, 1))->GainExp(10000);//稼ぐプレイ
		myparty.AddMember(2, *this);
		GetMember(false, 2)->ai = Ai_AttackEnemy;
		GetMember(false, 2)->now_hp = 100;
		GetMember(false, 2)->DecideNextAction(*this);
		static_pointer_cast<MyChara>(GetMember(false, 2))->GainExp(10000);
		myparty.AddMember(3, *this);
		opparty.AddMember(21, 0, *this);
	}
	else {
		// 無理やりな冬挿入
		myparty.AddMember(23, *this);
		GetMember(7)->isdead = true;
		season = 0;
		day = 0;
	}

	Initialize();


	rand.init();
	aMusic.Play(-1);
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

			*situation = S_TurnStart;
		}
		break;
	case S_Help://ヘルプ
		break;
	case S_TurnStart:
		CheckDeadPlayer();
		////////////////////////////////////////////////
		if (EnemyMaps[season][day%DAY_PER_SEASON] >= 4) {

			opparty.AddMember(EnemyMaps[season][day%DAY_PER_SEASON], *this);
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
		else if (Keyboard_Get('Q') == 1) {
			*situation = S_Save;
		}
		else if (Keyboard_Get('L') == 1) {
			*situation = S_Load;
		}

		break;
	case S_ChoosingTarget://対象を選択中
		if (Keyboard_Get('X') == 1) {
			*situation = S_ChoosingAction;
			break;
		}
		for (int i = 0; i < myparty.maxmember + opparty.maxmember; ++i) {
			if (Keyboard_Get(i + 48) == 1) {
				shared_ptr<Chara> target(GetMember(i));

				if (target != NULL) {
					*situation = S_ChoosingAction;
					Act(GetMember(nowplayernum), target, nowaction);
				}
				break;
			}
		}
		break;
	case S_AllyTurn: {

		shared_ptr<MyChara> nowplayer = static_pointer_cast<MyChara>(GetMember(nowplayernum));
		if (nowplayer->nextActionInfo.targetnum == -1 || GetMember(nowplayer->nextActionInfo.targetnum) == NULL) {
			nowplayer->DecideNextAction(*this);
		}
		Act(nowplayer, GetMember(nowplayer->nextActionInfo.targetnum), nowplayer->nextActionInfo.type);
		nowplayer->DecideNextAction(*this);
	}
					 break;
	case S_EnemyTurn: {

		shared_ptr<OpChara> nowplayer = static_pointer_cast<OpChara>(GetMember(nowplayernum));
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
		if (day % DAY_PER_SEASON == 0) {
			season++;
			switch (season) {
			case 0:
				assert(false);
				break;
			case 1:
				myparty.AddMember(1, *this);
				break;
			case 2:
				myparty.AddMember(2, *this);
				actionlog->push_back("夏の攻撃対象が変更された");
				GetMember(false, 1)->count = 2;
				GetMember(false, 1)->DecideNextAction(*this);
				break;
			case 3:
				myparty.AddMember(3, *this);
				opparty.AddMember(-1, 0, *this);
				opparty.AddMember(-1, 1, *this);
				opparty.AddMember(-1, 2, *this);
				opparty.AddMember(-1, 3, *this);
				break;
			default:
				;
			}
		}
		*situation = S_TurnStart;
		break;
	case S_Save:
		if (Keyboard_Get('Z') == 1) {
			Save();
			*situation = S_ChoosingAction;

		}
		else if (Keyboard_Get('X')) {
			*situation = S_ChoosingAction;

		}
		break;
	case S_Load:
		if (Keyboard_Get('Z') == 1) {
			Load();
			*situation = S_ChoosingAction;

		}
		else if (Keyboard_Get('X')) {
			*situation = S_ChoosingAction;

		}
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
	aDrawableConsole.draw(7, 0, Common::To_ZString(day) + "日/365日");
	aDrawableConsole.draw(13, 0, YOUBI_DETAIL[Date(day % 7)].name + "曜日：" + YOUBI_DETAIL[Date(day % 7)].GetDescript());
	//////////////////////////////////////////////////////////////////////////////
#pragma endregion	
#pragma region MAP
	vector<int> My_EnemyMap(EnemyMaps[season]);
	My_EnemyMap[day%DAY_PER_SEASON] = 1;

	assert(7 * 13 <= My_EnemyMap.size());
	for (int h = 0; h < My_EnemyMap.size(); ++h) {
		int ax, ay;
		if (h<7 * 13) {

			const int i = h / 13;
			const int j = h % 13;

			if (i % 2) {
				if (j != 12) {
					ax = 11 - j + MAP_LEFT;
					ay = MAP_UP + 2 * (6 - i) + 1;
				}
				else {
					ax = MAP_LEFT;
					ay = MAP_UP + 2 * (6 - i);
				}
			}
			else {
				if (j != 12) {
					ax = j + MAP_LEFT;
					ay = MAP_UP + 2 * (6 - i) + 1;
				}
				else {
					ax = 11 + MAP_LEFT;
					ay = MAP_UP + 2 * (6 - i);
				}
			}
			
		}
		else {
			ax = 12 + MAP_LEFT;
			ay = MAP_UP;
		}
		string st = CHIP_DETAIL[My_EnemyMap[h]].shortname;
		if (st == "春") {
			aDrawableConsole.drawc(ax, ay, st, DrawableConsole::COLOR::C_LPINK, DrawableConsole::COLOR::C_BLACK);
		}
		else {
			aDrawableConsole.draw(ax, ay, st);
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
		aDrawableConsole.draw(ax, ay, "Ｚを押してスタート");
		break;
	case S_Help:
		aDrawableConsole.draw(ax, ay, "ヘルプ画面");
		break;
	case S_TurnStart:
		aDrawableConsole.draw(ax, ay, "ターンスタート");
		break;
	case S_ChoosingAction:
		aDrawableConsole.draw(ax, ay, "行動の選択");
		break;
	case S_ChoosingTarget:
		aDrawableConsole.draw(ax, ay, "対象の選択　Ｘで戻る");
		break;
	case S_AllyTurn:
		aDrawableConsole.draw(ax, ay, "味方のターン");
		break;
	case S_EnemyTurn:
		aDrawableConsole.draw(ax, ay, "敵のターン");
		break;
	case S_TurnEnd:
		aDrawableConsole.draw(ax, ay, "日が暮れた。日が明けた。");
		break;
	case S_Save:
		aDrawableConsole.draw(ax, ay, "セーブする？");
		break;
	case S_Load:
		aDrawableConsole.draw(ax, ay, "ロードする？");
		break;
	default:
		assert(false);
		break;
	}
#pragma endregion	
#pragma region LOG

	aDrawableConsole.draw(1, LOG_LINE_Y + 1, "ログ");
	auto startit = actionlog->size() <= 3 ? actionlog->begin() : actionlog->end() - 4;
	for (int i = 0; i < 4; ++i) {
		if (startit + i == actionlog->end())break;
		aDrawableConsole.draw(5, LOG_LINE_Y + 1 + i, *(startit + i));
	}

#pragma endregion

#pragma region MANUAL

	aDrawableConsole.draw(1, LOG_LINE_Y - 1, "A:攻撃　D:防御　S:愛");

#pragma endregion

}
int RogueGame::Regenerate(shared_ptr<Chara> from, shared_ptr<Chara> to) {
	const int pluslife = max(0, min(to->max_hp - to->now_hp, (YOUBI_DETAIL[Date(day % 7)].effect == E_LoveUp) ? from->max_hp : (from->max_hp / 3)));

	to->GainLife(pluslife);
	if (from->id == 0 && DETAILS[to->id].isenemy) {//春がfrom,敵がtoなら

												   //toからとれる経験値増える
		static_pointer_cast<OpChara>(to)->exp += pluslife;

	}
	return pluslife;
}
int RogueGame::Regenerate(const int fromnum, const int tonum) {
	shared_ptr<Chara> from = GetMember(fromnum);
	shared_ptr<Chara> to = GetMember(tonum);
	return Regenerate(from, to);
}

//ダメージを返す
int RogueGame::Attack(shared_ptr<Chara> from, shared_ptr<Chara> to) {
	const int dmg = CalculateDmg(from, to);
	actionlog->push_back(from->name + "の攻撃　" + to->name + "に" + Common::To_ZString(dmg) + "のダメージ");
	to->GetDamage(dmg);
	if (dmg) {
		if (to->isdead&&DETAILS[to->id].isenemy) {
			KillNum++;
			int getexp = static_pointer_cast<OpChara>(to)->exp;
			if (YOUBI_DETAIL[Date(day % 7)].effect == E_ExpUp) {
				getexp *= 2;
			}
			myparty.GainExp(getexp);
		}
	}
	//夏が秋攻撃体制に入ってなかったら
	if (DETAILS[from->id].isenemy&&to->ai == Ai_Summer&&to->count != 2) {
		static bool speaked = false;
		if (!speaked) {
			switch (rand.gen() % 2) {
			case 0:
				actionlog->push_back("「邪魔するなよ」");
				break;
			case 1:
				actionlog->push_back("「うっとうしいな」");
			}
			speaked = true;
		}
		actionlog->push_back(to->name + "の攻撃対象が変更された");
		to->count = 1;
		to->DecideNextAction(*this);
	}

	return dmg;
}
//ダメージを返す
int RogueGame::Attack(const int fromnum, const int tonum) {
	shared_ptr<Chara> from = GetMember(fromnum);
	shared_ptr<Chara> to = GetMember(tonum);
	return Attack(from, to);
}
//回復量を返す
int RogueGame::Special(shared_ptr<Chara> from, shared_ptr<Chara> to) {
	//fromによって分岐
	switch (from->id) {
	case 0: {//春
		const int regenehp = Regenerate(from, to);
		actionlog->push_back(from->name + "の愛　" + to->name + "は" + Common::To_ZString(regenehp) + "回復した");
		if (DETAILS[to->id].isenemy) {
			LoveHp += regenehp;
		}
		return regenehp;
	}
	case 18: {//小隕石のつもり
		const int SMALLCOUNT = 8;
		from->count++;
		if (from->count < SMALLCOUNT) {
			actionlog->push_back(from->name + "は接近している　残り" + Common::To_ZString(SMALLCOUNT - from->count) + "ターン");
		}
		else {
			actionlog->push_back("ズドオオン！");
			for (int i = 0; i < myparty.maxmember; ++i) {
				shared_ptr<Chara> achara(GetMember(false, i));
				if (achara != NULL) {
					const int dmg = CalculateDmg(from, achara);
					actionlog->push_back(achara->name + "に" + Common::To_ZString(dmg) + "のダメージ");
					achara->GetDamage(dmg);
				}
			}
			from->GetDamage(100000);
		}
	}
			 break;
	case 19: {//小隕石のつもり
		const int MIDDLECOUNT = 10;
		from->count++;
		if (from->count < MIDDLECOUNT) {
			actionlog->push_back(from->name + "は接近している　残り" + Common::To_ZString(MIDDLECOUNT - from->count) + "ターン");
		}
		else {
			actionlog->push_back("ズドオオン！");
			for (int i = 0; i < myparty.maxmember; ++i) {
				shared_ptr<Chara> achara(GetMember(false, i));
				if (achara != NULL) {
					const int dmg = CalculateDmg(from, achara);
					actionlog->push_back(achara->name + "に" + Common::To_ZString(dmg) + "のダメージ");
					achara->GetDamage(dmg);
				}
			}
			from->GetDamage(100000);
		}
	}
			 break;
	case 20: {//小隕石のつもり
		const int BIGCOUNT = 15;
		from->count++;
		if (from->count < BIGCOUNT) {
			actionlog->push_back(from->name + "は接近している　残り" + Common::To_ZString(BIGCOUNT - from->count) + "ターン");
		}
		else {
			actionlog->push_back("ズドオオン！");
			for (int i = 0; i < myparty.maxmember; ++i) {
				shared_ptr<Chara> achara(GetMember(false, i));
				if (achara != NULL) {
					const int dmg = CalculateDmg(from, achara);
					actionlog->push_back(achara->name + "に" + Common::To_ZString(dmg) + "のダメージ");
					achara->GetDamage(dmg);
				}
			}
			from->GetDamage(100000);
		}
	}
			 break;
	case 21: {//超隕石のつもり
		const int MEGACOUNT = 91;
		from->count++;
		if (from->count < MEGACOUNT) {
			actionlog->push_back(from->name + "は接近している…　残り" + Common::To_ZString(MEGACOUNT - from->count) + "ターン");
		}
		else {
			actionlog->push_back("ズドオオオオオオオオオン！！！！");
			for (int i = 0; i < myparty.maxmember; ++i) {
				shared_ptr<Chara> achara(GetMember(false, i));
				if (achara != NULL) {
					const int dmg = CalculateDmg(from, achara);
					actionlog->push_back(achara->name + "に" + Common::To_ZString(dmg) + "のダメージ！！！！！！");
					achara->GetDamage(dmg);
				}
			}
			from->GetDamage(100000);
		}
	}
			 break;
	case 22: {//
		const int MOONCOUNT = 37;
		from->count++;
		if (from->count < MOONCOUNT) {
			actionlog->push_back(from->name + "は嘲笑っている");
		}
		else {
			MoonKillFlag = false;
			actionlog->push_back(from->name + "は嘲笑っている");
			from->isdead = true;
		}
	}
			 break;
	default:
		assert(false);
		;
	}
	return 0;
}
//回復量を返す
int RogueGame::Special(const int fromnum, const int tonum) {
	shared_ptr<Chara> from = GetMember(fromnum);
	shared_ptr<Chara> to = GetMember(tonum);
	return Special(from, to);
}
int RogueGame::Act(shared_ptr<Chara> from, shared_ptr<Chara> to, const ActionType type) {
	switch (type) {
	case A_Attack:
		Attack(from, to);
		break;
	case A_Defence:
		from->defending = true;
		actionlog->push_back(from->name + "の防御");
		break;
	case A_Special:
		Special(from, to);
		break;
	case A_Nothing:
		actionlog->push_back(from->name + "は何もしない");
		break;
	default:
		assert(false);
	}


	//死亡チェック
	CheckDeadPlayer();

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
		Act(GetMember(nowplayernum), GetMember(nowplayernum), A_Defence);
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

//基本的に攻撃力ー防御力　ただし最低１
inline int RogueGame::CalculateDmg(const shared_ptr<Chara> from, const shared_ptr<Chara> to) {
	if (YOUBI_DETAIL[Date(day % 7)].effect == (E_Invin)) {
		return 0;
	}
	else {
		int realatk = (YOUBI_DETAIL[Date(day % 7)].effect == (E_AtkUp)) ? from->atk * 2 : from->atk;
		int realdef = (YOUBI_DETAIL[Date(day % 7)].effect == (E_DefUp)) ? to->def * 2 : to->def;

		if (YOUBI_DETAIL[Date(day % 7)].effect == (E_Moon)) {
			if (!DETAILS[from->id].isenemy&&MoonKillFlag) {
				realatk *= 2;
			}
			if (!DETAILS[to->id].isenemy&&MoonKillFlag) {
				realdef *= 2;
			}
		}

		int diff = max(0, realatk - realdef);
		if ((from->id == 1 && to->id == 0) || (from->id == 2 && to->id == 1) || (from->id == 3 && to->id == 2) || (from->id == 0 && to->id == 3)) {
			diff *= 2;
			actionlog->push_back("特攻！　ダメージ二倍");
		}
		else if ((from->id == 0 && to->id == 1) || (from->id == 1 && to->id == 2) || (from->id == 2 && to->id == 3) || (from->id == 3 && to->id == 0)) {
			diff /= 2;
			actionlog->push_back("ダメージ半減");
		}
		return max(1, to->defending ? diff / DEFENDINGCUTOFF : diff);
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
		if ((GetMember(nowplayernum))->ai == Ai_Controlable) {
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
		shared_ptr<Chara> aopchara = opparty.GetMember(i);
		if (aopchara != NULL&&aopchara->isdead) {
			if (aopchara->id == 22){
				if (aopchara->now_hp > 0) {
					opparty.DeleteMember(i,3);
				}
				else {
					opparty.DeleteMember(i,2);
				}
			}
			opparty.DeleteMember(i);
		}
	}
	for (int i = 0; i < myparty.maxmember; ++i) {
		shared_ptr<Chara> amychara = myparty.GetMember(i);
		if (amychara != NULL&&amychara->isdead) {
			//エンディング判定したい
			switch (season) {
			case 0:
				switch (amychara->id) {
				case 0:
					EndingNum = E_Bad;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}
				break;
			case 1:
				switch (amychara->id) {
				case 0:
					EndingNum = E_True;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					EndingNum = E_SummerDead;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 2:

					break;

				case 3:
					break;
				}
				break;
			case 2:
				switch (amychara->id) {
				case 0:
					EndingNum = E_Why;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					EndingNum = E_FallKillSummer;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 2:
					break;
				case 3:
					break;
				}
				break;
			case 3:
				switch (amychara->id) {
				case 0:
					EndingNum = E_DeadInWinter;
					mgameSceneChanger->ChangeScene(eGameScene_Ending);
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				}
			default:
				break;
			}
			myparty.DeleteMember(i);
		}
	}
	return 0;
}

//Nullが帰ってくることもあるので注意
shared_ptr<Chara> RogueGame::GetMember(int num)const {
	if (num < 0) {
		return NULL;
	}else if (num < opparty.maxmember) {
		return opparty.GetMember(num);
	}
	else if (num < opparty.maxmember + myparty.maxmember) {
		return myparty.GetMember(num - opparty.maxmember);
	}
	else {
		//assert(false);
		return NULL;
	}
}
shared_ptr<Chara> RogueGame::GetMember(const bool isop, const int num)const {
	return GetMember(isop ? num : opparty.maxmember + num);
}
int RogueGame::Save() {
	RogueSaveData data = {
		myparty,
		opparty,
		day,
		season,
	};
	return aRogueSaveManager.Save(0, &data);
}

int RogueGame::Load() {
	RogueSaveData dddata;
	aRogueSaveManager.Load(0, &dddata);
	myparty.Load(dddata);
	opparty.Load(dddata);
	//myparty=data.myparty;
	//opparty = data.opparty;
	day = dddata.day;
	season = dddata.season;
	return 1;
}
