#pragma once
#include "BaseScene.h"
#include <assert.h>
using namespace std;

//#include "//"


//ÉQÅ[ÉÄâÊñ 
BaseScene::BaseScene(SceneChanger* changer) :
mImageHandle(0) {
	mSceneChanger = changer;
}
void BaseScene::Draw(){
	//assert(false);
	//DrawGraph(0, 0, mImageHandle, true);
}
void BaseScene::Draw(vector<string> &tmpfield) {
	//DrawGraph(0, 0, mImageHandle, true);
}
void BaseScene::Finalize(){
	//DeleteGraph(mImageHandle);
}