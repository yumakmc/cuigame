#include "FallingObjectCollection.h"
#include <assert.h>

FallingObjectCollection::FallingObjectCollection():FallingObjects() {

}
FallingObjectCollection::~FallingObjectCollection() {

}
void FallingObjectCollection::Initialize() {

}
void FallingObjectCollection::Update() {
	count++;
	count %= 360;
	vector<int> EraseCole;
	for (int i = 0; i < FallingObjects.size(); ++i) {
		
		if (!FallingObjects[i].Update()) {
			EraseCole.push_back(i);
		}
	}
	for (int i = 0; i <EraseCole.size(); ++i) {
		FallingObjects.erase(FallingObjects.begin() + EraseCole[i]);//=のオーバーライドが必要？めんどいからひまなときに
	}
	if (count % 3 == 0) {
		FallingObject a(count / 90 + 1);
		FallingObjects.push_back(a);
	}
}
void FallingObjectCollection::Draw() {
	for (int i = 0; i < FallingObjects.size(); ++i) {
		FallingObjects[i].Draw();
	}
}
void FallingObjectCollection::Draw(vector<string> &tmpfield) {
	for (int i = 0; i < FallingObjects.size(); ++i) {
		FallingObjects[i].Draw(tmpfield);
	}
}