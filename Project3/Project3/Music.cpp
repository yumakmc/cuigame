#include "Music.h"

Music::Music() {
}
bool Music::Play(const int newmusic) {
	if (newmusic == 0|| newmusic ==nowmusic) {
		return true;//�ω��Ȃ�
	}
	else {
		nowmusic = newmusic;
		return PlaySound(newmusic == -1 ? NULL : MyMusic::MUSICNAME[newmusic].c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
}