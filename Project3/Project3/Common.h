#ifndef		__COMMON_H__
#define		__COMMON_H__

#include	<cassert>
#include	<tchar.h>
#include	<windows.h>
#include <string>
#include	"typedef.h"

using namespace Library;

namespace Common {
	enum ERROR_CODE {
		ERR_CONSTRUCT = 1,	// コンストラクタ例外
	};

	namespace Meta {
		// ビット位置の静的算出
		// 値Nについて、最大のビット位置と最小のビット位置を求め
		//（例：126→most:7,least:1  128→most:8, least:8
		template<U32 N> struct BitPos
		{
			enum {
				most = (1 < N) ? BitPos<N / 2>::most + 1 : 0,
				least = ((N & 1) == 0) ? BitPos<N / 2>::least + 1 : 0
			};
		};
		template<> struct BitPos<0> { enum { most = -1, least = -1 }; };

	
		// 同一型チェック
		template<class T1, class T2> struct isEqualType
		{
			static const bool result = false;
		};
		template<class T1> struct isEqualType<T1, T1>
		{
			static const bool result = true;
		};
	}

	// スワップクラス
	class Swap
	{
	public:
		// 値の交換
		template<typename T> static void xor(T& v1, T& v2) {
			assert((&v1 != &v2) && ((&v1 != 0) && (&v2 != 0)));
			v1 ^= v2, v2 ^= v1, v1 ^= v2;
		}
		// 値の交換
		template<typename T> static void temporary(T* v1, T* v2) {
			assert((v1 != 0) && (v2 != 0));
			T tv = *v1;	*v1 = *v2; *v2 = tv;
		}
		// ビットパターンの逆転
		template<typename T> static T reverseBits(T v) {
			assert(sizeof T <= 4);
			switch(sizeof T) {
				case 4:	v = (v >> 16) | (v << 16);
				case 2:	v = ((v & 0xff00ff00) >> 8) | ((v & 0x00ff00ff) << 8);
				case 1:	v = ((v & 0xf0f0f0f0) >> 4) | ((v & 0x0f0f0f0f) << 4);
						v = ((v & 0xcccccccc) >> 2) | ((v & 0x33333333) << 2);
						v = ((v & 0xaaaaaaaa) >> 1) | ((v & 0x55555555) << 1);
			}
			return v;
		}
	};

	// 疑似乱数クラス
	class Rand
	{
	public:
		// 初期化
		void init();
		// 生成
		S32 gen();
		U32 ugen();
		// 配列シャッフル
		template<typename T> void shuffle(T* arrayVal, U32 valueCnt) {
			assert(arrayVal != 0);
			for(U32 i = 0; i < valueCnt; i++) {
				Swap::temporary(&arrayVal[ugen() % valueCnt], &arrayVal[i]);
			}
		}
	private:
		typedef S32 (*GENERATE)();
		typedef U32 (*UGENERATE)();
		static GENERATE fn_Generate;
		static UGENERATE fn_UGenerate;
	};


	// コンソールウィンドウ関連クラス
	class ConsoleWindow
	{
	public:
		typedef void (*CLOSEFUNC)(int);

		HWND getHandle() const;								// ウィンドウハンドル取得
		void setTitle(const TCHAR* const newTitle) const;	// タイトル設定
		void entryCloseCallback(CLOSEFUNC function);		// ウィンドウ終了時のコールバック関数登録

	private:
		static BOOL WINAPI HandlerRoutine(DWORD dwCtrlType);
		static CLOSEFUNC fn_close;
	};
	std::string inline To_ZString(const int anum) {
		std::string st = std::to_string(anum);
		if (st.size() % 2) {
			st = " " + st;
		}
		return st;
	}
};

#endif		// __COMMON_H__
