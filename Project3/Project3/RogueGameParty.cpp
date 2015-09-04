#include "RogueGameParty.h"
#include<assert.h>


Chara::Chara(const int aid, vector<string> *aactionlog, Situation *asituation) :id(aid), name(DETAILS[aid].name),actionlog(aactionlog),situation(asituation) {
	atk = TABLE<0, 0>::atk;
	def = TABLE<0, 0>::def;
	now_hp = DETAILS[aid].fst_hp;
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
int Chara::GainLife(const int pluslife) {
	assert(pluslife >= 0);//0でもＯＫにしてる　とりま
	const int realpluslife = max(0,min(pluslife, max_hp - now_hp));
	now_hp +=realpluslife;
	return realpluslife;
}
//int Chara::Act(const Action type) {
//	switch (type) {
//	case A_Attack:
//		
//		actionlog->push_back(name + "の攻撃");
//		break;
//	case A_Defence:
//		defending = true;
//		actionlog->push_back(name + "の防御");
//		
//		break;
//	case A_Special:
//		actionlog->push_back(name + "の特殊");
//		break;
//
//	default:
//		assert(false);
//	}
//	*situation = S_OtherTurn;
//	return true;
//}
//int Chara::SelectAction(const Action type) {
//	defending = false;//特殊効果解除
//	switch (type) {
//	case A_Attack:
//		*situation = S_ChoosingTarget;
//	
//		break;
//	case A_Defence:
//		Act(A_Defence);
//		break;
//	case A_Special:
//		*situation = S_ChoosingTarget;
//
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
	level = DETAILS[aid].fst_level;
	next_exp = 0;
	if (id == 0) {//春なら
		controlable = true;
	}
}
int MyChara::GainExp(const int aexp) {
	next_exp -= aexp;
	if(next_exp <= 0) {
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

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 1, "攻");
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 1, "守");
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
			if (DETAILS[aid].isenemy) {
				
			}
			members[i] = new MyChara(aid, actionlog, situation);
			return true;
		}
	}
	return false;
}
void Party::DeleteMember(const int anum) {
	
	members[anum] = NULL;

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
	//終了判定

}
void MyParty::Draw() {
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			MyChara *achara = static_cast<MyChara*> ((members[i]));
			aDrawableConsole.draw(LEFT, UP + 3 * i, std::to_string(4+i) + ":");
			aDrawableConsole.draw(LEFT + 1, UP + 3 * i, achara->name.c_str());

			aDrawableConsole.draw(LEFT + 1, UP + 3 * i + 1, "攻");
			aDrawableConsole.draw(LEFT + 3, UP + 3 * i + 1, "守");
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