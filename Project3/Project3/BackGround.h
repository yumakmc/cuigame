#pragma once
#include "ConsoleBuffer.h"

class BackGround {
public:
	BackGround();
	BackGround(const int num);

	void Update();
	void Draw();
	void operator = (const BackGround &a){
		 scene = a.scene;
		 count = a.count;
	}
private:
	void DrawDarkCheck();
	void DrawGreenWorld();
	int scene;
	int count;
};
