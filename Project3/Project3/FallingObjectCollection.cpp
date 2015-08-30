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
	for (int i = EraseCole.size()-1; i >=0; --i) {
		FallingObjects.erase(FallingObjects.begin() + EraseCole[i]);
	}
	if (count % 3 == 0) {
		FallingObject a;
		FallingObjects.push_back(a);
	}
}
void FallingObjectCollection::Draw() {
	for (int i = 0; i < FallingObjects.size(); ++i) {
		FallingObjects[i].Draw();
	}
}
void FallingObjectCollection::Draw(vector<string> &tmpfield) {
	assert(false);
	for (int i = 0; i < FallingObjects.size(); ++i) {
		FallingObjects[i].Draw(tmpfield);
	}
}