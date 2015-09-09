#include "RogueGameTable.h"


namespace roguegame {



	TABLEA::TABLEA() {
		tableinfos[0] = {
			5,
			25,
			4,
			2
		};
		for (int i = 1; i < MaxLevel; ++i) {
			tableinfos[i] = {
				tableinfos[i - 1].exp + i*i,
				25 + i*5,
				4 + 3*i/2,
				2+i/2
			};
		}
	}
	std::array<TableInfo, MaxLevel> TABLEA::Get(const int num) {
		return tableinfos;
	}
}