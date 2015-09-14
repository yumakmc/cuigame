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
	
	"�c",
	"�b",
	"�a",
	"�`",
	"�r",
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
		aDrawableConsole.draw(4, 4, "�G��"); 
		aDrawableConsole.draw(4, 5, "�߂����������F" + Common::To_ZString(SpendDay)+"�]���F"+ SHOWRANK[SpendDayPoint]);
		aDrawableConsole.draw(4, 6, "�|�����G�̐��F" + Common::To_ZString(KillNum) + "�]���F" + SHOWRANK[KillNumPoint]);
		aDrawableConsole.draw(4, 7, "�G���������ʁF" + Common::To_ZString(LoveHp) + "�]���F" + SHOWRANK[LoveHpPoint]);
		

	#pragma endregion
		switch (EndingNum) {
		case E_Dummy:
			assert(false);
		
			case E_Bad://�t�ɏt����	
				aDrawableConsole.draw(4, 8, "�Ηj���@���ꂳ���ӎ����Ă�΂ǂ��ɂł��Ȃ�܂�");
				aDrawableConsole.draw(4, 9, "�d�c�|�P�F�@�a�`�c�@�d�m�c");
				break;
			case E_True://�Ăɏt����
				aDrawableConsole.draw(4, 8, "�t�͉Ăɂ͏��Ă܂���@�~���t�ɏ��ĂȂ��悤��");
				aDrawableConsole.draw(4, 9, "�d�c�O�F�@�s�q�t�d�@�d�m�c");
				break;
			case E_SummerDead://�Ăɏt����
				aDrawableConsole.draw(4, 8, "�t�͉Ă𒴉z����");
				aDrawableConsole.draw(4, 9, "�d�c�P�F�@�b�g�d�`�s�@�d�m�c");
				break;
			case E_Why://�H�ɏt����
				aDrawableConsole.draw(4, 8, "����͎��ȐӔC");
				aDrawableConsole.draw(4, 9, "�d�c�Q�F�@�l�h�r�s�`�j�d�@�d�m�c");
				break;
			case E_FallKillSummer://�H�ɉĎ���	 
				aDrawableConsole.draw(4, 8, "�t�ƏH�ɑ������R�͂Ȃ������̂Œ��ǂ���炵�܂����Ƃ�");
				aDrawableConsole.draw(4, 9, "�d�c�R�F�@�e�q�h�d�m�c�@�d�m�c");
				break;
			case E_DeadInWinter://�H�ɏt����
				aDrawableConsole.draw(4, 8, "");
				aDrawableConsole.draw(4, 9, "�d�c�S�F�@�d�m�c");
				break;
			case E_KillMeteorWithAll://  
				aDrawableConsole.draw(4, 8, "�������Đ��E�͋~��ꂽ");
				aDrawableConsole.draw(4, 9, "�d�c�T�F�@�j�h�k�k�@�l�d�s�d�n�q of the �b�n�r�l�n�r�@�d�m�c");
				break;
			case E_KillMeteorWithOutAll://
				aDrawableConsole.draw(4, 8, "�������Đ��E�͋~��ꂽ");
				aDrawableConsole.draw(4, 9, "�d�c�T�F�@�j�h�k�k�@�l�d�s�d�n�q of the �b�n�r�l�n�r�@�d�m�c");
				break;
			default :
				assert(false);
		}

	}
}
