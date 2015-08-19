#pragma once
#include "FallingObject.h"
#include  "Data_Rand.h"
#include <vector>
using namespace std;

class FallingObjectCollection:public Task {
public:
	FallingObjectCollection();
	~FallingObjectCollection();
	void Initialize() override;    //�������������I�[�o�[���C�h�B
								   //void Finalize() override ;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void Draw(vector<string> &tmpfield);
private:
	vector<FallingObject> FallingObjects;
	int count;

};