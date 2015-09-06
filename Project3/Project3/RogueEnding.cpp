#include "RogueEnding.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include "Common.h"
#include <string>
#include <algorithm>

extern int EndingNum;//RogueGameより参照
extern int LoveHp ;//RogueGameより参照
extern int KillNum ;//RogueGameより参照
extern int SpendDay ;//RogueGameより参照

using namespace roguegame;

namespace roguegame {
	

}


RogueEnding::RogueEnding(gameSceneChanger* changer)
	:gameBaseScene(changer){


	aMusic.Play(5);
}

void RogueEnding::Initialize() {
}
void RogueEnding::Update() {
}
void RogueEnding::Draw() {

#pragma region BACK
	aDrawableConsole.draw(4, 4, "季節");
	aDrawableConsole.draw(4, 5, "過ごした日数："+Common::To_ZString(SpendDay));
	aDrawableConsole.draw(4, 6, "倒した敵の数：" + Common::To_ZString(KillNum));
	aDrawableConsole.draw(4, 7, "敵を愛した量：" + Common::To_ZString(LoveHp));
	aDrawableConsole.draw(4, 8, "季節");

#pragma endregion

}

