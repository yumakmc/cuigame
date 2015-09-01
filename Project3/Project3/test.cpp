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

//int CreateDIB32fromFile248(char *lpFileName, LPDWORD *lppPixel, BITMAPINFO *lpBmpInfo)
//{
//	HANDLE fh;
//	DWORD dwFileSize, dwReadSize;
//	LPBYTE lpbuf;
//
//	fh = CreateFile(lpFileName, GENERIC_READ, 0, NULL,
//		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (fh == INVALID_HANDLE_VALUE) {
//		MessageBox(NULL, "ファイルが開けません", lpFileName, MB_OK);
//		return -1;
//	}
//	dwFileSize = GetFileSize(fh, NULL);
//	lpbuf = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
//	ReadFile(fh, lpbuf, dwFileSize, &dwReadSize, NULL);
//	CloseHandle(fh);
//
//
//	LPBITMAPFILEHEADER lpbmpfh;
//	LPBITMAPINFO lpbmpInfo;
//	int bitCount;
//
//	lpbmpfh = (LPBITMAPFILEHEADER)lpbuf;
//	lpbmpInfo = (LPBITMAPINFO)(lpbuf + sizeof(BITMAPFILEHEADER));
//	bitCount = lpbmpInfo->bmiHeader.biBitCount;
//	if (lpbmpfh->bfType != ('M' << 8) + 'B' || (bitCount != 24 && bitCount != 8)) {
//		HeapFree(GetProcessHeap(), 0, lpbuf);
//		MessageBox(NULL, "24 or 8 ビットBMPファイルしか読み込めません", lpFileName, MB_OK);
//		return -2;
//	}
//
//
//	LPBYTE lpbmpPixel;
//	int iWidth, iHeight, iLength;
//
//	lpbmpPixel = lpbuf + lpbmpfh->bfOffBits;
//	iWidth = lpbmpInfo->bmiHeader.biWidth;
//	iHeight = lpbmpInfo->bmiHeader.biHeight;
//
//	if (iWidth*(bitCount / 8) % 4) iLength = iWidth*(bitCount / 8) + (4 - iWidth*(bitCount / 8) % 4);
//	else iLength = iWidth*(bitCount / 8);
//
//	*lppPixel = (LPDWORD)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, iWidth*iHeight * 4);
//
//
//	LPRGBQUAD lpColorTable;
//
//	switch (bitCount) {
//	case 24:
//		for (int y = 0; y<iHeight; y++)
//			for (int x = 0; x<iWidth; x++)
//				CopyMemory(*lppPixel + x + y*iWidth, lpbmpPixel + x * 3 + y*iLength, 3);
//		break;
//	case 8:
//		lpColorTable = lpbmpInfo->bmiColors;
//		for (int y = 0; y<iHeight; y++)
//			for (int x = 0; x<iWidth; x++)
//				CopyMemory(*lppPixel + x + y*iWidth, lpColorTable + lpbmpPixel[x + y*iLength], 3);
//		break;
//	}
//
//
//	CopyMemory(lpBmpInfo, &lpbmpInfo->bmiHeader, sizeof(BITMAPINFOHEADER));
//	lpBmpInfo->bmiHeader.biBitCount = 32;
//
//	HeapFree(GetProcessHeap(), 0, lpbuf);
//	return 0;
//}

int main(){
	/*static BITMAPINFO bmpInfo;
	static LPDWORD lpPixel;
	CreateDIB32fromFile248("2.bmp", &lpPixel, &bmpInfo);
	DWORD Pixel = *lpPixel;*/
	SceneMgr scenemgr;
	scenemgr.Initialize();
	clock_t time = 0;	
	CONSOLE_CURSOR_INFO info = {};

	static ConsoleBuffer&	m_ConsoleBuff(ConsoleBuffer::instance());

	 TCHAR			m_OriginalTitle[1024];
	// オリジナルのタイトルを取得
	::GetConsoleTitle(m_OriginalTitle, sizeof m_OriginalTitle);

	// 新しいタイトルを設定
	const TCHAR* title("黄色くなった時に上下左右キーで攻撃");
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
			time = min(time,TPF);
			
			Keyboard_Update();
			scenemgr.Update();

			m_ConsoleBuff.loadDefaultColor();// 規定描画色呼出
			m_ConsoleBuff.clear();// 画面のクリア

			scenemgr.Draw();
			
			m_ConsoleBuff.showScreen();// 描画先スクリーンバッファを表示
			m_ConsoleBuff.resetWindowSize();
			m_ConsoleBuff.nextScreen();
		}
	}
	::SetConsoleTitle(m_OriginalTitle);
	scenemgr.Finalize();
	return 0;
}
