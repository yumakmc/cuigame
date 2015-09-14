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
	
	"‚c",
	"‚b",
	"‚a",
	"‚`",
	"‚r",
};

namespace roguegame {
	
	RogueEnding::RogueEnding(gameSceneChanger* changer)
		:gameBaseScene(changer){
		

		aMusic.Play(-1);
	}

	void RogueEnding::Initialize() {
	}
	void RogueEnding::Update() {
		int rank=0;
		
	}
	void RogueEnding::Draw() {

	#pragma region BACK
		const int SpendDayPoint = SpendDay / 91;
		const int KillNumPoint = min(4, KillNum / 15);
		const int LoveHpPoint = min(4, (LoveHp + 99) / 100);
		aDrawableConsole.draw(4, 4, "‹Gß"); 
		aDrawableConsole.draw(4, 5, "‰ß‚²‚µ‚½“ú”F" + Common::To_ZString(SpendDay)+"•]‰¿F"+ SHOWRANK[SpendDayPoint]);
		aDrawableConsole.draw(4, 6, "“|‚µ‚½“G‚Ì”F" + Common::To_ZString(KillNum) + "•]‰¿F" + SHOWRANK[KillNumPoint]);
		aDrawableConsole.draw(4, 7, "“G‚ğˆ¤‚µ‚½—ÊF" + Common::To_ZString(LoveHp) + "•]‰¿F" + SHOWRANK[LoveHpPoint]);
		

	#pragma endregion
		switch (EndingNum) {
		case E_Dummy:
			assert(false);
		
			case E_Bad://t‚Ét€‚Ê	
				aDrawableConsole.draw(4, 8, "‰Î—j“ú@‚±‚ê‚³‚¦ˆÓ¯‚µ‚Ä‚ê‚Î‚Ç‚¤‚É‚Å‚à‚È‚è‚Ü‚·");
				aDrawableConsole.draw(4, 9, "‚d‚c|‚PF@‚a‚`‚c@‚d‚m‚c");
				break;
			case E_True://‰Ä‚Ét€‚Ê
				aDrawableConsole.draw(4, 8, "t‚Í‰Ä‚É‚ÍŸ‚Ä‚Ü‚¹‚ñ@“~‚ªt‚ÉŸ‚Ä‚È‚¢‚æ‚¤‚É");
				aDrawableConsole.draw(4, 9, "‚d‚c‚OF@‚s‚q‚t‚d@‚d‚m‚c");
				break;
			case E_SummerDead://‰Ä‚Ét€‚Ê
				aDrawableConsole.draw(4, 8, "t‚Í‰Ä‚ğ’´‰z‚µ‚½");
				aDrawableConsole.draw(4, 9, "‚d‚c‚PF@‚b‚g‚d‚`‚s@‚d‚m‚c");
				break;
			case E_Why://H‚Ét€‚Ê
				aDrawableConsole.draw(4, 8, "‚±‚ê‚Í©ŒÈÓ”C");
				aDrawableConsole.draw(4, 9, "‚d‚c‚QF@‚l‚h‚r‚s‚`‚j‚d@‚d‚m‚c");
				break;
			case E_FallKillSummer://H‚É‰Ä€‚Ê	 
				aDrawableConsole.draw(4, 8, "t‚ÆH‚É‘ˆ‚¤——R‚Í‚È‚©‚Á‚½‚Ì‚Å’‡—Ç‚­•é‚ç‚µ‚Ü‚µ‚½‚Æ‚³");
				aDrawableConsole.draw(4, 9, "‚d‚c‚RF@‚e‚q‚h‚d‚m‚c@‚d‚m‚c");
				break;
			case E_DeadInWinter://H‚Ét€‚Ê
				aDrawableConsole.draw(4, 8, "");
				aDrawableConsole.draw(4, 9, "‚d‚c‚SF@‚d‚m‚c");
				break;
			case E_KillMeteorWithAll://  
				aDrawableConsole.draw(4, 8, "‚±‚¤‚µ‚Ä¢ŠE‚Í‹~‚í‚ê‚½");
				aDrawableConsole.draw(4, 9, "‚d‚c‚TF@‚j‚h‚k‚k@‚l‚d‚s‚d‚n‚q of the ‚b‚n‚r‚l‚n‚r@‚d‚m‚c");
				break;
			case E_KillMeteorWithOutAll://
				aDrawableConsole.draw(4, 8, "‚±‚¤‚µ‚Ä¢ŠE‚Í‹~‚í‚ê‚½");
				aDrawableConsole.draw(4, 9, "‚d‚c‚TF@‚j‚h‚k‚k@‚l‚d‚s‚d‚n‚q of the ‚b‚n‚r‚l‚n‚r@‚d‚m‚c");
				break;
			default :
				assert(false);
		}

	}
}
