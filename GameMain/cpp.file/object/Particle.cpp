#include "GameMain/header.file/object/Particle.h"
#include "stdlib.h"

/// 初期化処理
void Particle::Initialize() {

#pragma region メンバ変数の定義

	///座標
	pos_ = {0,-10};
	
	///半径
	radius_ = rand() % 10 + 8;
	
	///移動速度
	speed_ = rand() % 3 + 1;
	
	///パーティクルの色
	color_ = 0x0000FF80;
	
	///ショットフラグ
	isShot_ = false;

	///ラムダ式を使用して、パーティクルの移動処理を行う
	particleMove_ = [this]() {

		//発射フラグがtrueにあるならば
		if (isShot_ == true)
		{
			//パーティクルを下方向に向かわせる
			pos_ += Vector2(0, speed_);

			//カラーのBLUE値とアルファ値を減算する
			color_ -= 0x01000002;

			//もしアルファ値が0であるならば
			if (color_ <= 0x0000FF00) {
				//青色にアルファ値128（約50%透明）を設定
				color_ = 0x0000FF80;
			}

			//Y座標が740以上であるなら
			if (pos_.y >= 740) {
				//発射フラグをfalseにする
				isShot_ = false;
			}
		}

	};

#pragma endregion

}

/// 更新処理
void Particle::Update(){

	//パーティクルを移動させるラムダ式を呼び出す
	particleMove_();

}

/// 描画処理
void Particle::Draw() {

	//もしショットフラグが立っているならば
	if (isShot_ == true)
	{
		//パーティクルを描画する
		Novice::DrawBox(pos_.x, pos_.y, radius_, radius_, 0.0f, color_, kFillModeSolid);
	}

}

#pragma region カプセル化とアクセッサの定義

void Particle::SetPosition(Vector2 pos) { this->pos_ = pos; }

bool Particle::GetIsShot() { return this->isShot_; }

bool Particle::SetIsShot(bool isShot) { return this->isShot_ = isShot; }

#pragma endregion