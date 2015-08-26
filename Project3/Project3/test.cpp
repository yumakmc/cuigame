#pragma once 
#include "test.h"
#include "ConsoleBuffer.h"
#include "Common.h"
#include "DrawableConsole.h"
#include <vector>
#include <assert.h>
using namespace std;
using namespace Common;

static int Scene = eScene_Menu;    //現在の画面(シーン)
const double FPS = 10.0;
const double TPF = CLOCKS_PER_SEC/ FPS;


int main(){
	SceneMgr scenemgr;
	scenemgr.Initialize();
	clock_t time = 0;	
	CONSOLE_CURSOR_INFO info = {};

	static ConsoleBuffer&	m_ConsoleBuff(ConsoleBuffer::instance());

	 TCHAR			m_OriginalTitle[1024];
	// オリジナルのタイトルを取得
	::GetConsoleTitle(m_OriginalTitle, sizeof m_OriginalTitle);

	// 新しいタイトルを設定
	const TCHAR* title("aaa");
	ConsoleWindow	cwnd;
	cwnd.setTitle(title);
	// カーソルを非表示
	m_ConsoleBuff.setCursorVisible(FALSE);
	// ダブルバッファリング用にスクリーンバッファを追加
	m_ConsoleBuff.addScreen();

	aTimeManager.GetDifference();
	while (1){
		time += aTimeManager.GetDifference();
		if (time > TPF) {
			time -= TPF;
			Keyboard_Update();
			scenemgr.Update();

			m_ConsoleBuff.loadDefaultColor();// 規定描画色呼出
			m_ConsoleBuff.clear();// 画面のクリア

			scenemgr.Draw();
			LPDWORD cell(0);
			
			m_ConsoleBuff.showScreen();// 描画先スクリーンバッファを表示
			m_ConsoleBuff.resetWindowSize();
			m_ConsoleBuff.nextScreen();
		}
	}
	::SetConsoleTitle(m_OriginalTitle);
	scenemgr.Finalize();
	return 0;
}
