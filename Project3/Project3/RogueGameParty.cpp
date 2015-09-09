#include "RogueGameParty.h"
#include "RogueGame.h"
#include<assert.h>


Chara::Chara(const int aid, vector<string> *aactionlog, Situation *asituation) :id(aid), name(DETAILS[aid].name),actionlog(aactionlog),situation(asituation) {
	isdead = false;
	ai = DETAILS[aid].fst_ai;
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
	assert(pluslife >= 0);//0Ç≈Ç‡ÇnÇjÇ…ÇµÇƒÇÈÅ@Ç∆ÇËÇ‹
	const int realpluslife = max(0,min(pluslife, max_hp - now_hp));
	now_hp +=realpluslife;
	return realpluslife;
}
ActionInfo Chara::DecideNextAction(const RogueGame& roguegame) {
	bool flag = false;
	int nexttargetnum = nextActionInfo.targetnum;
	ActionType nextaction = A_Attack;
	switch (ai) {
	case Ai_AttackEnemy:
	{
		if (nexttargetnum >= roguegame.opparty.maxmember) {//aiïœÇÌÇ¡ÇΩÇ∆Ç´ÇÊÇ§Å@è„Ç©ÇÁçUåÇ
			nexttargetnum = -1;
		}
		for (int i = 0; i < roguegame.opparty.maxmember; ++i) {
			nexttargetnum++;
			if (nexttargetnum == roguegame.opparty.maxmember) {
				nexttargetnum = 0;
			}
			if (roguegame.GetMember(nexttargetnum) == NULL) {
				continue;
			}
			else {
				nextActionInfo = {
					nexttargetnum,nextaction
				};
				return{ nextActionInfo };
			}
		}
		nextActionInfo = {
			-1,A_Nothing
		};
		return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
	}
	break;
	case Ai_AttackMy:
	{
		if (nexttargetnum < roguegame.opparty.maxmember) {//aiïœÇÌÇ¡ÇΩÇ∆Ç´ÇÊÇ§Å@è„Ç©ÇÁçUåÇ
			nexttargetnum = roguegame.opparty.maxmember - 1;
		}
		for (int i = 0; i < 4; ++i) {
			nexttargetnum++;
			if (nexttargetnum == roguegame.opparty.maxmember + roguegame.myparty.maxmember) {
				nexttargetnum = 4;
			}
			if (roguegame.GetMember(nexttargetnum) == NULL) {
				continue;
			}
			else {
				nextActionInfo = {
					nexttargetnum,nextaction
				};
				return{ nextActionInfo };
			}
		}
		nextActionInfo = {
			-1,A_Nothing
		};
		return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
	}
	break;
	case Ai_Summer: //id0Ç™ètÇ∆Ç¢Ç§ëOíÒ
	{
		if (count==1) {
			count = 0;
			if (nexttargetnum >= roguegame.opparty.maxmember) {//aiïœÇÌÇ¡ÇΩÇ∆Ç´ÇÊÇ§Å@è„Ç©ÇÁçUåÇ
				nexttargetnum = -1;
			}
			for (int i = 0; i < roguegame.opparty.maxmember; ++i) {
				nexttargetnum++;
				if (nexttargetnum == roguegame.opparty.maxmember) {
					nexttargetnum = 0;
				}
				if (roguegame.GetMember(nexttargetnum) == NULL) {
					continue;
				}
				else {
					nextActionInfo = {
						nexttargetnum,nextaction
					};
					return{ nextActionInfo };
				}

			}
			nextActionInfo = {
				-1,A_Nothing
			};
			return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
		}
		else if(count==0){
			for (int i = 0; i < roguegame.myparty.maxmember; ++i) {

				if (roguegame.GetMember(roguegame.opparty.maxmember + i) != NULL&&roguegame.GetMember(roguegame.opparty.maxmember + i)->id == 0) {
					nextActionInfo = {
						roguegame.opparty.maxmember + i,nextaction
					};
					return{ nextActionInfo };
				}
			}
			nextActionInfo = {
				-1,A_Nothing
			};
			return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
		}
		else if (count == 2) {
			for (int i = 0; i < roguegame.myparty.maxmember; ++i) {

				if (roguegame.GetMember(roguegame.opparty.maxmember + i) != NULL&&roguegame.GetMember(roguegame.opparty.maxmember + i)->id == 2) {
					nextActionInfo = {
						roguegame.opparty.maxmember + i,nextaction
					};
					return{ nextActionInfo };
				}
			}
			nextActionInfo = {
				-1,A_Nothing
			};
			return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
		}
		else {
			assert(false);
		}
		
		
	}

	break;
	case Ai_AttackSummer:
	{
		for (int i = 0; i < roguegame.myparty.maxmember; ++i) {
			if (roguegame.GetMember(roguegame.opparty.maxmember + i) != NULL&&roguegame.GetMember(roguegame.opparty.maxmember + i)->id == 1) {
				nextActionInfo = {
					roguegame.opparty.maxmember + i,nextaction
				};
				return{ nextActionInfo };
			}
		}
		nextActionInfo = {
			-1,A_Nothing
		};
		return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
	}
	break;
	case Ai_AttackFall:
	{
		for (int i = 0; i < roguegame.myparty.maxmember; ++i) {

			if (roguegame.GetMember(roguegame.opparty.maxmember + i) != NULL&&roguegame.GetMember(roguegame.opparty.maxmember + i)->id == 2) {
				nextActionInfo = {
					roguegame.opparty.maxmember + i,nextaction
				};
				return{ nextActionInfo };
			}
		}
		nextActionInfo = {
			-1,A_Nothing
		};
		return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
	}
	break;
	case Ai_Meteor:
	{
		nextActionInfo = {
			-1,A_Nothing
		};
		return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
	}
	break;
	case Ai_Moon:
	{
		nextActionInfo = {
			-1,A_Nothing
		};
		return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
	}
	}
	nextActionInfo = {
		-1,A_Nothing
	};
	return{ nextActionInfo };//çUåÇÇµÇ»Ç¢
}
//int Chara::Act(const ActionType type) {
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
//int Chara::SelectAction(const ActionType type) {
//	defending = false;//ì¡éÍå¯â âèú
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
OpChara::OpChara(const int aid, vector<string> *aactionlog, Situation *asituation) :Chara(aid, aactionlog, asituation){
	exp = DETAILS[aid].opinfo.exp;
	atk = DETAILS[aid].opinfo.atk;
	def = DETAILS[aid].opinfo.def;
	max_hp = DETAILS[aid].opinfo.max_hp;
	now_hp = max_hp;
}
MyChara::MyChara(const int aid, vector<string> *aactionlog, Situation *asituation) :Chara(aid,aactionlog, asituation), infos(TABLE_A.Get(id)) {
	level = DETAILS[aid].myinfo.fst_level;
	atk = infos[level].atk;
	def = infos[level].def;
	now_hp = DETAILS[aid].fst_hp;
	max_hp = infos[level].max_hp;
	next_exp = infos[level].exp;

}
int MyChara::GainExp(const int aexp) {
	next_exp -= aexp;
	int num = 0;
	while(next_exp <= 0) {
		LevelUp();
		num++;
	}
	if (num) {
		actionlog->push_back(name + "ÇÕ" + Common::To_ZString(level) + "Ç…ÉåÉxÉãÉAÉbÉvÇµÇΩ");
	}
	return num;
}
bool MyChara::LevelUp() {
	level++;
	atk = infos[level].atk;
	def = infos[level].def;
	max_hp = infos[level].max_hp;
	next_exp += infos[level].exp;
	
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
}
bool Party::AddMember(const int aid, const RogueGame &roguegame) {
	//ÇﬂÇøÇ·Ç≠ÇøÇ·ó·äOìIÇ»èàóùÅ@ÇSî‘ñ⁄Ç…ñ≥óùÇ‚ÇËì~ÅiÇ∑ÇÆéÄÇ ÅjÇì¸ÇÍÇƒÇÈ
	if (aid == 23) {
		members[3] = new MyChara(aid, actionlog, situation);
	}
	else {
		for (int i = 0; i < maxmember; ++i) {
			if (members[i] == NULL) {
				string st="";
				switch (aid) {
				case 0:
					st = "ètÇ™ê∂Ç‹ÇÍÇΩ";
					break;
				case 1:
					actionlog->push_back("âƒÇ™ê∂Ç‹ÇÍÇΩ");
					actionlog->push_back("Åuç°ì˙Ç‹Ç≈Ç®îÊÇÍÅ@Ç∂Ç·Å[ÇÀÅ[Åv");
					actionlog->push_back("íçà”ÅFâƒÇ©ÇÁÇÃÉ_ÉÅÅ[ÉWÇÕìÒî{Ç…Ç»ÇËÇ‹Ç∑");
					break;
				case 2:
					actionlog->push_back("èHÇ™ê∂Ç‹ÇÍÇΩ");
					actionlog->push_back("ÅuÇ»ÇÒÇ≈âƒÇ‹Çæê∂Ç´ÇƒÇÈÇÃÅHÅv");
					actionlog->push_back("ÅuÇøÇ¡ÅcÅcÅcÅv");
					
					break;
				case 3:
					st = "ì~Ç™ê∂Ç‹ÇÍÇΩ";
					break;
				case 23:
					st = "";
					break;
				default:
					st = DETAILS[aid].name + "Ç™åªÇÍÇΩ";

				}
				actionlog->push_back(st);


				if (DETAILS[aid].isenemy) {
					members[i] = new OpChara(aid, actionlog, situation);
				}
				else {
					members[i] = new MyChara(aid, actionlog, situation);
				}
				members[i]->DecideNextAction(roguegame);
				return true;
			}
		}
	}
	
	return false;
}
void Party::DeleteMember(const int anum) {
	actionlog->push_back(members[anum]->name+"ÇÕéÄÇÒÇæ");
	members[anum] = NULL;

}
Chara* Party::GetMember(const int anum)const  {
	return members[anum];
}
//int Party::Act(const ActionType type) {
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
			const int CHARAUP = UP + 3 * i;
			MyChara *achara = static_cast<MyChara*> ((members[i]));
			aDrawableConsole.draw(LEFT, CHARAUP, std::to_string(4+i) + ":");
			aDrawableConsole.draw(LEFT + 1, CHARAUP, achara->name.c_str());
			aDrawableConsole.draw(LEFT + 3, CHARAUP, "Lv");
			aDrawableConsole.draw(LEFT + 4, CHARAUP, Common::To_ZString(achara->level).c_str());
			aDrawableConsole.draw(LEFT + 7, CHARAUP, "NextExp:");
			aDrawableConsole.draw(LEFT + 11, CHARAUP, Common::To_ZString(achara->next_exp).c_str());

			const int ATTACKLEFT = LEFT;

			aDrawableConsole.draw(ATTACKLEFT, CHARAUP + 1, "çU");
			aDrawableConsole.draw(ATTACKLEFT, CHARAUP + 2, Common::To_ZString(achara->atk).c_str());

			aDrawableConsole.draw(ATTACKLEFT + 3, CHARAUP + 1, "éÁ");
			aDrawableConsole.draw(ATTACKLEFT + 3, CHARAUP + 2, Common::To_ZString(achara->def).c_str());

			aDrawableConsole.draw(ATTACKLEFT + 6, CHARAUP + 1, "HP");
			aDrawableConsole.draw(ATTACKLEFT + 6, CHARAUP + 2, ((Common::To_ZString(achara->now_hp) + " /" + Common::To_ZString(achara->max_hp)).c_str()));
			if (!achara->ai==Ai_Controlable) {
				aDrawableConsole.draw(LEFT + 12, CHARAUP + 1, "ëŒè€");
				aDrawableConsole.draw(LEFT + 12, CHARAUP + 2, Common::To_ZString(achara->nextActionInfo.targetnum));
			}
		}
	}
}
bool MyParty::AddMember(const int aid, const RogueGame &roguegame) {

	assert(!DETAILS[aid].isenemy);
	return Party::AddMember(aid, roguegame);
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
int MyParty::GainExp(const int exp) {
	for (int i = 0; i < maxmember; ++i) {
		MyChara* achara = static_cast<MyChara*>(members[i]);
		if (achara != NULL) {
			achara->GainExp(exp);
		}
		
	}
	return 1;
}

OpParty::OpParty(const int aleft, const int aup, vector<string> *aactionlog, Situation *asituation) : Party(aleft,aup,aactionlog, asituation) {
	
}
void OpParty::Update() {

}
void OpParty::Draw(){
	for (int i = 0; i < members.size(); ++i) {
		if (members[i] != NULL) {
			const int CHARAUP = UP + 3 * i;
			OpChara *achara = static_cast<OpChara*> ((members[i]));
			aDrawableConsole.draw(LEFT, CHARAUP, std::to_string(i) + ":");
			aDrawableConsole.draw(LEFT + 1, CHARAUP, achara->name.c_str());
			aDrawableConsole.draw(LEFT + 9, CHARAUP, "Exp:");
			aDrawableConsole.draw(LEFT + 11, CHARAUP, Common::To_ZString(achara->exp));

			const int ATTACKLEFT = LEFT;

			aDrawableConsole.draw(ATTACKLEFT, CHARAUP + 1, "çU");
			aDrawableConsole.draw(ATTACKLEFT, CHARAUP + 2, Common::To_ZString(achara->atk).c_str());

			aDrawableConsole.draw(ATTACKLEFT + 3, CHARAUP + 1, "éÁ");
			aDrawableConsole.draw(ATTACKLEFT + 3, CHARAUP + 2, Common::To_ZString(achara->def).c_str());

			aDrawableConsole.draw(ATTACKLEFT + 6, CHARAUP + 1, "HP");
			aDrawableConsole.draw(ATTACKLEFT + 6, CHARAUP + 2, ((Common::To_ZString(achara->now_hp) + " /" + Common::To_ZString(achara->max_hp)).c_str()));
			if (!achara->ai == Ai_Controlable) {
				aDrawableConsole.draw(LEFT + 12, CHARAUP + 1, "ëŒè€");
				aDrawableConsole.draw(LEFT + 12, CHARAUP + 2, Common::To_ZString(achara->nextActionInfo.targetnum));
			}
		}
	}
}
bool OpParty::AddMember(const int aid,const RogueGame &roguegame) {

	assert(DETAILS[aid].isenemy);
	return Party::AddMember(aid,roguegame);
}