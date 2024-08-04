#include "GameMain/header.file/scene/TitleScene.h"

/// 初期化処理
void TitleScene::Initialize() {
}

/// 更新処理
void TitleScene::Update(char *keys,char *preKeys) {

	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		sceneNo = Scene::STAGE;
	}
}

/// 更新処理
void TitleScene::Draw() {

	///画像の読み込み
	int TitleBackGroundHandle = Novice::LoadTexture("./Resources/Title.png");

	///DrawSprite関数で画像を描画する
	Novice::DrawSprite(0, 0, TitleBackGroundHandle, 1, 1, 0, WHITE);

}
