#include "RogueGameParty.h"
#include<assert.h>


Chara::Chara(const int aid) :id(aid), name(DATES[aid].name) {
	atk = TABLE<0, 0>::atk;
	def = TABLE<0, 0>::def;
	now_hp = DATES[aid].fst_hp;
	max_hp = TABLE<0, 0>::max_hp;
	isdead = false;
}
bool Chara::GetDamage(const int admg) {
	assert(admg >= 0);
	now_hp -= admg;
	if (now_hp <= 0) {
		isdead = true;
		return true;
	}
	else {
		return false;
	}
}
bool Chara::GainLife(const int alife) {
	assert(alife >= 0);
	now_hp = max(now_hp + alife, max_hp);;
	return true;
}
MyChara::MyChara(const int aid) :Chara(aid) {
	level = DATES[aid].fst_level;
	next_exp = 0;
}
int MyChara::GainExp(const int aexp) {
	next_exp -= aexp;
	while (next_exp <= 0) {
	}
	return true;
}
Party::Party(const int aleft, const int aup) :members() {
	LEFT = aleft;
	UP = aup;
	
}
void Party::Update() {

}
void Party::Draw() {
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			aDrawableConsole.draw(LEFT, UP + 3 * i, members[i]->name.c_str());

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 1, "U");
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 1, "Žç");
			aDrawableConsole.draw(LEFT + 5, UP + 3 * i + 1, "HP");

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 2, Common::To_ZString(members[i]->atk).c_str());
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 2, Common::To_ZString(members[i]->def).c_str());
			aDrawableConsole.draw(LEFT + 5, UP + 3 * i + 2, ((Common::To_ZString(members[i]->now_hp) + " /" + Common::To_ZString(members[i]->max_hp)).c_str()));
		}
	}
}
bool Party::AddMember(const int aid) {
	for (int i = 0; i < maxmember; ++i) {
		if (members[i] == NULL) {
			Chara *a;
			if (DATES[aid].isenemy) {
				a = new Chara(aid);
			}
			members[i] = new MyChara(aid);
			return true;
		}
	}
	return false;
}
MyParty::MyParty(const int aleft, const int aup) :Party(aleft,aup) {
	
}
void MyParty::Update() {
	//I—¹”»’è

}
void MyParty::Draw() {
	Party::Draw();
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			MyChara *a = static_cast<MyChara*> ((members[i]));
			aDrawableConsole.draw(LEFT + 2, UP + 3 * i, "ƒŒƒxƒ‹");
			aDrawableConsole.draw(LEFT + 5, UP + 3 * i, Common::To_ZString(a->level).c_str());
			aDrawableConsole.draw(LEFT + 11, UP + 3 * i, "NextExp ");
			aDrawableConsole.draw(LEFT + 5, UP + 3 * i, Common::To_ZString(a->next_exp).c_str());
		}
		
	}
}
vector<int > MyParty::GetAliveMemberId() {
	vector<int> AliveId;
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			if (!members[i]->isdead)
				AliveId.push_back(members[i]->id);
		}
	}
	return AliveId;
}
OpParty::OpParty(const int aleft, const int aup) : Party(aleft,aup) {
	
}
void OpParty::Update() {

}
void OpParty::Draw(){
	Party::Draw();
}