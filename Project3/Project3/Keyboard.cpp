#include <vector>
#include "Keyboard.h"
using namespace std;

static int m_Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�
static vector < vector<int> > b;

// �L�[�̓��͏�ԍX�V
void Keyboard_Update(){
	unsigned char tmpKey[256];             
	GetKeyboardState(tmpKey);  
	for (int i = 0; i<256; i++){
		if (GetAsyncKeyState(i)){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i]++;   // ���Z
		}
		else {              // ������Ă��Ȃ����
			m_Key[i] = 0; // 0�ɂ���
		}
	}
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard_Get(int KeyCode){
	return m_Key[KeyCode]; // KeyCode�̓��͏�Ԃ�Ԃ�
}