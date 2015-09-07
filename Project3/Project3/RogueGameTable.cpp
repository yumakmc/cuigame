#include "RogueGameTable.h"


namespace roguegame {



	TABLEA::TABLEA() {
		tableinfos[0] = {
			5,
			30,
			5,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[i] = {
				tableinfos[i - 1].exp + i*i,
				tableinfos[i - 1].max_hp + i*i/2,
				tableinfos[i - 1].atk + i-1,
				2+i/2
			};
		}
	}
	std::array<TableInfo, MaxLevel> TABLEA::Get(const int num) {
		return tableinfos;
	}
}