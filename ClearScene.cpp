#include "ClearScene.h"

void ClearScene::Initialize() {}

void ClearScene::Update(char* keys, char* preKeys) {

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		sceneNo = Scene::TITLE;
	}
}

void ClearScene::Draw() 
{
	//クリア画面の画像を読み込む
	int ClearBackGroundHandle = Novice::LoadTexture("./Resources/Clear.png");

	///Drawsprite関数で画像を描画する
	Novice::DrawSprite(0, 0, ClearBackGroundHandle, 1, 1, 0, WHITE);

}