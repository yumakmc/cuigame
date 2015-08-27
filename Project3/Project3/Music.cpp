#include "Music.h"

namespace MyMusic {
	bool PlayMusic(const int num) {
		if (num == 0) {
			return true;//•Ï‰»‚È‚µ
		}
		return PlaySound(num==-1?NULL:MUSICNAME[num].c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}

Music::Music() {
}
bool Music::Play(const int newmusic) {
	if (newmusic == 0|| newmusic ==nowmusic) {
		return true;//•Ï‰»‚È‚µ
	}
	else {
		nowmusic = newmusic;
		return PlaySound(newmusic == -1 ? NULL : MUSICNAME[newmusic].c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	
}