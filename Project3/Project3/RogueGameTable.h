#pragma once
namespace  roguegame {
	
	
	/*template<int dimension>
	struct TABLES<dimension>
	{
		for (int i = 0; i < dimension; ++i)
			value[i] = i;

	};*/


	template <int id, int level>
	struct TABLE {
		static const int next_exp = level + TABLE<id, level - 1>::next_exp; //idが敵なら落とす経験値　味方なら次に必要な経験値
		static const int max_hp = level + TABLE<id, level - 1>::max_hp;
		static const int atk = level + TABLE<id, level - 1>::atk;
		static const int def = level / 2 + TABLE<id, level - 1>::def;
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