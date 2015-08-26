#include "PlayMusic.h"

namespace MyMusic {
	bool PlayMusic(const int num) {
		return PlaySound(num==-1?NULL:MUSICNAME[num].c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}