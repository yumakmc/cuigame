#pragma once
#include <array>

namespace  roguegame {
	const int MaxLevel=101;
	
	struct TableInfo {
		 int exp;
		 int max_hp;
		 int atk;
		 int def;
	};
	static class TABLEA {
	public:
		TABLEA();
		std::array<TableInfo, MaxLevel> Get(const int num);
	private:
		std::array<std::array<TableInfo, MaxLevel>,4> tableinfos;

	}TABLE_A;
	

	//template <int level>
	//constexpr int TBLE <0, level> {
	//	static const int next_exp = level + TBLE(0, level - 1);
	//	//static const int max_hp = level + TBLE<0, level - 1>::max_hp;
	//	//static const int atk = level + TBLE<0, level - 1>::atk;
	//	//static const int def = level + TBLE<0, level - 1>::def / 2;
	//	return next_exp;
	//};
	//template <>
	//constexpr int TBLE <0, 0> {
	//	static const int next_exp = 1; // fact(n) = n * fact(n-1)
	//	//static const int max_hp = 10;
	//	//static const int atk = 3;
	//	//static const int def = 2;
	//	return next_exp;
	//};
	
	template <int id, int level>
	struct TABLE {
		static const int next_exp = level + TABLE<id, level - 1>::next_exp; //idが敵なら落とす経験値　味方なら次に必要な経験値
		static const int max_hp = level + TABLE<id, level - 1>::max_hp;
		static const int atk = level + TABLE<id, level - 1>::atk;
		static const int def = level + TABLE<id, level - 1>::def / 2;
	};
	template <int id>
	struct TABLE <id, 0> {
		static const int next_exp = 1; // fact(n) = n * fact(n-1)
		static const int max_hp = 10;
		static const int atk = 3;
		static const int def = 2;
	};
	template <int level>
	struct TABLE <0, level> {
		static const int next_exp = level + TABLE<0, level - 1>::next_exp;
		static const int max_hp = level + TABLE<0, level - 1>::max_hp;
		static const int atk = level + TABLE<0, level - 1>::atk;
		static const int def = level + TABLE<0, level - 1>::def / 2;
	};
	template <>
	struct TABLE <0, 0> {
		static const int next_exp = 1; // fact(n) = n * fact(n-1)
		static const int max_hp = 10;
		static const int atk = 3;
		static const int def = 2;
	};
	
}