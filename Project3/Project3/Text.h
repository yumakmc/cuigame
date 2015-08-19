#pragma once 
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gameBaseScene.h"
#include <vector>
#include <string>
#include <map>
using namespace std;



class Text:public gameBaseScene{
public:
	//Text::Text(gameSceneChanger* changer);

	Text::Text(vector<string> atexts, gameSceneChanger* changer);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpfield)override;
private:

	vector<string>texts;

	int nowline;
	int nowtext;
};