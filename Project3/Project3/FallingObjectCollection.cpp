#include "FallingObjectCollection.h"
#include <assert.h>
FallingObjectCollection::FallingObjectCollection(int atype,const bool havecolor) :FallingObjects(), color(havecolor), type(atype) {

}
FallingObjectCollection::FallingObjectCollection(const bool havecolor):FallingObjects(),color(havecolor),type(0) {

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
	switch (type) {
	case 0:
		if (count % 3 == 0) {
			FallingObject a(color);
			FallingObjects.push_back(a);
		}
		break;
	case 1:
		if (count % 12 == 0) {
			FallingObject a(type,color);
			FallingObjects.push_back(a);
		}
		break;
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