#include "RogueEnding.h"
#include "Keyboard.h"
#include "DrawableConsole.h"
#include "BackGround.h"
#include "Music.h"
#include "Common.h"
#include "RogueGame.h"
#include <string>
#include <algorithm>

extern roguegame::Ending EndingNum;//RogueGame���Q��
extern int LoveHp ;//RogueGame���Q��
extern int KillNum ;//RogueGame���Q��
extern int SpendDay ;//RogueGame���Q��

std::vector<string> SHOWRANK = {
	"�r",
	"�`",
	"�a",
	"�b",
	"�c",
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
		aDrawableConsole.draw(4, 4, "�G��");
		aDrawableConsole.draw(4, 5, "�߂����������F"+Common::To_ZString(SpendDay)+"�]���F"+ SHOWRANK[SpendDayPoint]);
		aDrawableConsole.draw(4, 6, "�|�����G�̐��F" + Common::To_ZString(KillNum) + "�]���F" + SHOWRANK[KillNumPoint]);
		aDrawableConsole.draw(4, 7, "�G���������ʁF" + Common::To_ZString(LoveHp) + "�]���F" + SHOWRANK[LoveHpPoint]);
		

	#pragma endregion
		switch (EndingNum) {
		case E_Dummy:
			assert(false);
		
			case E_Bad://�t�ɏt����				   
			break;
			case E_True://�Ăɏt����
				aDrawableConsole.draw(4, 8, "�t�͉Ăɂ͏��Ă܂���@�~���t�ɏ��ĂȂ��悤��");
			break;
			case E_SummerDead://�Ăɏt����
				
			break;
			case E_Why://�H�ɏt����				   
			break;
			case E_FallKillSummer://�H�ɉĎ���	   
			break;
			case E_KillMeteorWithAll://�~�ɏt����   
			break;
			case E_KillMeteorWithOutAll://�~�ɏt����
			break;
		}

	}
}
