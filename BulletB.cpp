#include "BulletB.h"

//初期化処理
void BulletB::Initialize() {

	//座標
	pos_ = { 0,-10 };

	//半径
	radius_ = { 10,10 };

	///移動速度
	speed_ =  7;

	//弾の色
	color_ = WHITE;

	//発射フラグ
	isShot_ = false;

	//敵機弾を移動させる処理
	bulletMove_ = [this]()
	{
		if (isShot_)
		{
			pos_ += Vector2(0, speed_);

			if (pos_.y >= 740) {
				isShot_ = false;
			}

		}
	};
}

//更新処理
void BulletB::Update(){

	///敵機弾を移動させるラムダ式を呼び出す
	bulletMove_();
}

///描画処理
void BulletB::Draw(){
	///敵機の弾の画像を読み込む
	int bulletHandle = Novice::LoadTexture("./Resources/enemyBullet.png");

	///発射フラグが立っていれば
	if (isShot_) {
		///敵機の弾を描画する
		Novice::DrawSprite(pos_.x + 22, pos_.y + 40, bulletHandle, 1.0f, 1.0f, 0.0f, color_);
	}
}

