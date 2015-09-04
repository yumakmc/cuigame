#include "RogueGameParty.h"
#include<assert.h>


Chara::Chara(const int aid, vector<string> *aactionlog, Situation *asituation) :id(aid), name(DATES[aid].name),actionlog(aactionlog),situation(asituation) {
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
//int Chara::Act(const Action type) {
//	switch (type) {
//	case A_Attack:
//		
//		actionlog->push_back(name + "ÇÃçUåÇ");
//		break;
//	case A_Defence:
//		defending = true;
//		actionlog->push_back(name + "ÇÃñhå‰");
//		
//		break;
//	case A_Special:
//		actionlog->push_back(name + "ÇÃì¡éÍ");
//		break;
//
//	default:
//		assert(false);
//	}
//	*situation = S_OtherTurn;
//	return true;
//}
//int Chara::SelectAction(const Action type) {
//	defending = false;//ì¡éÍå¯â âèú
//	switch (type) {
//	case A_Attack:
//		*situation = S_ChoosingTarget;
//		nowfor = 0;
//		break;
//	case A_Defence:
//		Act(A_Defence);
//		break;
//	case A_Special:
//		*situation = S_ChoosingTarget;
//		nowfor = 2;
//		break;
//
//	default:
//		assert(false);
//	}
//	return true;
//}
//bool Chara:: Attack(Chara &atarget) {
//	return atarget.GetDamage(CalculateDmg(atarget));
//}
//inline int Chara::CalculateDmg(const Chara& atarget) {
//	const int diff = max(0, atk - atarget.def);
//	return atarget.defending ? diff / 4 : diff;
//}
MyChara::MyChara(const int aid, vector<string> *aactionlog, Situation *asituation) :Chara(aid,aactionlog, asituation){
	level = DATES[aid].fst_level;
	next_exp = 0;
}
int MyChara::GainExp(const int aexp) {
	next_exp -= aexp;
	while (next_exp <= 0) {
	}
	return true;
}
//bool MyChara::Attack(Chara &atarget){
//	if (atarget.GetDamage(CalculateDmg(atarget))) {
//		GainExp(777);
//		return true;//////////////
//	}
//	return false;
//}
Party::Party(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation) :members(), actionlog(aactionlog),situation(asituation){
	LEFT = aleft;
	UP = aup;
	
}
void Party::Update() {

}
void Party::Draw() {
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			aDrawableConsole.draw(LEFT, UP + 3 * i, std::to_string(i)+":");
			aDrawableConsole.draw(LEFT+1, UP + 3 * i, members[i]->name.c_str());

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 1, "çU");
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 1, "éÁ");
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
			if (DATES[aid].isenemy) {
				
			}
			members[i] = new MyChara(aid, actionlog, situation);
			return true;
		}
	}
	return false;
}
Chara* Party::GetMember(const int anum) {
	return members[anum];
}
//int Party::Act(const Action type) {
//	return members[nowselect]->SelectAction(type);
//}
MyParty::MyParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation) :Party(aleft,aup,aactionlog, asituation) {
	
}
void MyParty::Update() {
	//èIóπîªíË

}
void MyParty::Draw() {
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			MyChara *achara = static_cast<MyChara*> ((members[i]));
			aDrawableConsole.draw(LEFT, UP + 3 * i, std::to_string(4+i) + ":");
			aDrawableConsole.draw(LEFT + 1, UP + 3 * i, achara->name.c_str());

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 1, "çU");
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 1, "éÁ");
			aDrawableConsole.draw(LEFT + 5, UP + 3 * i + 1, "HP");

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 2, Common::To_ZString(achara->atk).c_str());
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 2, Common::To_ZString(achara->def).c_str());
			aDrawableConsole.draw(LEFT + 5, UP + 3 * i + 2, ((Common::To_ZString(achara->now_hp) + " /" + Common::To_ZString(members[i]->max_hp)).c_str()));
			
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i, "Lv");
			aDrawableConsole.draw(LEFT + 4, UP + 3 * i, Common::To_ZString(achara->level).c_str());
			aDrawableConsole.draw(LEFT + 8, UP + 3 * i, "NextExp:");
			aDrawableConsole.draw(LEFT + 13, UP + 3 * i, Common::To_ZString(achara->next_exp).c_str());
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
OpParty::OpParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation) : Party(aleft,aup,aactionlog, asituation) {
	
}
void OpParty::Update() {

}
void OpParty::Draw(){
	Party::Draw();
}