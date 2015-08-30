#include	"ConsoleBuffer.h"


ConsoleBuffer::ConsoleBuffer()
	: m_NowIndex(0), m_ScreenNum(0), m_hSrceenBuffer(NULL), m_DefaultTextColor(0x0f), m_DefaultBgColor(0)
{
	// コンソール出力ハンドルを取得
	try {
		// 基本スクリーンバッファを作成し、アクティブにする
		m_hSrceenBuffer = new HANDLE[1];
		m_hConsoleOut = m_hSrceenBuffer[0] = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if(m_hSrceenBuffer[0] == INVALID_HANDLE_VALUE) {
			throw;
		}
		m_ScreenNum = 1;
		// スクリーンバッファサイズ・ウィンドウサイズを規定サイズに変更
		COORD coord = { MAX_WIDTH, MAX_HEIGHT };
		SMALL_RECT sr = { 0, 0, (MAX_WIDTH-1), (MAX_HEIGHT-1) };
		::SetConsoleScreenBufferSize(m_hConsoleOut, coord);
		::SetConsoleWindowInfo(m_hConsoleOut, TRUE, &sr);
		// 初期画面として設定
		::SetConsoleActiveScreenBuffer(m_hConsoleOut);

		// 作業用スクリーンバッファを作成
		m_hWorkBuffer = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if(m_hWorkBuffer == INVALID_HANDLE_VALUE) {
			throw;
		}
	} catch(...) {
		throw Common::ERR_CONSTRUCT;
	}
}

ConsoleBuffer::~ConsoleBuffer()
{
	::CloseHandle(m_hWorkBuffer);
	m_hWorkBuffer = NULL;

	for(SCREENNUM i = 0; i < m_ScreenNum; i++) {
		::CloseHandle(m_hSrceenBuffer[i]);
	}
	delete[] m_hSrceenBuffer;
	m_hSrceenBuffer = NULL;

	m_hConsoleOut = NULL;	// 複製である為、解放処理は不要
}

// インスタンスの取得
ConsoleBuffer& ConsoleBuffer::instance() {
	static ConsoleBuffer buffer;
	return buffer;
}

// ウィンドウサイズのリセット
void ConsoleBuffer::resetWindowSize()
{
	CONSOLE_SCREEN_BUFFER_INFO buff;
	
	// 初期のバッファサイズと現状のバッファサイズとを比較
	::GetConsoleScreenBufferInfo(m_hConsoleOut, &buff);
	if((MAX_WIDTH != buff.dwSize.X)
	|| (MAX_HEIGHT != buff.dwSize.Y)) {
		COORD coord = { MAX_WIDTH, MAX_HEIGHT };
		::SetConsoleScreenBufferSize(m_hConsoleOut, coord);

	}
	// 規定のウィンドウサイズと現状のウィンドウサイズとを比較
	if((0 != buff.srWindow.Left)
	|| (0 != buff.srWindow.Top)
	|| ((MAX_WIDTH-1) != buff.srWindow.Right)
	|| ((MAX_HEIGHT-1) != buff.srWindow.Bottom)) {
		SMALL_RECT sr = { 0, 0, (MAX_WIDTH-1), (MAX_HEIGHT-1) };
		::SetConsoleWindowInfo(m_hConsoleOut, TRUE, &sr);
	}
}

// スクリーンバッファを追加
ConsoleBuffer::SCREENNUM ConsoleBuffer::addScreen()
{
	HANDLE* htmp = 0;
	SCREENNUM num = m_ScreenNum + 1;

	try {
		// スクリーンバッファ作成
		htmp = new HANDLE[num];
		memcpy_s(htmp, sizeof(HANDLE) * num, m_hSrceenBuffer, sizeof(HANDLE) * (num - 1));
		delete[] m_hSrceenBuffer;
		m_hSrceenBuffer = new HANDLE[num];

		htmp[num - 1] = ::CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if(htmp[num - 1] == INVALID_HANDLE_VALUE) {
			throw;
		}
		memcpy_s(m_hSrceenBuffer, sizeof(HANDLE) * num, htmp, sizeof(HANDLE) * num);

		// カーソル表示状態を継承
		CONSOLE_CURSOR_INFO info = {};
		::GetConsoleCursorInfo(m_hConsoleOut, &info);
		::SetConsoleCursorInfo(m_hSrceenBuffer[num - 1], &info);

		m_ScreenNum = num;

	} catch(...) {
		num = INVALID_SCREEN;
	}
	delete[] htmp;

	return num;
}

