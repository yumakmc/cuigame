#pragma once
#include "gameBaseScene.h"


//ÉQÅ[ÉÄâÊñ 
gameBaseScene::gameBaseScene(gameSceneChanger* changer) :
mImageHandle(0) {
	mgameSceneChanger = changer;
}
gameBaseScene::gameBaseScene(vector<Text_Detail> adetail, gameSceneChanger* changer) :
mImageHandle(0) {
	mgameSceneChanger = changer;
}
void gameBaseScene::Draw(){
	//DrawGraph(0, 0, mImageHandle, true);
}

void gameBaseScene::Finalize(){
	//DeleteGraph(mImageHandle);
}