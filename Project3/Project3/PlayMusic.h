#pragma once
#pragma comment(lib,"winmm")//Play Sound のため
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
namespace MyMusic {
	const vector<string> MUSICNAME = {
		"Dummy.wav",//ダミー
	};


	bool PlayMusic(const int num);//基本無限ループ
};