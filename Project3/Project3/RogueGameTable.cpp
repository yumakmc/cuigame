#include "RogueGameTable.h"


namespace roguegame {



	TABLEA::TABLEA() {
		tableinfos[0] = {
			5,
			10,
			3,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[i] = {
				tableinfos[i-1].exp + i,
				tableinfos[i - 1].max_hp + i,
				tableinfos[i - 1].atk + i,
				tableinfos[i - 1].def / 2 + i
			};
		}
	}
	std::array<TableInfo, MaxLevel> TABLEA::Get(const int id) {
		return tableinfos;
	}
}