#pragma once

#include "gameBaseScene.h"
#include  "BackGround.h"
#include "RogueGameTable.h"
#include "RogueGameParty.h"
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
	

	class RogueGame :public gameBaseScene {
	public:
		RogueGame(gameSceneChanger* changer);
		void Initialize() override;
		//void Finalize() override;
		void Update() override;        //更新処理をオーバーライド。
		void Draw() override;            //描画処理をオーバーライド。
	private:

		MyParty myparty;
		OpParty opparty;
		string inline To_ZenString(const int anum);

		BackGround abackground;

		int situation;

		Common::Rand aRand;
		data adata;

	};
}
