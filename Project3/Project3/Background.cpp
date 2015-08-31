#include "Background.h"
#include "DrawableConsole.h"
#include <string>
using namespace std;

bool HaveColor=false;//Menu��extern�Q�Ƃ����@Menu�̐F�̗L���Ɏg�p

BackGround::BackGround(){
	BackGround(0);
}
BackGround::BackGround(const int num):scene(num),afoc(1,true) {
	count = 0;
}
void BackGround::Update() {
	count++;
	switch (scene) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		afoc.Update();
	}
}
void BackGround::Draw() {
	switch (scene) {
	case 0:
		break;
	case 1:
		HaveColor = true;
		DrawGreenWorld();
		DrawDarkCheck();
		break;

	case 2:
		DrawGreenWorld();
		break;
	case 3:
		DrawGreenWorld();
		DrawFallingFlower();
	}
}
void BackGround::DrawFallingFlower() {
	afoc.Draw();
}
void BackGround::DrawDarkCheck() {
	//aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_BLACK);//��
	//
	//for (int y = 0; y <25; ++y) {
	//	string blank = "";
	//	const int num= min(40, y - count + 40);
	//	for (int i = 0; i < num  ; ++i) {
	//		blank += "�@";
	//	}
	//	TCHAR a[81]= _T("          �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
	//	if (y > count) {
	//		aDrawableConsole.draw(0, y, a);
	//	}
	//	/*for (int x = 0; x < 40; x++) {
	//		
	//		if (y - x > count - 40) {
	//			if(x!=39||y!=24)
	//				aDrawableConsole.draw(x, y, "��");
	//			if (x == 39&& y == 24)
	//				aDrawableConsole.draw(x, y, "aa");
	//		}
	//	}*/
	//}
	//aDrawableConsole.loadDefaultColor();
	aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_BLACK);//��
	for (int y = 0; y <25; ++y) {
		string blank;
		const int num= max(0,min(40, y - count + 40));
		for (int i = 0; i < num; ++i) {
			blank += "�@";
		}
		aDrawableConsole.draw(0, y, blank.c_str());
	}
	aDrawableConsole.loadDefaultColor();
}
void BackGround::DrawGreenWorld() {
	aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_LBLUE);//��
	TCHAR str[81] = _T("          �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
	for (int i = 0; i < 25; ++i) {
		aDrawableConsole.draw(0, i, str);
	}
	aDrawableConsole.draw(8, 3, "�_�_�_�_");
	aDrawableConsole.draw(6, 4, "�_�_�_�_�_�_�_�_");
	aDrawableConsole.draw(6, 5, "�_�_�_�_�_�_�_�_�_");
	aDrawableConsole.draw(8, 6, "�_�_�_�_");
	aDrawableConsole.draw(31, 11, "�_�_�_�_");
	aDrawableConsole.draw(31, 12, "�_�_�_�_");

	aDrawableConsole.setColor(DrawableConsole::COLOR::C_DGREEN, DrawableConsole::COLOR::C_LGREEN);//��
	aDrawableConsole.draw(12, 14, "    �@�@�@�@�@�@�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(2, 15, "    �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
	for (int i = 16; i < 25; ++i) {
		aDrawableConsole.draw(0, i, str);
	}
	//aDrawableConsole.draw(1, 16, "��");
	//aDrawableConsole.draw(14, 18, "��");
	//aDrawableConsole.draw(17, 19, "��");
	//aDrawableConsole.draw(19, 21, "��");
	//aDrawableConsole.draw(23, 16, "��");
	//aDrawableConsole.draw(27, 22, "��");
	//aDrawableConsole.draw(30, 17, "��");
	//aDrawableConsole.draw(33, 23, "��");
	//aDrawableConsole.draw(34, 24, "��");

	aDrawableConsole.setColor(DrawableConsole::COLOR::C_DRED, DrawableConsole::COLOR::C_LYELLOW);//���z
	aDrawableConsole.draw(29, 0, "�@�@�@�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(29, 1, "�@�@�@�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(30, 2, "�@�@�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(30, 3, "�@�@�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(31, 4, "�@�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(32, 5, "�@�@�@�@�@�@�@�@");
	aDrawableConsole.draw(34, 6, "�@�@�@�@�@");

	aDrawableConsole.loadDefaultColor();
}