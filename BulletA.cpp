#include "BulletA.h"

///自機弾の初期化処理
void BulletA::Initialize() {

	///座標
	pos_ = { 0,-10 };
	///半径
	radius_ = { 10,10 };
	///移動速度
	speed_ = 7;
	///自機弾の色
	color_ = WHITE;
	///発射フラグ
	isShot_ = false;
	///自機弾の移動処理をラムダ式を使用して定義する
	bulletMove_ = [this]() 
	{
		//自機弾の発射フラグがtrueである場合
		if (isShot_) 
		{
			///複合減算演算子を使用して、自機弾を上方向に飛ばす
			pos_ -= Vector2(0, speed_);

			///Y座標が-20であるならば
			if (pos_.y <= -20) {
				///自機弾の発射フラグをfalseに設定する
				isShot_ = false;
			}

		}
	};
}

///自機弾の更新処理
void BulletA::Update() {
	///定義したラムダ式を呼び出す
	bulletMove_();
}

///自機弾の描画処理
void BulletA::Draw() {
	//自機弾の画像を呼び出す
	int bulletHandle = Novice::LoadTexture("./Resources/playerBullet.png");

	///発射フラグがtrueであれば
	if (isShot_) {
		///自機弾の画像を描画する
		Novice::DrawSprite(pos_.x + 22, pos_.y - 10, bulletHandle, 1.0f, 1.0f, 0.0f, color_);
		
	}
}


