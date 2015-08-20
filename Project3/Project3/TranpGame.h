#pragma once
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gameBaseScene.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

class TranpGame :public gameBaseScene {
public:

	TranpGame::TranpGame(const int aopponent,vector<string> atexts, gameSceneChanger* changer);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpfield)override;
private:
	const int opponent;
	bool mycarduseds[13];
	int  mypoint;
	bool opcarduseds[13];
	int  oppoint;
	vector<int> opcards;
};