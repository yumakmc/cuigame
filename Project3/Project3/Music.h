#pragma once
#pragma comment(lib,"winmm")//Play Sound �̂���
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;



namespace MyMusic {
	const vector<string> MUSICNAME = {
		"",//���� �A�N�Z�X�֎~
		"Dummy.wav",//�_�~�[
		"pop.wav",//�w�i�ɐF�������Ƃ���
		"sad_dream.wav",//���̒�
		"op.wav",//�I�[�v�j���O
		"lastboss.wav",//���X�{�X
	};
};

static class Music{
public:
	Music();
	bool Play(const int num);
private:
	int nowmusic=0;

}aMusic;