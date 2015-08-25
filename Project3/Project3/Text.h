#pragma once 
#include "BaseScene.h"
#include "gameSceneChanger.h"
#include "gameBaseScene.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Text_Detail {//テキスト一行分
	string text;
	int color;
	int speed;//流れる速度
};
struct Text_Set {//テキスト数行分　これにアクションやしゃべる人の情報が加わる
	string name;
	int action;
	vector<Text_Detail> text_details;
};


class Text:public gameBaseScene{
public:
	//Text::Text(gameSceneChanger* changer);

	Text::Text(vector<string> atexts, gameSceneChanger* changer,const int enemy);
	void Initialize() override;
	//void Finalize() override;
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void Draw(vector<string> &tmpfield)override;

private:

	vector<string>texts;
	vector<Text_Set>textss;

	int nowline;
	int nowtext;

	static const int TEXTNUM = 3;//同時に表示されるテキストの行
	static const int NAMEUP = 15;
	static const int NAMELEFT = 0;
};