#include	<cstdarg>
#include	<tchar.h>
#include	<cassert>
#include	<cstdio>
#include	"DrawableConsole.h"


DrawableConsole::DrawableConsole()
	: m_ConsoleBuff(ConsoleBuffer::instance()), MAX_WIDTH(ConsoleBuffer::MAX_WIDTH), MAX_HEIGHT(ConsoleBuffer::MAX_HEIGHT)
{
}
DrawableConsole::~DrawableConsole()
{
}


// 描画位置設定
void DrawableConsole::setDrawPosition(DRAW_POS pos) const
{
	assert(((pos.X >> 1) < MAX_WIDTH) && (pos.Y < MAX_HEIGHT));

	pos.X <<= 1;
	m_ConsoleBuff.setCursorPossition(pos);
}
void DrawableConsole::setDrawPosition(POS x, POS y) const
{
	assert(((x >> 1) < MAX_WIDTH) && (y < MAX_HEIGHT));

	x <<= 1;
	COORD coord = {x, y};

	m_ConsoleBuff.setCursorPossition(coord);
}


// テキスト描画
void DrawableConsole::draw(const TCHAR* text) const
{
	m_ConsoleBuff.writeString(text);
}
// テキスト描画（座標付）
void DrawableConsole::draw(DRAW_POS pos, const TCHAR* text) const
{
	setDrawPosition(pos);
	m_ConsoleBuff.writeString(text);
}
// テキスト描画（座標付）
void DrawableConsole::draw(POS x, POS y, const TCHAR* text) const
{
	setDrawPosition(x, y);
	m_ConsoleBuff.writeString(text);
}

// テキスト描画（書式付）
void DrawableConsole::drawf(const TCHAR* formatText, ...) const
{
	TCHAR text[ConsoleBuffer::MAX_WIDTH * ConsoleBuffer::MAX_HEIGHT + 1] = _T("");
	va_list args;

	va_start(args, formatText);

	_vstprintf_s(text, (sizeof text / sizeof TCHAR), formatText, args);
	m_ConsoleBuff.writeString(text);

	va_end(args);
}
// テキスト描画（座標・書式付）
void DrawableConsole::drawf(DRAW_POS pos, const TCHAR* formatText, ... ) const
{
	TCHAR text[ConsoleBuffer::MAX_WIDTH * ConsoleBuffer::MAX_HEIGHT + 1] = _T("");
	va_list args;

	va_start(args, formatText);

	setDrawPosition(pos);
	_vstprintf_s(text, (sizeof text / sizeof TCHAR), formatText, args);
	m_ConsoleBuff.writeString(text);

	va_end(args);
}
// テキスト描画（座標・書式付）
void DrawableConsole::drawf(POS x, POS y, const TCHAR* formatText, ... ) const
{
	TCHAR text[ConsoleBuffer::MAX_WIDTH * ConsoleBuffer::MAX_HEIGHT + 1] = _T("");
	va_list args;

	va_start(args, formatText);

	setDrawPosition(x, y);
	_vstprintf_s(text, (sizeof text / sizeof TCHAR), formatText, args);
	m_ConsoleBuff.writeString(text);

	va_end(args);
}

// 描画色設定
void DrawableConsole::setColor(COLOR textcolor, COLOR bgcolor) const
{	
	m_ConsoleBuff.setColor(static_cast<WORD>(textcolor), static_cast<WORD>(bgcolor));
}


// 規定色設定
void DrawableConsole::setDefaultColor(COLOR textcolor, COLOR bgcolor)
{
	m_ConsoleBuff.setDefaultColor(static_cast<WORD>(textcolor), static_cast<WORD>(bgcolor));
}
// 規定色呼出
void DrawableConsole::loadDefaultColor() const
{
	m_ConsoleBuff.loadDefaultColor();
}
