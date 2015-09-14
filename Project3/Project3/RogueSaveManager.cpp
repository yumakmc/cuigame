#include "RogueSaveManager.h"

RogueSaveManager::RogueSaveManager() {
}
int RogueSaveManager::Save(const int num, BaseSaveData* savedata) {
	const string wfilename(GetFileName(num));
	std::ofstream ofs(wfilename, ios::out | ios::binary | ios::trunc);

	RogueSaveData* wdata(static_cast<RogueSaveData*>(savedata));
	Sizes[num] = sizeof(*wdata);
	ofs.write((char *)(wdata), sizeof(*wdata));
	//// �t�@�C����1�s����������
	//for (int i = 0; i < game.opparty.maxmember; ++i)
	//{
	//	OpChara *opchara = static_cast<OpChara*>(game.GetMember(i));
	//	if (opchara) {
	//		ofs << to_string(opchara->exp) << std::endl;
	//		ofs << to_string(opchara->id) << std::endl;
	//	}
	//	else {
	//		ofs <<"M" << std::endl;
	//	}
	//}
	//ofs << "N" << std::endl;
	//for (int i = 0; i < game.opparty.maxmember; ++i)
	//{
	//	MyChara *mychara = static_cast<MyChara*>(game.GetMember(i));
	//	if (mychara) {
	//		ofs << to_string(mychara->id) << std::endl;
	//		ofs << to_string(mychara->level) << std::endl;
	//	}
	//	else {
	//		ofs << "M" << std::endl;
	//	}
	//}
	//ofs << "N" << std::endl;
	//ofs << "" << std::endl;
	//ofs << "egg" << std::endl;
	//ofs << "spam" << std::endl;

	return 1;
}
int RogueSaveManager::Load(const int num, BaseSaveData* loaddata) {
	const string rfilename(GetFileName(num));
	std::ifstream ifs(rfilename,ios::in | ios::binary);

	RogueSaveData* rdata(static_cast<RogueSaveData*>(loaddata));
	ifs.read((char *)(rdata), Sizes[num]);

	return 1;
}
string RogueSaveManager::GetFileName(const int num) {
	return ("Rogue" + to_string(num) + ".txt");
}