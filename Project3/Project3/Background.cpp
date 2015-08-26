#include "Background.h"
#include "DrawableConsole.h"

BackGround::BackGround() :scene(0) {
}
BackGround::BackGround(const int num):scene(num) {
	
}
void BackGround::Update() {
	count++;
}
void BackGround::Draw() {
	switch (scene) {
	case 0:
		break;
	case 1:
	{
		aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_LBLUE);//��
		TCHAR str[81] = _T("          �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		for (int i = 0; i < 25; ++i) {
			aDrawableConsole.draw(0, i, str);
		}
		aDrawableConsole.draw(7, 5, "�_�_�_�_");
		aDrawableConsole.draw(5, 6, "�_�_�_�_�_�_�_�_");
		aDrawableConsole.draw(5, 7, "�_�_�_�_�_�_�_�_�_");
		aDrawableConsole.draw(7, 8, "�_�_�_�_");
		aDrawableConsole.draw(31, 11, "�_�_�_�_");
		aDrawableConsole.draw(31, 12, "�_�_�_�_");
		aDrawableConsole.setColor(DrawableConsole::COLOR::C_DGREEN, DrawableConsole::COLOR::C_LGREEN);//��
		aDrawableConsole.draw(12, 14, "    �@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(2, 15, "    �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		for (int i = 16; i < 25; ++i) {
			aDrawableConsole.draw(0, i, str);
		}
		aDrawableConsole.draw(1, 16, "��");
		aDrawableConsole.draw(4, 22, "��");
		aDrawableConsole.draw(14, 18, "��");
		aDrawableConsole.draw(17, 19, "��");
		aDrawableConsole.draw(19, 21, "��");
		aDrawableConsole.draw(23, 16, "��");
		aDrawableConsole.draw(27, 22, "��");
		aDrawableConsole.draw(30, 17, "��");
		aDrawableConsole.draw(33, 23, "��");
		aDrawableConsole.draw(34, 24, "��");

		aDrawableConsole.setColor(DrawableConsole::COLOR::C_DRED, DrawableConsole::COLOR::C_LYELLOW);//���z
		aDrawableConsole.draw(29, 0, "�@�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(29, 1, "�@�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(30, 2, "�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(30, 3, "�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(31, 4, "�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(32, 5, "�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(34, 6, "�@�@�@�@�@");
	}
	aDrawableConsole.loadDefaultColor();

	break;

	case 2:
	{
		aDrawableConsole.setColor(DrawableConsole::COLOR::C_WHITE, DrawableConsole::COLOR::C_LBLUE);//��
		TCHAR str[81] = _T("          �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		for (int i = 0; i < 25; ++i) {
			aDrawableConsole.draw(0, i, str);
		}
		aDrawableConsole.draw(7, 5, "�_�_�_�_");
		aDrawableConsole.draw(5, 6, "�_�_�_�_�_�_�_�_");
		aDrawableConsole.draw(5, 7, "�_�_�_�_�_�_�_�_�_");
		aDrawableConsole.draw(7, 8, "�_�_�_�_");
		aDrawableConsole.draw(31, 11, "�_�_�_�_");
		aDrawableConsole.draw(31, 12, "�_�_�_�_");
		aDrawableConsole.setColor(DrawableConsole::COLOR::C_DGREEN, DrawableConsole::COLOR::C_LGREEN);//��
		aDrawableConsole.draw(12, 14, "    �@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(2, 15, "    �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@");
		for (int i = 16; i < 25; ++i) {
			aDrawableConsole.draw(0, i, str);
		}
		aDrawableConsole.draw(1, 16, "��");
		aDrawableConsole.draw(4, 22, "��");
		aDrawableConsole.draw(14, 18, "��");
		aDrawableConsole.draw(17, 19, "��");
		aDrawableConsole.draw(19, 21, "��");
		aDrawableConsole.draw(23, 16, "��");
		aDrawableConsole.draw(27, 22, "��");
		aDrawableConsole.draw(30, 17, "��");
		aDrawableConsole.draw(33, 23, "��");
		aDrawableConsole.draw(34, 24, "��");

		aDrawableConsole.setColor(DrawableConsole::COLOR::C_DRED, DrawableConsole::COLOR::C_LYELLOW);//���z
		aDrawableConsole.draw(29, 0, "�@�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(29, 1, "�@�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(30, 2, "�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(30, 3, "�@�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(31, 4, "�@�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(32, 5, "�@�@�@�@�@�@�@�@");
		aDrawableConsole.draw(34, 6, "�@�@�@�@�@");
	}
	aDrawableConsole.loadDefaultColor();

	break;

	}
}