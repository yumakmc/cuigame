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

	TranpGame::TranpGame(vector<string> atexts, gameSceneChanger* changer);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpfield)override;
private:

	
};