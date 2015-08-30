#pragma once
#include "Task.h"
#include "Data_Rand.h"
#include "Common.h"
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
	void Draw();
	void Draw(vector<string> &tmpfield);   
	void FallingObject::operator =(const FallingObject &a) {
		vel_x = a.vel_x;
		vel_y = a.vel_y;
		x = a.x;
		y = a.y;
		type = a.type;
	}
private:
	random_device rnd;
	float vel_x;
	float vel_y;
	float x;
	float y;
	int type;
	Common::Rand arand;
};
