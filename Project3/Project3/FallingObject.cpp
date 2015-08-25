#include "FallingObject.h"
#include "Data_Rand.h"
#include "DrawableConsole.h"
#include <math.h>

FallingObject::FallingObject() {
	type=rnd() % 4+1;
	FallingObject(type);
}
FallingObject::FallingObject(const int atype) {
	type = atype;
	x = rnd() % SIZE_X;
	y = 0;
	switch (type) {
	case 1://‰Ô
		vel_x = 0.6;
		vel_y = 0.4;
		break;
	case 2://Œõ
		vel_x = 0.5;
		vel_y = 1;
		break;
	case 3://—t
		vel_x = -0.8;
		vel_y = 0.5;
		break;
	case 4://á
		vel_x = 0.3;
		vel_y = 0.2;
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
							   
bool FallingObject::Update(){//‰æ–Ê‚ª‚¢‚Éo‚½‚çfalse •Ô‚·
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
	aDrawableConsole.draw(x, y, FALLINGREAL[type].c_str());
}
void FallingObject::Draw(vector<string> &tmpfield) {
	aDrawableConsole.draw(x, y, FALLINGREAL[type].c_str());

}
