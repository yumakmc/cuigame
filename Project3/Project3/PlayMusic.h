#pragma once
#pragma comment(lib,"winmm")//Play Sound �̂���
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;
namespace MyMusic {
	const vector<string> MUSICNAME = {
		"Dummy.wav",//�_�~�[
	};


	bool PlayMusic(const int num);//��{�������[�v
};