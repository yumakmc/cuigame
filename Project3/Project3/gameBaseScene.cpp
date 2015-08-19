#pragma once
#include "gameBaseScene.h"
#include <assert.h>

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
	assert(false);
}
void gameBaseScene::Draw(vector<string> &tmpfield) {

}
void gameBaseScene::Finalize(){
}