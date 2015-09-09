#include "RogueGameTable.h"


namespace roguegame {



	TABLEA::TABLEA() {
#pragma region PARAMETER_SPRING
		int id = 0;
		tableinfos[id][0] = {
			5,
			25,
			4,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[id][i] = {
				tableinfos[id][i - 1].exp + i*i,
				25 + i * 5,
				4 + 3 * i / 2,
				2 + i / 2
			};
		}
#pragma endregion
#pragma region PARAMETER_SUMMER
		id = 1;
		tableinfos[id][0] = {
			5,
			100,
			4,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[id][i] = {
				tableinfos[id][i - 1].exp + i*i,
				100 + i * 20,
				4 + 3 * i / 2,
				2 + i / 2
			};
		}

#pragma endregion
#pragma region PARAMETER_FALL
		id = 2;
		tableinfos[id][0] = {
			5,
			100,
			4,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[id][i] = {
				tableinfos[id][i - 1].exp + i*i,
				100 + i * 20,
				4 + 3 * i / 2,
				2 + i / 2
			};
		}
#pragma endregion
#pragma region PARAMETER_WINTER
		id = 3;
		tableinfos[id][0] = {
			5,
			100,
			4,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[id][i] = {
				tableinfos[id][i - 1].exp + i*i,
				100 + i * 20,
				4 + 3 * i / 2,
				2 + i / 2
			};
		}
#pragma endregion
	}
	std::array<TableInfo, MaxLevel> TABLEA::Get(const int num) {
		return tableinfos[num];
	}
}