#include "RogueEnding.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include "Common.h"
#include "RogueGame.h"
#include <string>
#include <algorithm>

extern roguegame::Ending EndingNum;//RogueGame‚æ‚èQÆ
extern int LoveHp ;//RogueGame‚æ‚èQÆ
extern int KillNum ;//RogueGame‚æ‚èQÆ
extern int SpendDay ;//RogueGame‚æ‚èQÆ

std::vector<string> SHOWRANK = {
	"‚r",
	"‚`",
	"‚a",
	"‚b",
	"‚c",
};

namespace roguegame {
	
	RogueEnding::RogueEnding(gameSceneChanger* changer)
		:gameBaseScene(changer){
		

		aMusic.Play(5);
	}

	void RogueEnding::Initialize() {
	}
	void RogueEnding::Update() {
		int rank=0;
		
	}
	void RogueEnding::Draw() {

	#pragma region BACK
		const int SpendDayPoint = SpendDay / 91;
		const int KillNumPoint = max(4, KillNum / 15);
		const int LoveHpPoint = max(4, (LoveHp + 99) / 100);
		aDrawableConsole.draw(4, 4, "‹Gß");
		aDrawableConsole.draw(4, 5, "‰ß‚²‚µ‚½“ú”F"+Common::To_ZString(SpendDay)+"•]‰¿F"+ SHOWRANK[SpendDayPoint]);
		aDrawableConsole.draw(4, 6, "“|‚µ‚½“G‚Ì”F" + Common::To_ZString(KillNum) + "•]‰¿F" + SHOWRANK[KillNumPoint]);
		aDrawableConsole.draw(4, 7, "“G‚ğˆ¤‚µ‚½—ÊF" + Common::To_ZString(LoveHp) + "•]‰¿F" + SHOWRANK[LoveHpPoint]);
		

	#pragma endregion
		switch (EndingNum) {
		case E_Dummy:
			assert(false);
		
			case E_Bad://t‚Ét€‚Ê				   
			break;
			case E_True://‰Ä‚Ét€‚Ê
				aDrawableConsole.draw(4, 8, "t‚Í‰Ä‚É‚ÍŸ‚Ä‚Ü‚¹‚ñ@“~‚ªt‚ÉŸ‚Ä‚È‚¢‚æ‚¤‚É");
			break;
			case E_SummerDead://‰Ä‚Ét€‚Ê
				
			break;
			case E_Why://H‚Ét€‚Ê				   
			break;
			case E_FallKillSummer://H‚É‰Ä€‚Ê	   
			break;
			case E_KillMeteorWithAll://“~‚Ét€‚Ê   
			break;
			case E_KillMeteorWithOutAll://“~‚Ét€‚Ê
			break;
		}

	}
}
