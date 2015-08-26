#pragma once

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
	int scene;
	int count;
};
