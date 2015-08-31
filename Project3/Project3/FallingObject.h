#pragma once
#include "Task.h"
#include "Data_Rand.h"
#include "Common.h"
#include "ConsoleBuffer.h"
#include "DrawableConsole.h"
#include <random>
#include <vector>
using namespace std;

struct FallingObjectInfo{
	string ch;
	DrawableConsole::COLOR color;
};

static map<int, FallingObjectInfo> FALLINGREAL = {
	{ 0,{"Å@",DrawableConsole::COLOR::C_WHITE }},
	{ 1,{"â‘",DrawableConsole::COLOR::C_LPINK } },
	{ 2,{"åı",DrawableConsole::COLOR::C_LYELLOW } },
	{ 3,{"ót",DrawableConsole::COLOR::C_LGREEN } },
	{ 4,{"ê·",DrawableConsole::COLOR::C_WHITE } },
};

class FallingObject{
public:
	FallingObject(const bool havecolor);
	FallingObject(const int atype, const bool havecolor);
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
	const int min_x;
	const int max_x;
	const int min_y;
	const int max_y;
	random_device rnd;
	float vel_x;
	float vel_y;
	float x;
	float y;

	const bool color;

	int type;
	Common::Rand arand;
};
