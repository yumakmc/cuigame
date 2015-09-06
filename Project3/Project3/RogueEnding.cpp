#include "RogueEnding.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include "Common.h"
#include <string>
#include <algorithm>

extern int EndingNum;//RogueGame���Q��
extern int LoveHp ;//RogueGame���Q��
extern int KillNum ;//RogueGame���Q��
extern int SpendDay ;//RogueGame���Q��

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
	aDrawableConsole.draw(4, 4, "�G��");
	aDrawableConsole.draw(4, 5, "�߂����������F"+Common::To_ZString(SpendDay));
	aDrawableConsole.draw(4, 6, "�|�����G�̐��F" + Common::To_ZString(KillNum));
	aDrawableConsole.draw(4, 7, "�G���������ʁF" + Common::To_ZString(LoveHp));
	aDrawableConsole.draw(4, 8, "�G��");

#pragma endregion

}

