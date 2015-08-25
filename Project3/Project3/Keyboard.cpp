#include <vector>
#include "Keyboard.h"
using namespace std;

static int m_Key[256];  // キーの入力状態格納用変数
static vector < vector<int> > b;

// キーの入力状態更新
void Keyboard_Update(){
	unsigned char tmpKey[256];             
	GetKeyboardState(tmpKey);  
	for (int i = 0; i<256; i++){
		if (GetAsyncKeyState(i)){ // i番のキーコードに対応するキーが押されていたら
			m_Key[i]++;   // 加算
		}
		else {              // 押されていなければ
			m_Key[i] = 0; // 0にする
		}
	}
}

// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode){
	return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}