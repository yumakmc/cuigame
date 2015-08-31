#include "Background.h"
#include "DrawableConsole.h"
#include <string>
using namespace std;

bool HaveColor=false;//Menuでextern参照される　Menuの色の有無に使用

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
	//aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_BLACK);//黒
	//
	//for (int y = 0; y <25; ++y) {
	//	string blank = "";
	//	const int num= min(40, y - count + 40);
	//	for (int i = 0; i < num  ; ++i) {
	//		blank += "　";
	//	}
	//	TCHAR a[81]= _T("          　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	//	if (y > count) {
	//		aDrawableConsole.draw(0, y, a);
	//	}
	//	/*for (int x = 0; x < 40; x++) {
	//		
	//		if (y - x > count - 40) {
	//			if(x!=39||y!=24)
	//				aDrawableConsole.draw(x, y, "あ");
	//			if (x == 39&& y == 24)
	//				aDrawableConsole.draw(x, y, "aa");
	//		}
	//	}*/
	//}
	//aDrawableConsole.loadDefaultColor();
	aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_BLACK);//空
	for (int y = 0; y <25; ++y) {
		string blank;
		const int num= max(0,min(40, y - count + 40));
		for (int i = 0; i < num; ++i) {
			blank += "　";
		}
		aDrawableConsole.draw(0, y, blank.c_str());
	}
	aDrawableConsole.loadDefaultColor();
}
void BackGround::DrawGreenWorld() {
	aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_LBLUE);//空
	TCHAR str[81] = _T("          　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	for (int i = 0; i < 25; ++i) {
		aDrawableConsole.draw(0, i, str);
	}
	aDrawableConsole.draw(8, 3, "雲雲雲雲");
	aDrawableConsole.draw(6, 4, "雲雲雲雲雲雲雲雲");
	aDrawableConsole.draw(6, 5, "雲雲雲雲雲雲雲雲雲");
	aDrawableConsole.draw(8, 6, "雲雲雲雲");
	aDrawableConsole.draw(31, 11, "雲雲雲雲");
	aDrawableConsole.draw(31, 12, "雲雲雲雲");

	aDrawableConsole.setColor(DrawableConsole::COLOR::C_DGREEN, DrawableConsole::COLOR::C_LGREEN);//草
	aDrawableConsole.draw(12, 14, "    　　　　　　　　　　　　　　");
	aDrawableConsole.draw(2, 15, "    　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	for (int i = 16; i < 25; ++i) {
		aDrawableConsole.draw(0, i, str);
	}
	//aDrawableConsole.draw(1, 16, "草");
	//aDrawableConsole.draw(14, 18, "草");
	//aDrawableConsole.draw(17, 19, "草");
	//aDrawableConsole.draw(19, 21, "草");
	//aDrawableConsole.draw(23, 16, "草");
	//aDrawableConsole.draw(27, 22, "草");
	//aDrawableConsole.draw(30, 17, "草");
	//aDrawableConsole.draw(33, 23, "草");
	//aDrawableConsole.draw(34, 24, "草");

	aDrawableConsole.setColor(DrawableConsole::COLOR::C_DRED, DrawableConsole::COLOR::C_LYELLOW);//太陽
	aDrawableConsole.draw(29, 0, "　　　　　　　　　　　");
	aDrawableConsole.draw(29, 1, "　　　　　　　　　　　");
	aDrawableConsole.draw(30, 2, "　　　　　　　　　　");
	aDrawableConsole.draw(30, 3, "　　　　　　　　　　");
	aDrawableConsole.draw(31, 4, "　　　　　　　　　");
	aDrawableConsole.draw(32, 5, "　　　　　　　　");
	aDrawableConsole.draw(34, 6, "　　　　　");

	aDrawableConsole.loadDefaultColor();
}