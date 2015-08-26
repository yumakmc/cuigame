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


int main(){
	SceneMgr scenemgr;
	scenemgr.Initialize();
	clock_t time = 0;	
	CONSOLE_CURSOR_INFO info = {};

	static ConsoleBuffer&	m_ConsoleBuff(ConsoleBuffer::instance());

	 TCHAR			m_OriginalTitle[1024];
	// �I���W�i���̃^�C�g�����擾
	::GetConsoleTitle(m_OriginalTitle, sizeof m_OriginalTitle);

	// �V�����^�C�g����ݒ�
	const TCHAR* title("aaa");
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
			Keyboard_Update();
			scenemgr.Update();

			m_ConsoleBuff.loadDefaultColor();// �K��`��F�ďo
			m_ConsoleBuff.clear();// ��ʂ̃N���A

			scenemgr.Draw();
			LPDWORD cell(0);
			
			m_ConsoleBuff.showScreen();// �`���X�N���[���o�b�t�@��\��
			m_ConsoleBuff.resetWindowSize();
			m_ConsoleBuff.nextScreen();
		}
	}
	::SetConsoleTitle(m_OriginalTitle);
	scenemgr.Finalize();
	return 0;
}
