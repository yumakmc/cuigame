#pragma once
#pragma comment(lib,"winmm")//Play Sound �̂���
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

const vector<string> MUSICNAME = {
	"",//���� �A�N�Z�X�֎~
	"Dummy.wav",//�_�~�[
	"pop.wav",//�w�i�ɐF�������Ƃ���
	"sad_dream.wav",//���̒�
};

namespace MyMusic {
	

	bool PlayMusic(const int num);//��{�������[�v
};

static class Music{
public:
	Music();
	bool Play(const int num);
private:
	int nowmusic;

}aMusic;