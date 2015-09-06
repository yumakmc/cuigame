#pragma once

#include "gameBaseScene.h"
#include  "BackGround.h"
#include "Common.h"
#include <map>
#include <vector>
#include <array>
#include <string>
#include <utility>
using namespace std;
namespace  roguegame {

	/*struct table {
	int next_exp;
	int max_hp;
	int atk;
	int def;
	};
	static vector<array < table, 100 >> TABLES;*/



	class RogueEnding :public gameBaseScene {
	public:
		RogueEnding(gameSceneChanger* changer);
		void Initialize() override;
		void Update() override;        //更新処理をオーバーライド。
		void Draw() override;            //描画処理をオーバーライド。
		
	private:
	};
}