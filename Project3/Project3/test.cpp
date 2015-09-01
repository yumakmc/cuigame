#pragma once 
#include "test.h"
#include "ConsoleBuffer.h"
#include "Common.h"
#include "DrawableConsole.h"
#include <vector>
#include <assert.h>
using namespace std;
using namespace Common;

static int Scene = eScene_Menu;    //���݂̉��(�V�[��)
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
//		MessageBox(NULL, "�t�@�C�����J���܂���", lpFileName, MB_OK);
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
//		MessageBox(NULL, "24 or 8 �r�b�gBMP�t�@�C�������ǂݍ��߂܂���", lpFileName, MB_OK);
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
	// �I���W�i���̃^�C�g�����擾
	::GetConsoleTitle(m_OriginalTitle, sizeof m_OriginalTitle);

	// �V�����^�C�g����ݒ�
	const TCHAR* title("���F���Ȃ������ɏ㉺���E�L�[�ōU��");
	ConsoleWindow	cwnd;
	cwnd.setTitle(title);
	// �J�[�\�����\��
	m_ConsoleBuff.setCursorVisible(FALSE);
	// �_�u���o�b�t�@�����O�p�ɃX�N���[���o�b�t�@��ǉ�
	m_ConsoleBuff.addScreen();

	aTimeManager.GetDifference();
	while (1){
		time += aTimeManager.GetDifference();
		if (time > TPF) {
			time -= TPF;
			time = min(time,TPF);
			
			Keyboard_Update();
			scenemgr.Update();

			m_ConsoleBuff.loadDefaultColor();// �K��`��F�ďo
			m_ConsoleBuff.clear();// ��ʂ̃N���A

			scenemgr.Draw();
			
			m_ConsoleBuff.showScreen();// �`���X�N���[���o�b�t�@��\��
			m_ConsoleBuff.resetWindowSize();
			m_ConsoleBuff.nextScreen();
		}
	}
	::SetConsoleTitle(m_OriginalTitle);
	scenemgr.Finalize();
	return 0;
}