// 描画先スクリーンバッファを表示
void ConsoleBuffer::showScreen() const
{
	::SetConsoleActiveScreenBuffer(m_hConsoleOut);
}
// 次のスクリーンバッファを対象とする
void ConsoleBuffer::nextScreen()
{
	m_NowIndex = (m_NowIndex + 1) % m_ScreenNum;
	m_hConsoleOut = m_hSrceenBuffer[m_NowIndex];
}
// スクリーンバッファNoにて描画対象スクリーンバッファを指定する
void ConsoleBuffer::selectScreen(SCREENNUM screenNo)
{
	assert((0 <= screenNo) && (screenNo <= m_ScreenNum));

	if(0 < screenNo) {
		m_NowIndex = screenNo - 1;
		m_hConsoleOut = m_hSrceenBuffer[m_NowIndex];
	}
}


// カーソル表示切り替え
void ConsoleBuffer::setCursorVisible(BOOL visible) const
{
	CONSOLE_CURSOR_INFO info = {};

	::GetConsoleCursorInfo(m_hConsoleOut, &info);
	info.bVisible = visible;
	for(SCREENNUM i = 0; i < m_ScreenNum; i++) {
		::SetConsoleCursorInfo(m_hSrceenBuffer[i], &info);
	}
}

// カーソル位置の設定
void ConsoleBuffer::setCursorPossition(COORD pos) const
{
	::SetConsoleCursorPosition(m_hConsoleOut, pos);
}


// 画面のクリア
void ConsoleBuffer::clear() const
{
	DWORD wbyte;
	COORD coord = {};
	TCHAR str[MAX_WIDTH * MAX_HEIGHT+1] = _T("");

	::SetConsoleCursorPosition(m_hConsoleOut, coord);
	::WriteConsole(m_hConsoleOut, str, static_cast<DWORD>(MAX_WIDTH * MAX_HEIGHT), &wbyte, NULL);
}
/*
// 画面塗りつぶし
DWORD ConsoleBuffer::fill(COORD pos, TCHAR chr, DWORD length) const
{
	DWORD cell;

	::FillConsoleOutputCharacter(m_hConsoleOut, chr, length, pos, &cell);

	return cell;
}
*/
// 規定描画色設定
void ConsoleBuffer::setDefaultColor(WORD textcolor, WORD bgcolor)
{
	m_DefaultTextColor = textcolor;
	m_DefaultBgColor = bgcolor;
}
// 規定描画色呼出
void ConsoleBuffer::loadDefaultColor() const
{
	::SetConsoleTextAttribute(m_hConsoleOut, (m_DefaultTextColor | (m_DefaultBgColor << 4)));
	::SetConsoleTextAttribute(m_hConsoleOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 描画色の設定
void ConsoleBuffer::setColor(WORD textcolor, WORD bgcolor) const
{
	::SetConsoleTextAttribute(m_hConsoleOut, static_cast<WORD>(textcolor | (bgcolor << 4)));
}

// 文字列を描画先スクリーンバッファに書き込む カーソル位置動かさないためにいろいろ変更
void ConsoleBuffer::writeString(const TCHAR* text, const bool changebgcolor) const
{
	/*DWORD wbyte;
	::WriteConsole(m_hConsoleOut, text, static_cast<DWORD>(_tcslen(text)), &wbyte, NULL);*/
	CHAR_INFO  charInfo[2001],precharInfo[2001];
	COORD      coordSize;
	SMALL_RECT prercDest;
	int tsize = strlen(text);
	
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(m_hConsoleOut, &info);
	// コピー元のサイズ
	coordSize.X = tsize;
	coordSize.Y = 1;
	prercDest.Left = info.dwCursorPosition.X;
	prercDest.Top = info.dwCursorPosition.Y;
	prercDest.Right = info.dwCursorPosition.X + coordSize.X;
	prercDest.Bottom = info.dwCursorPosition.Y + 1;
	ReadConsoleOutput(m_hConsoleOut, precharInfo, { SHORT(tsize),1 }, { 0,0 }, &prercDest);
	for (int i = 0; i < tsize; i++) {
		charInfo[i].Char.UnicodeChar = text[i];
		if (changebgcolor) {
			charInfo[i].Attributes = info.wAttributes;
		}
		else {
			charInfo[i].Attributes = (info.wAttributes&0x0f)|(precharInfo[i].Attributes&0xf0);
		}
	}
	// コピー先の位置とサイズ

	WriteConsoleOutput(m_hConsoleOut, charInfo, coordSize, { 0,0 }, &prercDest);
}

// 文字列の幅を取得（描画時の実セル数）
unsigned short ConsoleBuffer::getStringWdith(const TCHAR* str) const
{
	DWORD wbyte;
	COORD coord = {0};
	CONSOLE_SCREEN_BUFFER_INFO info = {0};

	::SetConsoleCursorPosition(m_hWorkBuffer, coord);
	::WriteConsole(m_hWorkBuffer, str, static_cast<DWORD>(_tcslen(str)), &wbyte, NULL);
	::GetConsoleScreenBufferInfo(m_hWorkBuffer, &info);

	return static_cast<unsigned short>(info.dwCursorPosition.Y * info.dwSize.X + info.dwCursorPosition.X);
}
