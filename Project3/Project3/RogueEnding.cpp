#include "RogueEnding.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include <string>
#include <algorithm>

extern int EndingNum;//RogueGameÇÊÇËéQè∆

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
	aDrawableConsole.draw(4, 4, "ãGêﬂ");

#pragma endregion

}

