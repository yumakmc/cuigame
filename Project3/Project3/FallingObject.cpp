#include "FallingObject.h"
#include "Data_Rand.h"
#include "DrawableConsole.h"
#include <math.h>

FallingObject::FallingObject(const bool havecolor):FallingObject(rnd() % 4 + 1,havecolor) {
	
}
FallingObject::FallingObject(const int atype, const bool havecolor): min_x(0), max_x(80/2), min_y(0), max_y(25),color(havecolor) {
	arand.init();
	type = atype;
	x = rnd() % SIZE_X;
	y = 0;
	switch (type) {
	case 1://花
		vel_x = 0.4*(1.0 + 0.01*float(arand.gen() % 100));
		vel_y = 0.3*(1.0 + 0.01*float(arand.gen() % 100));
		break;
	case 2://光
		vel_x = 0.3*(1.0 + 0.01*float(arand.gen() % 100));
		vel_y = 0.7*(1.0 + 0.01*float(arand.gen() % 100));
		break;
	case 3://葉
		vel_x =-0.5*(1.0 + 0.01*float(arand.gen() % 100));
		vel_y = 0.3*(1.0 + 0.01*float(arand.gen() % 100));
		break;
	case 4://雪
		vel_x = 0.2*(1.0 + 0.01*float(arand.gen() % 100));
		vel_y = 0.1*(1.0 + 0.01*float(arand.gen() % 100));
		break;
	}
}
FallingObject::FallingObject(const FallingObject &a) : min_x(0), max_x(80 / 2), min_y(0), max_y(25), color(a.color){
	type = a.type;
	x = a.x;
	y = a.y;
	vel_x = a.vel_x;
	vel_y = a.vel_y;
}
FallingObject::~FallingObject() {
}
void FallingObject::Initialize() {
}
							   
bool FallingObject::Update(){//画面がいに出たらfalse 返す
	x += vel_x;
	x=fmod(x+ max_x, max_x);

	y += vel_y;
	if (y > float(max_y)-0.00001) {
		return false;
	}
	else {
		return true;
	}
}
void FallingObject::Draw() {
	assert(y < float(max_y));
	if (!color) {
		aDrawableConsole.draw(DrawableConsole::POS(x), DrawableConsole::POS(y), FALLINGREAL[type].ch.c_str());
	}
	else {
		//DrawableConsole::COLOR::C_WHITE
		aDrawableConsole.setColor(FALLINGREAL[type].color, FALLINGREAL[type].color);//二個目の引数はダミー
		aDrawableConsole.draw(DrawableConsole::POS(x), DrawableConsole::POS(y), FALLINGREAL[type].ch.c_str(),false);
		aDrawableConsole.loadDefaultColor();
	}
}
void FallingObject::Draw(vector<string> &tmpfield) {
	assert(false);
	//aDrawableConsole.draw(x, y, FALLINGREAL[type].c_str());
}
