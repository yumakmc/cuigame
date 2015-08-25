#ifndef	 __CONSOLE_BUFFER_H__
#define	 __CONSOLE_BUFFER_H__

#include	<Windows.h>
#include	"Common.h"


class ConsoleBuffer
{
public:
	// 描画領域最大サイズ
	static const unsigned short MAX_WIDTH = 80;
	static const unsigned short MAX_HEIGHT = 25;

	// ウインドウ関連
	virtual void resetWindowSize();					// ウィンドウサイズのリセット

	// スクリーンバッファ関連
	typedef char SCREENNUM;							// スクリーンバッファの数
	static const SCREENNUM	INVALID_SCREEN = -1;	// 無効なスクリーン

	static ConsoleBuffer& instance();				// インスタンスの取得（Singleton）
	virtual ~ConsoleBuffer();

	virtual SCREENNUM addScreen();					// スクリーンバッファを追加（正常時：作成したスクリーンバッファNo、異常時：INVALID_SCREEN）
	virtual void showScreen() const;				// 描画先スクリーンバッファを表示
	virtual void nextScreen();						// 次のスクリーンバッファを描画対象とする
	virtual void selectScreen(SCREENNUM screenNo);	// スクリーンバッファNoにて描画対象スクリーンバッファを指定する(1以上、0は変更無し)
	
	// カーソル関連
	virtual void setCursorVisible(BOOL visible) const;	// カーソル表示切り替え
	virtual void setCursorPossition(COORD coord) const;	// カーソル位置の設定

	// 描画関連
	virtual void clear() const;										// 画面のクリア
//	virtual DWORD fill(COORD pos, TCHAR chr, DWORD length) const;	// 塗りつぶし
	virtual void setDefaultColor(WORD textcolor, WORD bgcolor);		// 規定描画色設定
	virtual void loadDefaultColor() const;	 						// 規定描画色呼出
	virtual void setColor(WORD textcolor, WORD bgcolor) const;		// 描画色の設定
	virtual void writeString(const TCHAR* text) const;				// 文字列を描画先スクリーンバッファに書き込む
	virtual unsigned short getStringWdith(const TCHAR* str) const;	// 文字列の幅を取得（描画時の実セル数）

private:
	ConsoleBuffer();

	HANDLE		m_hOriginal;
	HANDLE		m_hConsoleOut;
	HANDLE*		m_hSrceenBuffer;
	HANDLE		m_hWorkBuffer;
	SCREENNUM	m_ScreenNum;
	SCREENNUM	m_NowIndex;
	WORD		m_DefaultTextColor;
	WORD		m_DefaultBgColor;
};

#endif	 // __CONSOLE_BUFFER_H__


