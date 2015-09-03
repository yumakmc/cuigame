#include	<time.h>
#include	<stdexcept>
#include	<cstdio>
#include <string>
#include	"mt19937ar.h"
#include	"Common.h"

using namespace Library;

namespace Common
{
	// 疑似乱数
	Rand::GENERATE Rand::fn_Generate;
	Rand::UGENERATE Rand::fn_UGenerate;
	void Rand::init()
	{
		U32 seed = static_cast<U32>(time((time_t*)0));
		seed += Swap::reverseBits(seed); 
		init_genrand(seed);
	}
	S32 Rand::gen()
	{
		return genrand_int31();
	}
	U32 Rand::ugen()
	{
		return genrand_int32();
	}


	// コンソールウィンドウ
	ConsoleWindow::CLOSEFUNC ConsoleWindow::fn_close = 0;
	HWND ConsoleWindow::getHandle() const
	{
		HWND hwnd;
		TCHAR newTitle[1024];				// ハンドル取得用ウィンドウタイトル
		TCHAR oldTitle[sizeof newTitle];	// オリジナルウィンドウタイトル

		// 現在のウィンドウタイトルを取得
		::GetConsoleTitle(oldTitle, sizeof oldTitle);

		// ユニークなタイトルに変更し、タイトルからウィンドウハンドルを特定
		_stprintf_s(newTitle, (sizeof newTitle / sizeof TCHAR), _T("%d/%d\0"), GetTickCount(), GetCurrentProcessId());
		::SetConsoleTitle(newTitle);
		::Sleep(40);	// 誤作動防止に必要
		hwnd = ::FindWindow(NULL, newTitle);

		// タイトルを戻す
		::SetConsoleTitle(oldTitle);

		return hwnd;
	}
	void ConsoleWindow::setTitle(const TCHAR* const newTitle) const
	{
		// 新タイトルを設定
		::SetConsoleTitle(newTitle);
	}
	// ウィンドウ終了時のコールバック関数登録
	void ConsoleWindow::entryCloseCallback(CLOSEFUNC function)
	{
		::SetConsoleCtrlHandler(HandlerRoutine, TRUE);
		fn_close = function;
	}
	BOOL WINAPI ConsoleWindow::HandlerRoutine(DWORD dwCtrlType)
	{
		BOOL ret;

		switch(dwCtrlType) {
		case CTRL_C_EVENT:
		case CTRL_CLOSE_EVENT:
			if(fn_close != 0) {
				fn_close(1);
			}
			ret = TRUE;
			break;
		default:
			ret = FALSE;
			break;
		}

		return ret;
	}
	
}
