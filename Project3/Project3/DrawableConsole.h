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
	// 描画領域最大サイズ
	const POS MAX_WIDTH;
	const POS MAX_HEIGHT;
	// 色
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

	void setDrawPosition(DRAW_POS pos) const;		// 描画位置
	void setDrawPosition(POS x, POS y) const;		// 描画位置

	void draw(const TCHAR* text) const;								// テキスト描画
	void draw(DRAW_POS pos, const TCHAR* text) const;	 			// テキスト描画（座標付）
	void draw(POS x, POS y, const TCHAR* text) const;	 			// テキスト描画（座標付）
	void drawf(const TCHAR* formatText, ...) const;	 				// テキスト描画（書式付）
	void drawf(DRAW_POS pos, const TCHAR* formatText, ...) const;	// テキスト描画（座標・書式付）	
	void drawf(POS x, POS y, const TCHAR* formatText, ...) const;	// テキスト描画（座標・書式付）

	void setColor(COLOR textcolor, COLOR bgcolor) const;	 // 描画色設定
	void setDefaultColor(COLOR textcolor, COLOR bgcolor);	 // 規定色設定

	void loadDefaultColor() const;	 				// 規定色呼出


private:
	ConsoleBuffer&	m_ConsoleBuff;
}aDrawableConsole;

#endif	 // __DRAWABLE_CONSOLE_H__
