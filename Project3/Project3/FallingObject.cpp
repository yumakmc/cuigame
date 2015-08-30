#include "FallingObject.h"
#include "Data_Rand.h"
#include "DrawableConsole.h"
#include <math.h>

FallingObject::FallingObject() {
	type=rnd() % 4+1;
	FallingObject(type);
}
FallingObject::FallingObject(const int atype) {
	arand.init();
	type = atype;
	x = rnd() % SIZE_X;
	y = 0;
	switch (type) {
	case 1://花
		vel_x = 0.4*(1+0.01*double(arand.gen()%100));
		vel_y = 0.3*(1.0 + 0.01*double(arand.gen() % 100));
		break;
	case 2://光
		vel_x = 0.3*(1.0 + 0.01*double(arand.gen() % 100));
		vel_y = 0.7 * (1.0 + 0.01*double(arand.gen() % 100));
		break;
	case 3://葉
		vel_x = -0.5*(1.0 + 0.01*double(arand.gen() % 100));
		vel_y = 0.3*(1.0 + 0.01*double(arand.gen() % 100));
		break;
	case 4://雪
		vel_x = 0.2*(1.0 + 0.01*double(arand.gen() % 100));
		vel_y = 0.1*(1.0 + 0.01*double(arand.gen() % 100));
		break;
	}
}
FallingObject::FallingObject(const FallingObject &a) {
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
	x=fmod(x+SIZE_X, SIZE_X);

	y += vel_y;
	if (y > SIZE_Y) {
		return false;
	}
	else {
		return true;
	}
}
void FallingObject::Draw() {
	aDrawableConsole.draw(DrawableConsole::POS(x), DrawableConsole::POS(y), FALLINGREAL[type].c_str());
}
void FallingObject::Draw(vector<string> &tmpfield) {
	assert(false);
	//aDrawableConsole.draw(x, y, FALLINGREAL[type].c_str());

}
