#pragma once
#include "gameBaseScene.h"
#include <assert.h>

//�Q�[�����
gameBaseScene::gameBaseScene(gameSceneChanger* changer) :
mImageHandle(0) {
	mgameSceneChanger = changer;
}

void gameBaseScene::Draw(){
}
void gameBaseScene::Draw(vector<string> &tmpfield) {

}
void gameBaseScene::Finalize(){
}