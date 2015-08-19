#pragma once
#include "Task.h"
#include "Data_Rand.h"
#include <random>
#include <vector>
using namespace std;
class FallingObject{
public:
	FallingObject();
	FallingObject(const int atype);
	FallingObject(const FallingObject &rhs);
	virtual ~FallingObject() ;
	virtual void Initialize();    
	//void Finalize() override ;        
	bool Update() ;        
	void Draw(vector<string> &tmpfield);          
private:
	random_device rnd;
	float vel_x;
	float vel_y;
	float x;
	float y;
	int type;
};
