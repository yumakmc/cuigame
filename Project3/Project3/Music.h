#pragma once
#pragma comment(lib,"winmm")//Play Sound のため
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

const vector<string> MUSICNAME = {
	"",//無音 アクセス禁止
	"Dummy.wav",//ダミー
	"pop.wav",//背景に色がついたときの
	"sad_dream.wav",//夢の中
	"op.wav",//オープニング
};

namespace MyMusic {
	

	bool PlayMusic(const int num);//基本無限ループ
};

static class Music{
public:
	Music();
	bool Play(const int num);
private:
	int nowmusic=0;

}aMusic;