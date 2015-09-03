#include "RogueGameParty.h"
#include<assert.h>


Chara::Chara(const int aid) :id(aid), name(DATES[aid].name) {
	atk = TABLE<0, 0>::atk;
	def = TABLE<0, 0>::def;
	now_hp = DATES[aid].fst_hp;
	
}
int Chara::GetDamage(const int admg) {
	assert(admg >= 0);
	now_hp -= admg;
	if (now_hp <= 0) {
		return true;
	}
	else {
		return false;
	}
}
MyChara::MyChara(const int aid) :Chara(aid) {
	level = DATES[aid].fst_level;
	exp = 0;
}
int MyChara::GetExp(const int aexp) {
	exp += aexp;
	return true;
}
Party::Party() :members() {
	
}
void Party::Update() {

}
void Party::Draw() {
	for (int i = 0; i < members.size(); ++i) {
		aDrawableConsole.draw(LEFT, UP+3*i,members[i].name.c_str());
		aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 1, "U");
		aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 1, "Žç");
		aDrawableConsole.draw(LEFT+1, UP + 3 * i+2, Common::To_ZString(members[i].atk).c_str());
		aDrawableConsole.draw(LEFT+3, UP + 3 * i + 2, Common::To_ZString(members[i].def).c_str());
	}

}
bool Party::AddMember(const int aid) {
	if (members.size() >= maxmember) { return false; }
	members.push_back(Chara(aid));
	return true;
}
MyParty::MyParty() :Party() {
	LEFT = 30;
	UP = 13;
}
OpParty::OpParty() : Party() {
	LEFT = 30;
	UP = 0;
}