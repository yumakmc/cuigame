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
		//FallingObjects.erase(FallingObjects.begin() + EraseCole[i]);//=のオーバーライドが必要？めんどいからひまなときに
	}
	if (count % 3 == 0) {
		FallingObject a(count / 90 + 1);
		FallingObjects.push_back(a);
	}
}
void FallingObjectCollection::Draw() {
	assert(false);
	vector<vector<int>> TmpField(SIZE_Y, vector<int>(SIZE_X,0));
	for (int i = 0; i < FallingObjects.size(); ++i) {
		//FallingObjects[i].Draw();
	}
	for (int y = 0; y < TmpField.size(); ++y) {
		for (int  x= 0; x < TmpField[0].size(); ++x) {
			cout << FALLINGREAL[TmpField[y][x]];
		}
		cout << endl;
	}
}
void FallingObjectCollection::Draw(vector<string> &tmpfield) {
	vector<vector<int>> TmpField(SIZE_Y, vector<int>(SIZE_X, 0));
	for (int i = 0; i < FallingObjects.size(); ++i) {
		FallingObjects[i].Draw(tmpfield);
	}
}