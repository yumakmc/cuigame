#include "RogueEnding.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include "Common.h"
#include "RogueGame.h"
#include <string>
#include <algorithm>

extern roguegame::Ending EndingNum;//RogueGameより参照
extern int LoveHp ;//RogueGameより参照
extern int KillNum ;//RogueGameより参照
extern int SpendDay ;//RogueGameより参照

std::vector<string> SHOWRANK = {
	"Ｓ",
	"Ａ",
	"Ｂ",
	"Ｃ",
	"Ｄ",
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
		aDrawableConsole.draw(4, 4, "季節");
		aDrawableConsole.draw(4, 5, "過ごした日数："+Common::To_ZString(SpendDay)+"評価："+ SHOWRANK[SpendDayPoint]);
		aDrawableConsole.draw(4, 6, "倒した敵の数：" + Common::To_ZString(KillNum) + "評価：" + SHOWRANK[KillNumPoint]);
		aDrawableConsole.draw(4, 7, "敵を愛した量：" + Common::To_ZString(LoveHp) + "評価：" + SHOWRANK[LoveHpPoint]);
		

	#pragma endregion
		switch (EndingNum) {
		case E_Dummy:
			assert(false);
		
			case E_Bad://春に春死ぬ	
				aDrawableConsole.draw(4, 8, "火曜日　これさえ意識してればどうにでもなります");
				aDrawableConsole.draw(4, 9, "ＥＤ−１：　ＢＡＤ　ＥＮＤ");
				break;
			case E_True://夏に春死ぬ
				aDrawableConsole.draw(4, 8, "春は夏には勝てません　冬が春に勝てないように");
				aDrawableConsole.draw(4, 9, "ＥＤ０：　ＴＲＵＥ　ＥＮＤ");
				break;
			case E_SummerDead://夏に春死ぬ
				aDrawableConsole.draw(4, 8, "春は夏を超越した");
				aDrawableConsole.draw(4, 9, "ＥＤ１：　ＲＥＶＥＮＧＥ　ＥＮＤ");
				break;
			case E_Why://秋に春死ぬ
				aDrawableConsole.draw(4, 8, "これは自己責任");
				aDrawableConsole.draw(4, 9, "ＥＤ２：　ＭＩＳＴＡＫＥ　ＥＮＤ");
				break;
			case E_FallKillSummer://秋に夏死ぬ	 
				aDrawableConsole.draw(4, 8, "春と秋に争う理由はなかったので仲良く暮らしましたとさ");
				aDrawableConsole.draw(4, 9, "ＥＤ３：　ＦＲＩＥＮＤ　ＥＮＤ");
				break;
			case E_DeadInWinter://秋に春死ぬ
				aDrawableConsole.draw(4, 8, "");
				aDrawableConsole.draw(4, 9, "ＥＤ４：　ＥＮＤ");
				break;
			case E_KillMeteorWithAll://  
				aDrawableConsole.draw(4, 8, "こうして世界は救われた");
				aDrawableConsole.draw(4, 9, "ＥＤ５：　ＫＩＬＬ　ＭＥＴＥＯＲ of the ＣＯＳＭＯＳ　ＥＮＤ");
				break;
			case E_KillMeteorWithOutAll://
				aDrawableConsole.draw(4, 8, "こうして世界は救われた");
				aDrawableConsole.draw(4, 9, "ＥＤ５：　ＫＩＬＬ　ＭＥＴＥＯＲ of the ＣＯＳＭＯＳ　ＥＮＤ");
				break;
			default :
				assert(false);
		}

	}
}
