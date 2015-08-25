#ifndef	 __DRAWABLE_CONSOLE_H__
#define	 __DRAWABLE_CONSOLE_H__

#include	<Windows.h>
#include	"Common.h"
#include	"ConsoleBuffer.h"

static class DrawableConsole
{
public:	
	typedef unsigned short POS;
	typedef COORD DRAW_POS;
	// �`��̈�ő�T�C�Y
	const POS MAX_WIDTH;
	const POS MAX_HEIGHT;
	// �F
	enum COLOR {
		C_BLACK = 0x00,
		C_DBLUE,
		C_DGREEN,
		C_DCYAN,
		C_DRED,
		C_DPINK,
		C_DYELLOW,
		C_LGRAY,
		C_DGRAY,
		C_LBLUE,
		C_LGREEN,
		C_LCYAN,
		C_LRED,
		C_LPINK,
		C_LYELLOW,
		C_WHITE
	};

	DrawableConsole();
	DrawableConsole& operator=(DrawableConsole&){};
	virtual ~DrawableConsole();

	void setDrawPosition(DRAW_POS pos) const;		// �`��ʒu
	void setDrawPosition(POS x, POS y) const;		// �`��ʒu

	void draw(const TCHAR* text) const;								// �e�L�X�g�`��
	void draw(DRAW_POS pos, const TCHAR* text) const;	 			// �e�L�X�g�`��i���W�t�j
	void draw(POS x, POS y, const TCHAR* text) const;	 			// �e�L�X�g�`��i���W�t�j
	void drawf(const TCHAR* formatText, ...) const;	 				// �e�L�X�g�`��i�����t�j
	void drawf(DRAW_POS pos, const TCHAR* formatText, ...) const;	// �e�L�X�g�`��i���W�E�����t�j	
	void drawf(POS x, POS y, const TCHAR* formatText, ...) const;	// �e�L�X�g�`��i���W�E�����t�j

	void setColor(COLOR textcolor, COLOR bgcolor) const;	 // �`��F�ݒ�
	void setDefaultColor(COLOR textcolor, COLOR bgcolor);	 // �K��F�ݒ�

	void loadDefaultColor() const;	 				// �K��F�ďo


private:
	ConsoleBuffer&	m_ConsoleBuff;
}aDrawableConsole;

#endif	 // __DRAWABLE_CONSOLE_H__
