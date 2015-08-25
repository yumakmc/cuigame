#ifndef	 __CONSOLE_BUFFER_H__
#define	 __CONSOLE_BUFFER_H__

#include	<Windows.h>
#include	"Common.h"


class ConsoleBuffer
{
public:
	// �`��̈�ő�T�C�Y
	static const unsigned short MAX_WIDTH = 80;
	static const unsigned short MAX_HEIGHT = 25;

	// �E�C���h�E�֘A
	virtual void resetWindowSize();					// �E�B���h�E�T�C�Y�̃��Z�b�g

	// �X�N���[���o�b�t�@�֘A
	typedef char SCREENNUM;							// �X�N���[���o�b�t�@�̐�
	static const SCREENNUM	INVALID_SCREEN = -1;	// �����ȃX�N���[��

	static ConsoleBuffer& instance();				// �C���X�^���X�̎擾�iSingleton�j
	virtual ~ConsoleBuffer();

	virtual SCREENNUM addScreen();					// �X�N���[���o�b�t�@��ǉ��i���펞�F�쐬�����X�N���[���o�b�t�@No�A�ُ펞�FINVALID_SCREEN�j
	virtual void showScreen() const;				// �`���X�N���[���o�b�t�@��\��
	virtual void nextScreen();						// ���̃X�N���[���o�b�t�@��`��ΏۂƂ���
	virtual void selectScreen(SCREENNUM screenNo);	// �X�N���[���o�b�t�@No�ɂĕ`��ΏۃX�N���[���o�b�t�@���w�肷��(1�ȏ�A0�͕ύX����)
	
	// �J�[�\���֘A
	virtual void setCursorVisible(BOOL visible) const;	// �J�[�\���\���؂�ւ�
	virtual void setCursorPossition(COORD coord) const;	// �J�[�\���ʒu�̐ݒ�

	// �`��֘A
	virtual void clear() const;										// ��ʂ̃N���A
//	virtual DWORD fill(COORD pos, TCHAR chr, DWORD length) const;	// �h��Ԃ�
	virtual void setDefaultColor(WORD textcolor, WORD bgcolor);		// �K��`��F�ݒ�
	virtual void loadDefaultColor() const;	 						// �K��`��F�ďo
	virtual void setColor(WORD textcolor, WORD bgcolor) const;		// �`��F�̐ݒ�
	virtual void writeString(const TCHAR* text) const;				// �������`���X�N���[���o�b�t�@�ɏ�������
	virtual unsigned short getStringWdith(const TCHAR* str) const;	// ������̕����擾�i�`�掞�̎��Z�����j

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


